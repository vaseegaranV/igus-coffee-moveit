#!/usr/bin/env python3
"""
Position Adjuster - Keyboard control to adjust object positions via ROS parameters

Controls:
    1-7: Select object (1=grinder, 2=coffee_machine, 3=tool_station, 4=cup_holder, 5=coffee_cup, 6=portafilter, 7=delivery_station)
    Arrow keys: Move in X/Y plane
    u/j: Move up/down in Z
    +/-: Increase/decrease step size
    r: Reset current object to starting position
    p: Print all current positions
    q: Quit and print final positions
"""

import rclpy
from rclpy.node import Node
from rcl_interfaces.msg import Parameter, ParameterValue, ParameterType
from rcl_interfaces.srv import SetParameters
import sys
import termios
import tty
import select


_table_surface_z = -0.120

INITIAL_POSITIONS = {
    'grinder':          {'x':  0.000, 'y': -0.300, 'z': 0.010},
    'coffee_machine':   {'x':  0.419, 'y': -0.316, 'z': 0.010},
    'tool_station':     {'x': -0.796, 'y': -0.278, 'z': 0.346},
    'cup_holder':       {'x': -0.473, 'y': -0.330, 'z': 0.348},
    'coffee_cup':       {'x':  0.700, 'y': -0.300, 'z': _table_surface_z + 0.7},
    'portafilter':      {'x': -0.800, 'y': -0.300, 'z': _table_surface_z + 0.7},
    'delivery_station': {'x': -0.800, 'y': -0.300, 'z': _table_surface_z + 0.7},
}


