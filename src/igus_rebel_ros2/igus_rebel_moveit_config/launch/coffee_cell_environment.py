#!/usr/bin/env python3
"""
coffee_cell_environment.py (Parameter-driven version)

Publishes collision objects to the MoveIt2 Planning Scene.
Object positions are read from ROS parameters, allowing real-time updates
from the position_adjuster.py script.

Usage:
    Terminal 1: ros2 launch your_moveit_config demo.launch.py
    Terminal 2: python3 coffee_cell_environment.py
    Terminal 3: python3 position_adjuster.py  (to adjust positions interactively)
"""

import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, DurabilityPolicy
from rcl_interfaces.msg import SetParametersResult

from geometry_msgs.msg import Pose, Point, Quaternion
from shape_msgs.msg import SolidPrimitive
from moveit_msgs.msg import CollisionObject, PlanningScene
from std_msgs.msg import Header, ColorRGBA
from moveit_msgs.msg import ObjectColor

from shape_msgs.msg import Mesh, MeshTriangle
from geometry_msgs.msg import Point as GeoPoint
import trimesh


# ---------------------------------------------------------------------------
# Dimensions — all in metres
# ---------------------------------------------------------------------------

# Cell enclosure
CELL = {
    "width":  2.000,
    "depth":  1.000,
    "height": 1.587,
    "wall_t": 0.045,
}

RAIL_BASE_Z  = 0.0
RAIL_HEIGHT  = 0.120

TABLE = {
    "size_x": 2.000,
    "size_y": 1.000,
    "size_z": 0.100,
}
TABLE["cz"] = RAIL_BASE_Z - RAIL_HEIGHT - TABLE["size_z"] / 2

FLOOR_Z = RAIL_BASE_Z - RAIL_HEIGHT - TABLE["size_z"]

_table_surface_z = RAIL_BASE_Z - RAIL_HEIGHT

NO_GO_ZONE = {
    "size_x": 2.00,
    "size_y": 0.35,
    "size_z": 0.13,
    "x":  0.00,
    "y": -0.32,
    "z":  _table_surface_z + 0.13 / 2,
}

FRAME_ID = "world"


# ---------------------------------------------------------------------------
# Helper Functions
# ---------------------------------------------------------------------------

def box_object(object_id: str, frame_id: str,
               sx: float, sy: float, sz: float,
               px: float, py: float, pz: float,
               qx: float = 0.0, qy: float = 0.0,
               qz: float = 0.0, qw: float = 1.0) -> CollisionObject:
    """Return a CollisionObject that is a box with the given pose."""
    obj = CollisionObject()
    obj.header = Header()
    obj.header.frame_id = frame_id
    obj.id = object_id
    obj.operation = CollisionObject.ADD

    box = SolidPrimitive()
    box.type = SolidPrimitive.BOX
    box.dimensions = [sx, sy, sz]

    pose = Pose()
    pose.position = Point(x=px, y=py, z=pz)
    pose.orientation = Quaternion(x=qx, y=qy, z=qz, w=qw)

    obj.primitives = [box]
    obj.primitive_poses = [pose]
    return obj


def rgba(r: float, g: float, b: float, a: float = 0.6) -> ColorRGBA:
    c = ColorRGBA()
    c.r, c.g, c.b, c.a = r, g, b, a
    return c


def mesh_object(object_id, frame_id, stl_path, px, py, pz, qx, qy, qz, qw, scale=1.0):
    mesh_data = trimesh.load(stl_path)
    
    obj = CollisionObject()
    obj.header = Header()
    obj.header.frame_id = frame_id
    obj.id = object_id
    obj.operation = CollisionObject.ADD

    ros_mesh = Mesh()
    
    # vertices
    for v in mesh_data.vertices:
        p = GeoPoint()
        p.x, p.y, p.z = float(v[0]) * scale, float(v[1]) * scale, float(v[2]) * scale
        ros_mesh.vertices.append(p)
    
    # triangles
    for f in mesh_data.faces:
        t = MeshTriangle()
        t.vertex_indices = [int(f[0]), int(f[1]), int(f[2])]
        ros_mesh.triangles.append(t)

    pose = Pose()
    pose.position = Point(x=px, y=py, z=pz)
    pose.orientation = Quaternion(x=qx, y=qy, z=qz, w=qw)

    obj.meshes = [ros_mesh]
    obj.mesh_poses = [pose]
    return obj


# ---------------------------------------------------------------------------
# Node
# ---------------------------------------------------------------------------

