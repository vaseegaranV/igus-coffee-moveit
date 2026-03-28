#!/usr/bin/env python3
"""
coffee_cell_environment.py

Publishes collision objects to the MoveIt2 Planning Scene:
  - 3 cell walls (back + left + right — front/operator face is open)
  - 1 ceiling panel
  - 1 welding table top (2000×1000×100mm, sitting on the floor inside the cell)
  - 1 coffee machine placeholder block (on the table surface)

Real-world dimensions taken from:
  Cell drawing (KJN job 74942):  2000mm W × 1000mm D × 1587mm H
  Frame profile:                 45×45mm aluminium throughout
  Welding table:                 2000mm × 1000mm × 100mm plasma nitrided top

Z coordinate convention (matches physical cell):
  Z = 0.000  →  floor / base of cell walls
  Z = 0.100  →  top of welding table = robot base mounting plane
  Z = 1.587  →  top of cell (ceiling underside)

The cell walls sit on the floor.  The welding table sits inside the cell
on the floor.  The robot URDF origin (Z=0 in world frame) should be set
to the table surface, i.e. 0.100m above the floor.  If your URDF places
the robot base at the world origin (0,0,0) you may need to add a static
transform: floor → robot_base  with  z = 0.100.

Usage (after sourcing ROS 2 + workspace):
    python3 coffee_cell_environment.py
"""

import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, DurabilityPolicy

from geometry_msgs.msg import Pose, Point, Quaternion
from shape_msgs.msg import SolidPrimitive
from moveit_msgs.msg import CollisionObject, PlanningScene
from std_msgs.msg import Header, ColorRGBA
from moveit_msgs.msg import ObjectColor


# ---------------------------------------------------------------------------
# Dimensions — all in metres
# ---------------------------------------------------------------------------

# Cell enclosure (from PDF drawing, job 74942)
CELL = {
    "width":  2.000,   # X — left / right  (2000mm)
    "depth":  1.000,   # Y — back to open front  (1000mm)
    "height": 1.587,   # Z — floor to ceiling  (1587mm)
    "wall_t": 0.045,   # aluminium profile section  (45mm)
}

# The rail (igus_7th_axis) sits at Z=0 in the world frame per /tf_static.
# The physical rail + base plate sits on the welding table surface.
# We estimate the rail+base assembly is ~120mm tall, so the table surface
# is at Z = -0.120 and the floor is at Z = -0.220 (table top - table thickness).
#
# Tweak FLOOR_Z if the floor doesn't visually align in RViz — move it in
# steps of 0.01 until it sits flush with the bottom of the rail.
RAIL_BASE_Z  = 0.0     # world Z of the igus_7th_axis frame (from /tf_static)
RAIL_HEIGHT  = 0.120   # estimated rail + base plate height (m) — adjust if needed

TABLE = {
    "size_x": 2.000,
    "size_y": 1.000,
    "size_z": 0.100,   # 100mm thick welding table top
}
# Table top surface sits just below the rail base
TABLE["cz"] = RAIL_BASE_Z - RAIL_HEIGHT - TABLE["size_z"] / 2  # = -0.170

# Floor sits on the underside of the table
FLOOR_Z = RAIL_BASE_Z - RAIL_HEIGHT - TABLE["size_z"]  # = -0.220

# Coffee machine placeholder — sits on the table surface
_table_surface_z = RAIL_BASE_Z - RAIL_HEIGHT  # = -0.120
COFFEE_MACHINE = {
    "size_x": 0.350,
    "size_y": 0.300,
    "size_z": 0.450,
    "x":  0.700,
    "y": -0.300,                              # towards back wall
    "z":  _table_surface_z + 0.450 / 2,      # base sits on table surface
}

FRAME_ID = "world"   # change to "base_link" if that is your fixed frame


# ---------------------------------------------------------------------------
# Helper
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
    box.dimensions = [sx, sy, sz]  # [X, Y, Z]

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


# ---------------------------------------------------------------------------
# Node
# ---------------------------------------------------------------------------