class PositionAdjuster(Node):
    def __init__(self):
        super().__init__('position_adjuster')
        
        self.positions = {}
        for name, data in INITIAL_POSITIONS.items():
            self.positions[name] = {'x': data['x'], 'y': data['y'], 'z': data['z']}
        
        self.current_obj = 'grinder'
        self.step = 0.01
        
        self.param_client = self.create_client(
            SetParameters,
            '/coffee_cell_environment/set_parameters'
        )
        
        self.get_logger().info("Waiting for coffee_cell_environment node...")
        while not self.param_client.wait_for_service(timeout_sec=1.0):
            self.get_logger().info("Waiting for /coffee_cell_environment/set_parameters service...")
        
        self.get_logger().info("Connected! Publishing initial positions...")
        self.publish_all_positions()
        self.get_logger().info("Ready for keyboard input!")
        
    def publish_all_positions(self):
        request = SetParameters.Request()
        
        for obj_name, pos in self.positions.items():
            for coord in ['x', 'y', 'z']:
                param = Parameter()
                param.name = f'{obj_name}_{coord}'
                param.value = ParameterValue()
                param.value.type = ParameterType.PARAMETER_DOUBLE
                param.value.double_value = pos[coord]
                request.parameters.append(param)
        
        future = self.param_client.call_async(request)
        rclpy.spin_until_future_complete(self, future, timeout_sec=1.0)
        
        if future.result() is None:
            self.get_logger().warn("Failed to set parameters")
    
    def move_current(self, dx=0.0, dy=0.0, dz=0.0):
        self.positions[self.current_obj]['x'] += dx
        self.positions[self.current_obj]['y'] += dy
        self.positions[self.current_obj]['z'] += dz
        
        request = SetParameters.Request()
        pos = self.positions[self.current_obj]
        
        for coord, value in [('x', pos['x']), ('y', pos['y']), ('z', pos['z'])]:
            param = Parameter()
            param.name = f'{self.current_obj}_{coord}'
            param.value = ParameterValue()
            param.value.type = ParameterType.PARAMETER_DOUBLE
            param.value.double_value = value
            request.parameters.append(param)
        
        future = self.param_client.call_async(request)
        rclpy.spin_until_future_complete(self, future, timeout_sec=0.5)
        self.print_current_position()
    
    def reset_current(self):
        init = INITIAL_POSITIONS[self.current_obj]
        self.positions[self.current_obj] = {'x': init['x'], 'y': init['y'], 'z': init['z']}
        
        request = SetParameters.Request()
        pos = self.positions[self.current_obj]
        
        for coord, value in [('x', pos['x']), ('y', pos['y']), ('z', pos['z'])]:
            param = Parameter()
            param.name = f'{self.current_obj}_{coord}'
            param.value = ParameterValue()
            param.value.type = ParameterType.PARAMETER_DOUBLE
            param.value.double_value = value
            request.parameters.append(param)
        
        future = self.param_client.call_async(request)
        rclpy.spin_until_future_complete(self, future, timeout_sec=0.5)
        
        self.get_logger().info(f"Reset {self.current_obj} to initial position")
        self.print_current_position()
    
    def print_current_position(self):
        pos = self.positions[self.current_obj]
        print(f"\r[{self.current_obj:20s}] x={pos['x']:7.3f} y={pos['y']:7.3f} z={pos['z']:7.3f} | step={self.step:.3f}m    ",
              end='', flush=True)
    
    def print_all_positions(self):
        print("\n\n" + "="*70)
        print("CURRENT POSITIONS:")
        print("="*70)
        for name in ['grinder', 'coffee_machine', 'tool_station', 'cup_holder', 'coffee_cup', 'portafilter', 'delivery_station']:
            pos = self.positions[name]
            print(f"{name:20s}: px={pos['x']:7.3f}, py={pos['y']:7.3f}, pz={pos['z']:7.3f}")
        print("="*70 + "\n")
    
    def run_keyboard_loop(self):
        fd = sys.stdin.fileno()
        old_settings = termios.tcgetattr(fd)
        
        print("\n" + "="*70)
        print("INTERACTIVE POSITION ADJUSTER")
        print("="*70)
        print("Objects: 1=grinder  2=coffee_machine  3=tool_station  4=cup_holder")
        print("         5=coffee_cup  6=portafilter  7=delivery_station")
        print("Move:    ← → ↑ ↓ (X/Y plane)    u/j (Z up/down)")
        print("Step:    + (bigger)  - (smaller)")
        print("Other:   r (reset)  p (print)  q (quit)")
        print("="*70)
        self.print_current_position()
        
        try:
            tty.setraw(fd)
            while rclpy.ok():
                if select.select([sys.stdin], [], [], 0.1)[0]:
                    ch = sys.stdin.read(1)
                    
                    if ch == 'q':
                        break
                    elif ch == '1':
                        self.current_obj = 'grinder'
                        self.print_current_position()
                    elif ch == '2':
                        self.current_obj = 'coffee_machine'
                        self.print_current_position()
                    elif ch == '3':
                        self.current_obj = 'tool_station'
                        self.print_current_position()
                    elif ch == '4':
                        self.current_obj = 'cup_holder'
                        self.print_current_position()
                    elif ch == '5':
                        self.current_obj = 'coffee_cup'
                        self.print_current_position()
                    elif ch == '6':
                        self.current_obj = 'portafilter'
                        self.print_current_position()
                    elif ch == '7':
                        self.current_obj = 'delivery_station'
                        self.print_current_position()
                    elif ch == '\x1b':
                        next1 = sys.stdin.read(1)
                        if next1 == '[':
                            next2 = sys.stdin.read(1)
                            if next2 == 'A':
                                self.move_current(dy=self.step)
                            elif next2 == 'B':
                                self.move_current(dy=-self.step)
                            elif next2 == 'C':
                                self.move_current(dx=self.step)
                            elif next2 == 'D':
                                self.move_current(dx=-self.step)
                    elif ch == 'u':
                        self.move_current(dz=self.step)
                    elif ch == 'j':
                        self.move_current(dz=-self.step)
                    elif ch == '+' or ch == '=':
                        self.step = min(self.step * 2, 0.5)
                        print(f"\rStep size: {self.step:.3f}m" + " "*50, end='', flush=True)
                    elif ch == '-' or ch == '_':
                        self.step = max(self.step / 2, 0.001)
                        print(f"\rStep size: {self.step:.3f}m" + " "*50, end='', flush=True)
                    elif ch == 'r':
                        self.reset_current()
                    elif ch == 'p':
                        self.print_all_positions()
                        self.print_current_position()
                        
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
            print("\n")
            self.print_all_positions()


def main(args=None):
    rclpy.init(args=args)
    node = PositionAdjuster()
    
    try:
        node.run_keyboard_loop()
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()