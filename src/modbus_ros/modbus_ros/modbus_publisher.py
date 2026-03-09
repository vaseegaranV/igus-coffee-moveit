import rclpy
from rclpy.node import Node
from sensor_msgs.msg import JointState
from pymodbus.client.sync import ModbusTcpClient

class JointStateUpdater(Node):
    def __init__(self):
        super().__init__("joint_state_updater")

        # Modbus client setup
        self.client = ModbusTcpClient("192.168.3.2", port=503) # port 503 is the one that should be used for igus rail # Change between 503 and 502 when receiving socket error
        
        if not self.client.connect():
            self.get_logger().fatal("Cannot connect to Modbus server")
            raise RuntimeError("Modbus connection failed")
        
        # ROS 2 subscribers & publishers
        self.subscription = self.create_subscription(
            JointState, "/joint_states", self.joint_state_callback, 10)
        self.publisher = self.create_publisher(JointState, "/joint_states_with_rail", 10)

    def joint_state_callback(self, msg):
        """Callback function that modifies and republishes the joint states."""
        if not self.client.is_socket_open() and not self.client.connect():
            self.get_logger().error("Modbus reconnect failed")
            return
        
        # Read the Modbus register
        response = self.client.read_holding_registers(23, 1)
        if response.isError():
            self.get_logger().error("Error reading Modbus register")
            return

        raw_modbus_value = response.registers[0]

        # Normalize to range [0.00, 1.00]
        modbus_value = 1.0 - ((raw_modbus_value - 9) / (109 - 9))
        modbus_value = max(0.0, min(1.0, modbus_value))  # Ensure it's within bounds


        # self.get_logger().info(f"Modbus value: {modbus_value}")

        # Modify the first position in the joint states
        if len(msg.position) > 0:
            # msg.position = list(msg.position)  # Convert tuple to list (if needed)
            msg.position[0] = float(modbus_value)  # Update the first joint position
            self.publisher.publish(msg)
            # self.get_logger().info(f"Updated joint position: {msg.position}")

    def destroy_node(self):
        """Shutdown node and close Modbus connection."""
        self.client.close()
        super().destroy_node()

def main(args=None):
    rclpy.init(args=args)
    node = JointStateUpdater()
    try:
        rclpy.spin(node)
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == "__main__":
    main()
