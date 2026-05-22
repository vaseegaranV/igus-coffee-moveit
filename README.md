# igus-coffee-moveit
 
Autonomous coffee-making pipeline for the **igus ReBeL 6-DOF collaborative robot arm**, built using ROS 2 Jazzy, MoveIt 2, and MoveIt Task Constructor.
 
This repository contains the full simulation environment, motion planning pipeline, and task implementation for a coffee-making robotic cell developed as part of the ELE322 final-year group design project at the University of Sheffield, in collaboration with the AMRC and Knox Thomas.
 
---
 
## Project Overview
 
The system automates the full coffee-making process — picking up tools, operating an espresso machine and coffee grinder, tamping coffee, delivering a finished cup, and disposing of grounds — using a single 6-DOF cobot. The software pipeline is built around **MoveIt Task Constructor (MTC)**, which decomposes each manipulation operation into typed planning stages (generators, connectors, propagators, and modifiers).
 
The architecture supports both simulated execution in Gazebo and deployment on the real igus ReBeL hardware via the `hardware_protocol` flag, with no code changes required to switch between targets.
 
---
 
## Features
 
- **23-task coffee-making pipeline** implemented as independent MTC tasks
- **Bayonet twist-lock end effector** for passive tool switching between cup holder and portafilter holder
- **RRTConnect** sampling-based motion planning for free-space transitions
- **Cartesian path planner** for precise straight-line insertions and retreats
- **KDL inverse kinematics** with up to 8 solutions per planning request
- **Per-stage collision context** allowing collision permissions to be scoped to individual stages
- **Sim-to-real architecture** via ros2_control hardware abstraction
- **Full Gazebo physics simulation** with STL mesh collision objects for all coffee cell components
- **RViz integration** with MTC stage introspection for real-time debugging
---
 
## Requirements
 
### System
- Ubuntu 24.04 LTS (native or WSL2)
- ROS 2 Jazzy Jalisco
- MoveIt 2 (Jazzy distribution)
- MoveIt Task Constructor
- Gazebo (Harmonic)
- gz_ros2_control plugin
### Build tools
- colcon
- CMake ≥ 3.16
- C++17 compiler
### Hardware (for real robot operation)
- igus ReBeL 6-DOF cobot
- igus Robot Control (IRC) software (Windows)
- Static IP configuration `192.168.3.102` / `255.255.255.0`
---
 
## Installation
 