class CoffeeCellEnvironment(Node):

    def __init__(self):
        super().__init__("coffee_cell_environment")

        # Latched publisher so RViz / move_group pick it up even if they start later
        latch_qos = QoSProfile(
            depth=1,
            durability=DurabilityPolicy.TRANSIENT_LOCAL,
        )

        self._scene_pub = self.create_publisher(
            PlanningScene,
            "/planning_scene",
            latch_qos,
        )

        # Small delay then publish once (move_group must be up first)
        self._timer = self.create_timer(2.0, self._publish_environment)
        self.get_logger().info("CoffeeCellEnvironment node started – will publish in 2 s")

    # ------------------------------------------------------------------
    def _publish_environment(self):
        """Build all collision objects and send them in one PlanningScene msg."""
        self._timer.cancel()   # fire only once

        w  = CELL["width"]    # 2.000 m
        d  = CELL["depth"]    # 1.000 m
        h  = CELL["height"]   # 1.587 m
        t  = CELL["wall_t"]   # 0.045 m  (45mm profile)
        hw = w / 2.0          # 1.000 m
        hd = d / 2.0          # 0.500 m

        # Cell walls rise from the floor upward
        # Centre Z = FLOOR_Z + h/2
        wall_cz = FLOOR_Z + h / 2.0

        objects: list[CollisionObject] = []

        # ── Walls (back/−Y face omitted — open side) ───────────────────

        # Front wall  (+Y face)
        objects.append(box_object(
            "wall_front", FRAME_ID,
            sx=w, sy=t, sz=h,
            px=0.0, py=hd + t / 2, pz=wall_cz,
        ))

        # Left wall  (−X face)
        objects.append(box_object(
            "wall_left", FRAME_ID,
            sx=t, sy=d, sz=h,
            px=-(hw + t / 2), py=0.0, pz=wall_cz,
        ))

        # Right wall  (+X face)
        objects.append(box_object(
            "wall_right", FRAME_ID,
            sx=t, sy=d, sz=h,
            px=hw + t / 2, py=0.0, pz=wall_cz,
        ))

        # ── Ceiling ────────────────────────────────────────────────────
        # Top of cell walls = FLOOR_Z + h = h.  Ceiling panel centre = h + t/2
        ceiling_z = FLOOR_Z + h + t / 2
        objects.append(box_object(
            "ceiling", FRAME_ID,
            sx=w, sy=d, sz=t,
            px=0.0, py=0.0, pz=ceiling_z,
        ))

        # ── Welding table top ──────────────────────────────────────────
        # Sits on the floor inside the cell.
        # Floor = Z=0, table top surface = Z=0.100, centre = Z=0.050
        objects.append(box_object(
            "welding_table", FRAME_ID,
            sx=TABLE["size_x"], sy=TABLE["size_y"], sz=TABLE["size_z"],
            px=0.0, py=0.0, pz=TABLE["cz"],
        ))

        # ── Coffee machine placeholder ─────────────────────────────────
        # Sits on the table surface → base at Z=0.100, centre at Z=0.325
        cm = COFFEE_MACHINE
        objects.append(box_object(
            "coffee_machine", FRAME_ID,
            sx=cm["size_x"], sy=cm["size_y"], sz=cm["size_z"],
            px=cm["x"], py=cm["y"], pz=cm["z"],
        ))

        # ── Colours ────────────────────────────────────────────────────
        colors = [
            self._make_color("wall_front",     0.7, 0.7, 0.7, 0.4),
            self._make_color("wall_left",      0.7, 0.7, 0.7, 0.4),
            self._make_color("wall_right",     0.7, 0.7, 0.7, 0.4),
            self._make_color("ceiling",        0.8, 0.8, 0.9, 0.3),
            self._make_color("welding_table",  0.3, 0.3, 0.35, 0.9),
            self._make_color("coffee_machine", 0.2, 0.6, 0.2,  0.9),
        ]

        # ── Pack into PlanningScene ────────────────────────────────────
        scene_msg = PlanningScene()
        scene_msg.is_diff = True   # merge with existing scene
        scene_msg.world.collision_objects = objects
        scene_msg.object_colors = colors

        self._scene_pub.publish(scene_msg)
        self.get_logger().info(
            f"Published {len(objects)} collision objects to /planning_scene"
        )
        for obj in objects:
            p = obj.primitive_poses[0].position
            s = obj.primitives[0].dimensions
            self.get_logger().info(
                f"  [{obj.id}]  size=({s[0]:.2f}, {s[1]:.2f}, {s[2]:.2f})  "
                f"pos=({p.x:.2f}, {p.y:.2f}, {p.z:.2f})"
            )

    # ------------------------------------------------------------------
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