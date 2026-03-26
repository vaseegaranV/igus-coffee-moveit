import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/vasee22/COAR-ROS2-Workspace-mai/COAR-ROS2-Workspace-main/install/modbus_ros'
