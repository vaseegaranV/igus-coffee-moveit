# COAR-ROS2-Workspace
This is the ROS2 Jazzy workspace for Cobot-On-A-Rail project to assess the security of Digital Twins

# Running the igus Coffee Cell System

## Step 1: Build and Source the Workspace
Open a terminal and run:
```bash
cd ~/igus-coffee-moveit
colcon build
source install/setup.bash
```

## Step 2: Launch the Environment
In the same terminal, launch MoveIt, Gazebo, and RViz:
```bash
ros2 launch igus_rebel_moveit_config environment.launch.py
```
**Leave this terminal running!**

## Step 3: Run the Pick-and-Place Program
Open a **new terminal** and run:
```bash
cd ~/igus-coffee-moveit
source install/setup.bash
ros2 launch igus_rebel pick_and_place.launch.py
```

The robot will now execute:
1. Pick cup holder from tool station (with twist lock)
2. Pick coffee cup using the attached cup holder

---

## Optional: Position Adjuster

To adjust object positions interactively, uncomment the second-to-last line in `environment.launch.py`:

```python
coffee_cell_env_process,  # Uncomment this line
```
```bash
cd ~/igus-coffee-moveit/src/igus_rebel_ros2/igus_rebel_description/scripts
python3 position_adjuster.py
```

Then relaunch the environment.
