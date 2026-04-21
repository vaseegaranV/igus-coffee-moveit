#include "igus_rebel/simple_task.hpp"
#include <moveit/planning_scene_interface/planning_scene_interface.hpp>
#include <geometric_shapes/shapes.h>
#include <geometric_shapes/shape_operations.h>
#include <geometric_shapes/mesh_operations.h>

static const rclcpp::Logger LOGGER = rclcpp::get_logger("simple_moveto");

void SimpleTask::setupPlanningScene()  // Implementation
{
    RCLCPP_INFO(LOGGER, "Setting up planning scene...");
  
    moveit::planning_interface::PlanningSceneInterface psi;
    std::vector<moveit_msgs::msg::CollisionObject> collision_objects;
    std::vector<moveit_msgs::msg::ObjectColor> object_colors;
    
    // Constants from Python file
    const double RAIL_BASE_Z = 0.0;
    const double RAIL_HEIGHT = 0.120;
    const double TABLE_SIZE_Z = 0.100;
    const double FLOOR_Z = RAIL_BASE_Z - RAIL_HEIGHT - TABLE_SIZE_Z;
    const double _table_surface_z = RAIL_BASE_Z - RAIL_HEIGHT;
    
    const double CELL_WIDTH = 2.000;
    const double CELL_DEPTH = 1.000;
    const double CELL_HEIGHT = 1.587;
    const double CELL_WALL_T = 0.045;
    
    // ── Walls ──────────────────────────────────────────────────────────────
    {
        double hw = CELL_WIDTH / 2.0;
        double hd = CELL_DEPTH / 2.0;
        double wall_cz = FLOOR_Z + CELL_HEIGHT / 2.0;
        
        // Wall front
        moveit_msgs::msg::CollisionObject wall_front;
        wall_front.header.frame_id = "world";
        wall_front.id = "wall_front";
        
        shape_msgs::msg::SolidPrimitive primitive;
        primitive.type = primitive.BOX;
        primitive.dimensions = {CELL_WIDTH, CELL_WALL_T, CELL_HEIGHT};
        
        geometry_msgs::msg::Pose pose;
        pose.position.x = 0.0;
        pose.position.y = hd + CELL_WALL_T / 2;
        pose.position.z = wall_cz;
        pose.orientation.w = 1.0;
        
        wall_front.primitives.push_back(primitive);
        wall_front.primitive_poses.push_back(pose);
        wall_front.operation = wall_front.ADD;
        collision_objects.push_back(wall_front);
        
        moveit_msgs::msg::ObjectColor wall_front_color;
        wall_front_color.id = "wall_front";
        wall_front_color.color.r = 0.7;
        wall_front_color.color.g = 0.7;
        wall_front_color.color.b = 0.7;
        wall_front_color.color.a = 0.4;
        object_colors.push_back(wall_front_color);
        
        // Wall left
        moveit_msgs::msg::CollisionObject wall_left;
        wall_left.header.frame_id = "world";
        wall_left.id = "wall_left";
        
        primitive.dimensions = {CELL_WALL_T, CELL_DEPTH, CELL_HEIGHT};
        pose.position.x = -(hw + CELL_WALL_T / 2);
        pose.position.y = 0.0;
        pose.position.z = wall_cz;
        
        wall_left.primitives.push_back(primitive);
        wall_left.primitive_poses.push_back(pose);
        wall_left.operation = wall_left.ADD;
        collision_objects.push_back(wall_left);
        
        moveit_msgs::msg::ObjectColor wall_left_color;
        wall_left_color.id = "wall_left";
        wall_left_color.color.r = 0.7;
        wall_left_color.color.g = 0.7;
        wall_left_color.color.b = 0.7;
        wall_left_color.color.a = 0.4;
        object_colors.push_back(wall_left_color);
        
        // Wall right
        moveit_msgs::msg::CollisionObject wall_right;
        wall_right.header.frame_id = "world";
        wall_right.id = "wall_right";
        
        pose.position.x = hw + CELL_WALL_T / 2;
        
        wall_right.primitives.push_back(primitive);
        wall_right.primitive_poses.push_back(pose);
        wall_right.operation = wall_right.ADD;
        collision_objects.push_back(wall_right);
        
        moveit_msgs::msg::ObjectColor wall_right_color;
        wall_right_color.id = "wall_right";
        wall_right_color.color.r = 0.7;
        wall_right_color.color.g = 0.7;
        wall_right_color.color.b = 0.7;
        wall_right_color.color.a = 0.4;
        object_colors.push_back(wall_right_color);
    }
    
    // ── Ceiling ────────────────────────────────────────────────────────────
    {
        moveit_msgs::msg::CollisionObject ceiling;
        ceiling.header.frame_id = "world";
        ceiling.id = "ceiling";
        
        shape_msgs::msg::SolidPrimitive primitive;
        primitive.type = primitive.BOX;
        primitive.dimensions = {CELL_WIDTH, CELL_DEPTH, CELL_WALL_T};
        
        geometry_msgs::msg::Pose pose;
        pose.position.x = 0.0;
        pose.position.y = 0.0;
        pose.position.z = FLOOR_Z + CELL_HEIGHT + CELL_WALL_T / 2;
        pose.orientation.w = 1.0;
        
        ceiling.primitives.push_back(primitive);
        ceiling.primitive_poses.push_back(pose);
        ceiling.operation = ceiling.ADD;
        collision_objects.push_back(ceiling);
        
        moveit_msgs::msg::ObjectColor ceiling_color;
        ceiling_color.id = "ceiling";
        ceiling_color.color.r = 0.8;
        ceiling_color.color.g = 0.8;
        ceiling_color.color.b = 0.9;
        ceiling_color.color.a = 0.3;
        object_colors.push_back(ceiling_color);
    }
    
    // ── Welding table ──────────────────────────────────────────────────────
    {
        moveit_msgs::msg::CollisionObject table;
        table.header.frame_id = "world";
        table.id = "welding_table";
        
        shape_msgs::msg::SolidPrimitive primitive;
        primitive.type = primitive.BOX;
        primitive.dimensions = {2.000, 1.000, 0.100};
        
        geometry_msgs::msg::Pose pose;
        pose.position.x = 0.0;
        pose.position.y = 0.0;
        pose.position.z = RAIL_BASE_Z - RAIL_HEIGHT - TABLE_SIZE_Z / 2;
        pose.orientation.w = 1.0;
        
        table.primitives.push_back(primitive);
        table.primitive_poses.push_back(pose);
        table.operation = table.ADD;
        collision_objects.push_back(table);
        
        moveit_msgs::msg::ObjectColor table_color;
        table_color.id = "welding_table";
        table_color.color.r = 0.3;
        table_color.color.g = 0.3;
        table_color.color.b = 0.35;
        table_color.color.a = 0.9;
        object_colors.push_back(table_color);
    }
    
    // ── No-go zone ─────────────────────────────────────────────────────────
    {
        moveit_msgs::msg::CollisionObject no_go;
        no_go.header.frame_id = "world";
        no_go.id = "no_go_zone";
        
        shape_msgs::msg::SolidPrimitive primitive;
        primitive.type = primitive.BOX;
        primitive.dimensions = {2.00, 0.35, 0.13};
        
        geometry_msgs::msg::Pose pose;
        pose.position.x = 0.00;
        pose.position.y = -0.32;
        pose.position.z = _table_surface_z + 0.13 / 2;
        pose.orientation.w = 1.0;
        
        no_go.primitives.push_back(primitive);
        no_go.primitive_poses.push_back(pose);
        no_go.operation = no_go.ADD;
        collision_objects.push_back(no_go);
        
        moveit_msgs::msg::ObjectColor no_go_color;
        no_go_color.id = "no_go_zone";
        no_go_color.color.r = 0.1;
        no_go_color.color.g = 0.6;
        no_go_color.color.b = 0.7;
        no_go_color.color.a = 0.5;
        object_colors.push_back(no_go_color);
    }

    // ── Plate ─────────────────────────────────────────────────────────
    {
         moveit_msgs::msg::CollisionObject plate;
         plate.header.frame_id = "world";
         plate.id = "plate";
        
         shape_msgs::msg::SolidPrimitive primitive;
         primitive.type = primitive.CYLINDER;
         primitive.dimensions = {0.040, 0.10};
        
         geometry_msgs::msg::Pose pose;
         pose.position.x = 0.700;
         pose.position.y = -0.300;
         pose.position.z = _table_surface_z + 0.675;
         pose.orientation.w = 1.0;
        
         plate.primitives.push_back(primitive);
         plate.primitive_poses.push_back(pose);
         plate.operation = plate.ADD;
         collision_objects.push_back(plate);
        
         moveit_msgs::msg::ObjectColor plate_col;
         plate_col.id = "plate";
         plate_col.color.r = 0.1;
         plate_col.color.g = 0.6;
         plate_col.color.b = 0.7;
         plate_col.color.a = 0.5;
         object_colors.push_back(plate_col);
    }
    
    // ── Coffee cup (mesh) ──────────────────────────────────────────────────
    {
        moveit_msgs::msg::CollisionObject cup;
        cup.header.frame_id = "world";
        cup.id = "object";
        
        shapes::Mesh* mesh = shapes::createMeshFromResource(
            "file:///home/vasee22/igus-coffee-moveit/src/igus_rebel_ros2/igus_rebel_description/meshes/coffee_cup.stl");
        
        if (mesh)
        {
        shape_msgs::msg::Mesh mesh_msg;
        shapes::ShapeMsg mesh_msg_variant;
        shapes::constructMsgFromShape(mesh, mesh_msg_variant);
        mesh_msg = boost::get<shape_msgs::msg::Mesh>(mesh_msg_variant);
        
        geometry_msgs::msg::Pose pose;
        pose.position.x = 0.700;
        pose.position.y = -0.300;
        pose.position.z = _table_surface_z + 0.7;
        pose.orientation.w = 1.0;
        
        cup.meshes.push_back(mesh_msg);
        cup.mesh_poses.push_back(pose);
        cup.operation = cup.ADD;
        collision_objects.push_back(cup);
        
        moveit_msgs::msg::ObjectColor cup_color;
        cup_color.id = "object";
        cup_color.color.r = 0.2;
        cup_color.color.g = 0.7;
        cup_color.color.b = 0.9;
        cup_color.color.a = 1.0;
        object_colors.push_back(cup_color);
        
        delete mesh;
        }
    }
    
    // ── Grinder (mesh) ─────────────────────────────────────────────────────
    {
        moveit_msgs::msg::CollisionObject grinder;
        grinder.header.frame_id = "world";
        grinder.id = "grinder";
        
        shapes::Mesh* mesh = shapes::createMeshFromResource(
            "file:///home/vasee22/igus-coffee-moveit/src/igus_rebel_ros2/igus_rebel_description/meshes/Coffee Grinder.stl",
            Eigen::Vector3d(0.001, 0.001, 0.001));
        
        if (mesh)
        {
        shape_msgs::msg::Mesh mesh_msg;
        shapes::ShapeMsg mesh_msg_variant;
        shapes::constructMsgFromShape(mesh, mesh_msg_variant);
        mesh_msg = boost::get<shape_msgs::msg::Mesh>(mesh_msg_variant);
        
        geometry_msgs::msg::Pose pose;
        pose.position.x = 0.000;
        pose.position.y = -0.300;
        pose.position.z = 0.010;
        pose.orientation.x = 0.0;
        pose.orientation.y = 0.0;
        pose.orientation.z = 1.0;
        pose.orientation.w = 0.0;
        
        grinder.meshes.push_back(mesh_msg);
        grinder.mesh_poses.push_back(pose);
        grinder.operation = grinder.ADD;
        collision_objects.push_back(grinder);
        
        moveit_msgs::msg::ObjectColor grinder_color;
        grinder_color.id = "grinder";
        grinder_color.color.r = 0.3;
        grinder_color.color.g = 0.8;
        grinder_color.color.b = 0.9;
        grinder_color.color.a = 1.0;
        object_colors.push_back(grinder_color);
        
        delete mesh;
        }
    }
    
    // ── Coffee machine (mesh) ──────────────────────────────────────────────
    {
        moveit_msgs::msg::CollisionObject coffee_machine;
        coffee_machine.header.frame_id = "world";
        coffee_machine.id = "coffee_machine";
        
        shapes::Mesh* mesh = shapes::createMeshFromResource(
            "file:///home/vasee22/igus-coffee-moveit/src/igus_rebel_ros2/igus_rebel_description/meshes/CoffeeMachine.stl",
            Eigen::Vector3d(0.001, 0.001, 0.001));
        
        if (mesh)
        {
        shape_msgs::msg::Mesh mesh_msg;
        shapes::ShapeMsg mesh_msg_variant;
        shapes::constructMsgFromShape(mesh, mesh_msg_variant);
        mesh_msg = boost::get<shape_msgs::msg::Mesh>(mesh_msg_variant);
        
        geometry_msgs::msg::Pose pose;
        pose.position.x = 0.419;
        pose.position.y = -0.316;
        pose.position.z = 0.010;
        pose.orientation.w = 1.0;
        
        coffee_machine.meshes.push_back(mesh_msg);
        coffee_machine.mesh_poses.push_back(pose);
        coffee_machine.operation = coffee_machine.ADD;
        collision_objects.push_back(coffee_machine);
        
        moveit_msgs::msg::ObjectColor coffee_machine_color;
        coffee_machine_color.id = "coffee_machine";
        coffee_machine_color.color.r = 0.2;
        coffee_machine_color.color.g = 0.6;
        coffee_machine_color.color.b = 0.2;
        coffee_machine_color.color.a = 1.0;
        object_colors.push_back(coffee_machine_color);
        
        delete mesh;
        }
    }
    
    // ── Tool station (mesh) ────────────────────────────────────────────────
    {
        moveit_msgs::msg::CollisionObject tool_station;
        tool_station.header.frame_id = "world";
        tool_station.id = "tool_station";
        
        shapes::Mesh* mesh = shapes::createMeshFromResource(
            "file:///home/vasee22/igus-coffee-moveit/src/igus_rebel_ros2/igus_rebel_description/meshes/Tool Station.stl",
            Eigen::Vector3d(0.001, 0.001, 0.001));
        
        if (mesh)
        {
        shape_msgs::msg::Mesh mesh_msg;
        shapes::ShapeMsg mesh_msg_variant;
        shapes::constructMsgFromShape(mesh, mesh_msg_variant);
        mesh_msg = boost::get<shape_msgs::msg::Mesh>(mesh_msg_variant);
        
        geometry_msgs::msg::Pose pose;
        pose.position.x = -0.670;
        pose.position.y = -0.300;
        pose.position.z = 0.210;
        pose.orientation.x = 0.0;
        pose.orientation.y = 0.0;
        pose.orientation.z = 0.7071;
        pose.orientation.w = 0.7071;
        
        tool_station.meshes.push_back(mesh_msg);
        tool_station.mesh_poses.push_back(pose);
        tool_station.operation = tool_station.ADD;
        collision_objects.push_back(tool_station);
        
        moveit_msgs::msg::ObjectColor tool_station_color;
        tool_station_color.id = "tool_station";
        tool_station_color.color.r = 0.7;
        tool_station_color.color.g = 0.1;
        tool_station_color.color.b = 0.8;
        tool_station_color.color.a = 1.0;
        object_colors.push_back(tool_station_color);
        
        delete mesh;
        }
    }
    
    // ── Cup holder (mesh) ──────────────────────────────────────────────────
    {
        moveit_msgs::msg::CollisionObject cup_holder;
        cup_holder.header.frame_id = "world";
        cup_holder.id = "cup_holder";
        
        shapes::Mesh* mesh = shapes::createMeshFromResource(
            "file:///home/vasee22/igus-coffee-moveit/src/igus_rebel_ros2/igus_rebel_description/meshes/CoffeeCupHolder.stl",
            Eigen::Vector3d(0.001, 0.001, 0.001));
        
        if (mesh)
        {
        shape_msgs::msg::Mesh mesh_msg;
        shapes::ShapeMsg mesh_msg_variant;
        shapes::constructMsgFromShape(mesh, mesh_msg_variant);
        mesh_msg = boost::get<shape_msgs::msg::Mesh>(mesh_msg_variant);
        
        geometry_msgs::msg::Pose pose;
        pose.position.x = -0.469;
        pose.position.y = -0.351;
        pose.position.z = 0.210;
        pose.orientation.x = 0.0;
        pose.orientation.y = 0.0;
        pose.orientation.z = -0.7071;
        pose.orientation.w = 0.7071;
        
        cup_holder.meshes.push_back(mesh_msg);
        cup_holder.mesh_poses.push_back(pose);
        cup_holder.operation = cup_holder.ADD;
        collision_objects.push_back(cup_holder);
        
        moveit_msgs::msg::ObjectColor cup_holder_color;
        cup_holder_color.id = "cup_holder";
        cup_holder_color.color.r = 0.1;
        cup_holder_color.color.g = 0.1;
        cup_holder_color.color.b = 0.1;
        cup_holder_color.color.a = 0.5;
        object_colors.push_back(cup_holder_color);
        
        delete mesh;
        }
    }
    
    // ── Add all objects to planning scene with colors ──────────────────────
    RCLCPP_INFO(LOGGER, "Adding %zu collision objects with colors to planning scene...", collision_objects.size());
    psi.applyCollisionObjects(collision_objects, object_colors);
    
    rclcpp::sleep_for(std::chrono::seconds(1));
    
    RCLCPP_INFO(LOGGER, "Planning scene setup complete!");
}