### 1. Install ROS 2 Jazzy
Follow the official guide at [docs.ros.org](https://docs.ros.org/en/jazzy/Installation.html).
 
### 2. Install MoveIt 2 and dependencies
```bash
sudo apt update
sudo apt install ros-jazzy-moveit
sudo apt install ros-jazzy-moveit-task-constructor
sudo apt install ros-jazzy-gz-ros2-control
sudo apt install ros-jazzy-ros-gz
```
 
### 3. Clone the repository
```bash
cd ~
git clone https://github.com/vaseegaranV/igus-coffee-moveit.git
cd igus-coffee-moveit
```
 
### 4. Build the workspace
```bash
colcon build --symlink-install
source install/setup.bash
```
 
For convenience, add the source line to your `.bashrc`:
```bash
echo "source ~/igus-coffee-moveit/install/setup.bash" >> ~/.bashrc
```
 
---
 
## Running the Simulation
 
The system uses a two-launch-file architecture so the simulation environment can stay running while the task pipeline is iterated.
 
### Terminal 1 — launch the simulation environment
```bash
ros2 launch igus_rebel environment.launch.py
```
This starts Gazebo with the coffee cell world, spawns the igus ReBeL robot, loads ros2_control with the joint trajectory controller, and opens RViz with the MoveIt plugin configured.
 
### Terminal 2 — run the task pipeline
```bash
ros2 launch igus_rebel main.launch.py
```
This launches the manipulation node which executes the 23-task `doTask()` sequence.
 
---
 
## Running on the Real Robot
 
### Prerequisites
1. igus ReBeL connected via Ethernet
2. Static IP configured (`192.168.3.102` / `255.255.255.0`)
3. igus Robot Control (IRC) software running on Windows and connected to the robot
### Launch sequence
```bash
# Terminal 1
ros2 launch igus_rebel rebel.launch.py hardware_protocol:=rebel
 
# Terminal 2
ros2 launch igus_rebel environment.launch.py
 
# Terminal 3
ros2 launch igus_rebel main.launch.py
```
 
The `hardware_protocol:=rebel` argument switches the ros2_control hardware interface from `gz_ros2_control` to the real igus controller via Ethernet.
 
---
 
## Repository Structure
 
```
igus-coffee-moveit/
└── src/igus_rebel_ros2/igus_rebel/
    ├── src/
    │   ├── main.cpp                       # main() + doTask() sequence
    │   ├── setup_environment.cpp          # planning scene + collision objects
    │   └── tasks/
    │       ├── task_pick_cup_holder.cpp
    │       ├── task_pick_portafilter.cpp
    │       ├── task_pick_cup.cpp
    │       ├── task_place_cup_holder.cpp
    │       ├── task_place_portafilter.cpp
    │       ├── task_place_cup_delivery_station.cpp
    │       ├── task_insert_portafilter_grinder.cpp
    │       ├── task_attach_portafilter_grinder.cpp
    │       ├── task_detach_portafilter_grinder.cpp
    │       ├── task_insert_cup_coffee_machine.cpp
    │       ├── task_pick_cup_coffee_machine.cpp
    │       ├── task_press_left_coffee_machine.cpp
    │       ├── task_press_middle_coffee_machine.cpp
    │       ├── task_press_grinder.cpp
    │       ├── task_tamp_portafilter.cpp
    │       ├── task_clean_portafilter.cpp
    │       ├── task_dispose_portafilter_bin.cpp
    │       └── task_go_home.cpp
    ├── include/igus_rebel/
    │   └── simple_task.hpp                # class declarations
    ├── launch/
    │   ├── environment.launch.py          # Gazebo + RViz + ros2_control
    │   └── main.launch.py                 # manipulation node
    ├── config/
    │   ├── igus_rebel2.srdf
    │   ├── joint_limits.yaml
    │   └── moveit_controllers.yaml
    ├── urdf/
    │   └── igus_rebel2.urdf
    ├── meshes/                            # STL collision meshes
    └── CMakeLists.txt
```
 
---
 
## Task Pipeline
 
The `doTask()` function in `main.cpp` executes 23 tasks in sequence:
 
| # | Task | Description |
|---|------|-------------|
| 1 | Press Left Button (On) | Turns the coffee machine on |
| 2 | Pick Portafilter | Picks the portafilter from the tool station |
| 3 | Go Home | Returns to home pose |
| 4 | Insert Portafilter Grinder | Inserts portafilter into grinder |
| 5 | Detach Portafilter Grinder | Releases portafilter from gripper |
| 6 | Press Grinder Power | Activates the coffee grinder |
| 7 | Attach Portafilter Grinder | Re-grasps the portafilter |
| 8 | Tamp Portafilter | Tamps the ground coffee |
| 9 | Insert Portafilter Coffee Machine | Locks portafilter into espresso machine |
| 10 | Pick Cup Holder | Picks the cup holder from tool station |
| 11 | Go Home | Returns to home pose |
| 12 | Pick Cup | Picks the coffee cup |
| 13 | Move to Coffee Machine | Places cup under the group head |
| 14 | Press Middle Button | Starts the brew cycle |
| 15 | Pick Cup From Machine | Retrieves the filled cup |
| 16 | Move to Delivery Station | Delivers the cup |
| 17 | Go Home | Returns to home pose |
| 18 | Place Cup Holder | Returns the cup holder |
| 19 | Press Left Button (Off) | Turns the coffee machine off |
| 20 | Attach Portafilter From Coffee Machine | Picks portafilter back up |
| 21 | Bin Dispose | Discards used grounds |
| 22 | Clean Brush | Cleans the portafilter |
| 23 | Place Portafilter | Returns the portafilter |
 
---
 
## Software Architecture
 
The pipeline is organised into three layers:
 
1. **Task layer** — MoveIt Task Constructor decomposes each operation into typed stages with per-stage collision context.
2. **Planning layer** — RRTConnect for free-space joint-space planning, the Cartesian planner for straight-line motions, and KDL for inverse kinematics.
3. **Execution layer** — ros2_control with `JointTrajectoryController` interpolates trajectories at the controller update rate and forwards position commands to either Gazebo or the real igus ReBeL via the `hardware_protocol` flag.

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