class CoffeeCellEnvironment(Node):

    def __init__(self):
        super().__init__("coffee_cell_environment")

        # Declare parameters for object positions (defaults)
        self.declare_parameter('grinder_x', 0.000)
        self.declare_parameter('grinder_y', -0.300)
        self.declare_parameter('grinder_z', 0.010)
        
        self.declare_parameter('coffee_machine_x', 0.419)
        self.declare_parameter('coffee_machine_y', -0.316)
        self.declare_parameter('coffee_machine_z', 0.010)
        
        self.declare_parameter('tool_station_x', -0.670)
        self.declare_parameter('tool_station_y', -0.300)
        self.declare_parameter('tool_station_z', 0.210)
        
        self.declare_parameter('cup_holder_x', -0.469)
        self.declare_parameter('cup_holder_y', -0.351)
        self.declare_parameter('cup_holder_z', 0.210)
        
        self.declare_parameter('coffee_cup_x', 0.700)
        self.declare_parameter('coffee_cup_y', -0.300)
        self.declare_parameter('coffee_cup_z', _table_surface_z + 0.7)

        # Latched publisher
        latch_qos = QoSProfile(
            depth=1,
            durability=DurabilityPolicy.TRANSIENT_LOCAL,
        )

        self._scene_pub = self.create_publisher(
            PlanningScene,
            "/planning_scene",
            latch_qos,
        )

        # Publish initial scene after delay
        self._timer = self.create_timer(2.0, self._initial_publish)
        
        # Set up parameter callback for live updates
        self.add_on_set_parameters_callback(self._parameter_callback)
        
        self.get_logger().info("CoffeeCellEnvironment node started will publish in 2 s")

    def _initial_publish(self):
        """Initial scene publish"""
        self._timer.cancel()
        self._publish_environment()
        
        # Set up periodic republish to catch parameter updates
        self._update_timer = self.create_timer(0.5, self._publish_environment)

    def _parameter_callback(self, params):
        """Called when parameters are updated"""
        # Republish scene whenever parameters change
        self._publish_environment()
        return SetParametersResult(successful=True)

    def _publish_environment(self):
        """Build all collision objects and send them in one PlanningScene msg."""
        
        # Read current parameter values
        grinder_x = self.get_parameter('grinder_x').value
        grinder_y = self.get_parameter('grinder_y').value
        grinder_z = self.get_parameter('grinder_z').value
        
        coffee_machine_x = self.get_parameter('coffee_machine_x').value
        coffee_machine_y = self.get_parameter('coffee_machine_y').value
        coffee_machine_z = self.get_parameter('coffee_machine_z').value
        
        tool_station_x = self.get_parameter('tool_station_x').value
        tool_station_y = self.get_parameter('tool_station_y').value
        tool_station_z = self.get_parameter('tool_station_z').value
        
        cup_holder_x = self.get_parameter('cup_holder_x').value
        cup_holder_y = self.get_parameter('cup_holder_y').value
        cup_holder_z = self.get_parameter('cup_holder_z').value
        
        coffee_cup_x = self.get_parameter('coffee_cup_x').value
        coffee_cup_y = self.get_parameter('coffee_cup_y').value
        coffee_cup_z = self.get_parameter('coffee_cup_z').value

        w  = CELL["width"]
        d  = CELL["depth"]
        h  = CELL["height"]
        t  = CELL["wall_t"]
        hw = w / 2.0
        hd = d / 2.0

        wall_cz = FLOOR_Z + h / 2.0

        objects: list[CollisionObject] = []

        # ── Walls ──────────────────────────────────────────────────────
        objects.append(box_object(
            "wall_front", FRAME_ID,
            sx=w, sy=t, sz=h,
            px=0.0, py=hd + t / 2, pz=wall_cz,
        ))

        objects.append(box_object(
            "wall_left", FRAME_ID,
            sx=t, sy=d, sz=h,
            px=-(hw + t / 2), py=0.0, pz=wall_cz,
        ))

        objects.append(box_object(
            "wall_right", FRAME_ID,
            sx=t, sy=d, sz=h,
            px=hw + t / 2, py=0.0, pz=wall_cz,
        ))

        # ── Ceiling ────────────────────────────────────────────────────
        ceiling_z = FLOOR_Z + h + t / 2
        objects.append(box_object(
            "ceiling", FRAME_ID,
            sx=w, sy=d, sz=t,
            px=0.0, py=0.0, pz=ceiling_z,
        ))

        # ── Welding table ──────────────────────────────────────────────
        objects.append(box_object(
            "welding_table", FRAME_ID,
            sx=TABLE["size_x"], sy=TABLE["size_y"], sz=TABLE["size_z"],
            px=0.0, py=0.0, pz=TABLE["cz"],
        ))

        # ── Coffee cup (dynamic position from parameters) ──────────────
        objects.append(mesh_object(
            "object", FRAME_ID,
            stl_path="/home/vasee22/igus-coffee-moveit/src/igus_rebel_ros2/igus_rebel_description/meshes/coffee_cup.stl",
            px=coffee_cup_x,
            py=coffee_cup_y,
            pz=coffee_cup_z,
            qx=0.0, qy=0.0, qz=0.0, qw=1.0,
        ))

        # ── No-go zone ─────────────────────────────────────────────────
        ngz = NO_GO_ZONE
        objects.append(box_object(
            "no_go_zone", FRAME_ID,
            sx=ngz["size_x"], sy=ngz["size_y"], sz=ngz["size_z"],
            px=ngz["x"], py=ngz["y"], pz=ngz["z"],
        ))

        # ── Dynamic objects (from parameters) ─────────────────────────
        objects.append(mesh_object(
            "grinder", FRAME_ID,
            stl_path="/home/vasee22/igus-coffee-moveit/src/igus_rebel_ros2/igus_rebel_description/meshes/Coffee Grinder.stl",
            px=grinder_x,
            py=grinder_y,
            pz=grinder_z,
            qx=0.0, qy=0.0, qz=1.0, qw=0.0,
            scale=0.001,
        ))

        objects.append(mesh_object(
            "coffee_machine", FRAME_ID,
            stl_path="/home/vasee22/igus-coffee-moveit/src/igus_rebel_ros2/igus_rebel_description/meshes/CoffeeMachine.stl",
            px=coffee_machine_x,
            py=coffee_machine_y,
            pz=coffee_machine_z,
            qx=0.0, qy=0.0, qz=0.0, qw=1.0,
            scale=0.001,
        ))

        objects.append(mesh_object(
            "tool_station", FRAME_ID,
            stl_path="/home/vasee22/igus-coffee-moveit/src/igus_rebel_ros2/igus_rebel_description/meshes/Tool Station.stl",
            px=tool_station_x,
            py=tool_station_y,
            pz=tool_station_z,
            qx=0.0, qy=0.0, qz=0.7071, qw=0.7071,
            scale=0.001,
        ))

        objects.append(mesh_object(
            "cup_holder", FRAME_ID,
            stl_path="/home/vasee22/igus-coffee-moveit/src/igus_rebel_ros2/igus_rebel_description/meshes/CoffeeCupHolder.stl",
            px=cup_holder_x,
            py=cup_holder_y,
            pz=cup_holder_z,
            qx=0.0, qy=0.0, qz=-0.7071, qw=0.7071,
            scale=0.001,
        ))

        # ── Colours ────────────────────────────────────────────────────
        colors = [
            self._make_color("wall_front",     0.7, 0.7, 0.7, 0.4),
            self._make_color("wall_left",      0.7, 0.7, 0.7, 0.4),
            self._make_color("wall_right",     0.7, 0.7, 0.7, 0.4),
            self._make_color("ceiling",        0.8, 0.8, 0.9, 0.3),
            self._make_color("welding_table",  0.3, 0.3, 0.35, 0.9),
            self._make_color("object",         0.9, 0.7, 0.3, 1.0),
            self._make_color("no_go_zone",     0.1, 0.6, 0.7, 0.5),
            self._make_color("grinder",        0.3, 0.8, 0.9, 1.0),
            self._make_color("coffee_machine", 0.2, 0.6, 0.2, 1.0),
            self._make_color("tool_station",   0.7, 0.1, 0.8, 1.0),
            self._make_color("cup_holder",     0.1, 0.1, 0.1, 0.5 )
        ]

        # ── Pack into PlanningScene ────────────────────────────────────
        scene_msg = PlanningScene()
        scene_msg.is_diff = True
        scene_msg.world.collision_objects = objects
        scene_msg.object_colors = colors

        self._scene_pub.publish(scene_msg)

    @staticmethod
    def _make_color(object_id: str, r: float, g: float, b: float,
                    a: float = 0.5) -> ObjectColor:
        oc = ObjectColor()
        oc.id = object_id
        oc.color = rgba(r, g, b, a)
        return oc


# ---------------------------------------------------------------------------

def main(args=None):
    rclpy.init(args=args)
    node = CoffeeCellEnvironment()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()