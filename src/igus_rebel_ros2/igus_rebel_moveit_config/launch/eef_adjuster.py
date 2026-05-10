#!/usr/bin/env python3
"""
End Effector Pose Adjuster - Keyboard control to move gripper_link via MoveIt

Controls:
    Arrow keys: Move in X/Y plane (world frame)
    u/j: Move up/down in Z (world frame)
    +/-: Increase/decrease step size
    p: Print current end effector pose
    q: Quit
"""

import rclpy
from rclpy.node import Node
from geometry_msgs.msg import PoseStamped
from moveit_msgs.action import MoveGroup
from moveit_msgs.msg import MotionPlanRequest, WorkspaceParameters, Constraints, PositionConstraint, OrientationConstraint, RobotState
from rclpy.action import ActionClient
import sys
import termios
import tty
import select
import tf2_ros
import rclpy.time


class EEFAdjuster(Node):
    def __init__(self):
        super().__init__('eef_adjuster')

        self.tf_buffer = tf2_ros.Buffer()
        self.tf_listener = tf2_ros.TransformListener(self.tf_buffer, self)

        self.action_client = ActionClient(self, MoveGroup, '/move_action')

        self.step = 0.01
        self.group_name = "igus_rebel_arm"
        self.eef_frame = "gripper_link"
        self.base_frame = "base_link"

        self.get_logger().info("Waiting for MoveGroup action server...")
        self.action_client.wait_for_server()
        self.get_logger().info("Connected! Ready for keyboard input.")

    def get_current_pose(self):
        try:
            transform = self.tf_buffer.lookup_transform(
                self.base_frame,
                self.eef_frame,
                rclpy.time.Time(),
                timeout=rclpy.duration.Duration(seconds=1.0)
            )
            return transform.transform
        except Exception as e:
            self.get_logger().error(f"Failed to get transform: {e}")
            return None

    def move_to_pose(self, x, y, z, qx, qy, qz, qw):
        goal_msg = MoveGroup.Goal()

        goal_msg.request.group_name = self.group_name
        goal_msg.request.num_planning_attempts = 5
        goal_msg.request.allowed_planning_time = 5.0
        goal_msg.request.max_velocity_scaling_factor = 0.1
        goal_msg.request.max_acceleration_scaling_factor = 0.1

        target_pose = PoseStamped()
        target_pose.header.frame_id = self.base_frame
        target_pose.header.stamp = self.get_clock().now().to_msg()
        target_pose.pose.position.x = x
        target_pose.pose.position.y = y
        target_pose.pose.position.z = z
        target_pose.pose.orientation.x = qx
        target_pose.pose.orientation.y = qy
        target_pose.pose.orientation.z = qz
        target_pose.pose.orientation.w = qw

        # Position constraint
        pos_constraint = PositionConstraint()
        pos_constraint.header = target_pose.header
        pos_constraint.link_name = self.eef_frame
        pos_constraint.target_point_offset.x = 0.0
        pos_constraint.target_point_offset.y = 0.0
        pos_constraint.target_point_offset.z = 0.0
        from shape_msgs.msg import SolidPrimitive
        sphere = SolidPrimitive()
        sphere.type = SolidPrimitive.SPHERE
        sphere.dimensions = [0.001]
        from geometry_msgs.msg import Pose
        sphere_pose = Pose()
        sphere_pose.position = target_pose.pose.position
        sphere_pose.orientation.w = 1.0
        pos_constraint.constraint_region.primitives.append(sphere)
        pos_constraint.constraint_region.primitive_poses.append(sphere_pose)
        pos_constraint.weight = 1.0

        # Orientation constraint
        ori_constraint = OrientationConstraint()
        ori_constraint.header = target_pose.header
        ori_constraint.link_name = self.eef_frame
        ori_constraint.orientation = target_pose.pose.orientation
        ori_constraint.absolute_x_axis_tolerance = 0.01
        ori_constraint.absolute_y_axis_tolerance = 0.01
        ori_constraint.absolute_z_axis_tolerance = 0.01
        ori_constraint.weight = 1.0

        constraints = Constraints()
        constraints.position_constraints.append(pos_constraint)
        constraints.orientation_constraints.append(ori_constraint)
        goal_msg.request.goal_constraints.append(constraints)

        future = self.action_client.send_goal_async(goal_msg)
        rclpy.spin_until_future_complete(self, future, timeout_sec=2.0)
        goal_handle = future.result()

        if not goal_handle or not goal_handle.accepted:
            self.get_logger().warn("Goal rejected")
            return False

        result_future = goal_handle.get_result_async()
        rclpy.spin_until_future_complete(self, result_future, timeout_sec=10.0)
        return True

    def print_pose(self, transform=None):
        if transform is None:
            transform = self.get_current_pose()
        if transform is None:
            return
        t = transform.translation
        r = transform.rotation
        print(f"\r[gripper_link] x={t.x:7.3f} y={t.y:7.3f} z={t.z:7.3f} | "
              f"qx={r.x:6.3f} qy={r.y:6.3f} qz={r.z:6.3f} qw={r.w:6.3f} | step={self.step:.3f}m    ",
              end='', flush=True)

    def run_keyboard_loop(self):
        fd = sys.stdin.fileno()
        old_settings = termios.tcgetattr(fd)

        print("\n" + "="*70)
        print("END EFFECTOR POSE ADJUSTER")
        print("="*70)
        print("Move:  ← → (Y)   ↑ ↓ (X)   u/j (Z up/down)")
        print("Step:  + (bigger)   - (smaller)")
        print("Other: p (print pose)   q (quit)")
        print("="*70)
        self.print_pose()

        try:
            tty.setraw(fd)
            while rclpy.ok():
                if select.select([sys.stdin], [], [], 0.1)[0]:
                    ch = sys.stdin.read(1)

                    if ch == 'q':
                        break

                    # Get current pose before moving
                    transform = self.get_current_pose()
                    if transform is None:
                        continue

                    t = transform.translation
                    r = transform.rotation
                    x, y, z = t.x, t.y, t.z
                    qx, qy, qz, qw = r.x, r.y, r.z, r.w

                    moved = False

                    if ch == '\x1b':
                        next1 = sys.stdin.read(1)
                        if next1 == '[':
                            next2 = sys.stdin.read(1)
                            if next2 == 'A':    # Up arrow → +X
                                x += self.step; moved = True
                            elif next2 == 'B':  # Down arrow → -X
                                x -= self.step; moved = True
                            elif next2 == 'C':  # Right arrow → +Y
                                y += self.step; moved = True
                            elif next2 == 'D':  # Left arrow → -Y
                                y -= self.step; moved = True
                    elif ch == 'u':
                        z += self.step; moved = True
                    elif ch == 'j':
                        z -= self.step; moved = True
                    elif ch == '+' or ch == '=':
                        self.step = min(self.step * 2, 0.5)
                        print(f"\rStep size: {self.step:.3f}m" + " "*60, end='', flush=True)
                    elif ch == '-' or ch == '_':
                        self.step = max(self.step / 2, 0.001)
                        print(f"\rStep size: {self.step:.3f}m" + " "*60, end='', flush=True)
                    elif ch == 'p':
                        print()
                        print(f"\n  position:    x={x:.4f}  y={y:.4f}  z={z:.4f}")
                        print(f"  orientation: qx={qx:.4f}  qy={qy:.4f}  qz={qz:.4f}  qw={qw:.4f}")
                        print()

                    if moved:
                        self.move_to_pose(x, y, z, qx, qy, qz, qw)
                        self.print_pose()

        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
            print("\n")
            transform = self.get_current_pose()
            if transform:
                t = transform.translation
                r = transform.rotation
                print("\nFINAL POSE:")
                print(f"  position:    x={t.x:.4f}  y={t.y:.4f}  z={t.z:.4f}")
                print(f"  orientation: qx={r.x:.4f}  qy={r.y:.4f}  qz={r.z:.4f}  qw={r.w:.4f}")


def main(args=None):
    rclpy.init(args=args)
    node = EEFAdjuster()

    try:
        node.run_keyboard_loop()
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()