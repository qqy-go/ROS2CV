from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    camera = Node(
            package="camera",
            executable="camera"
            )
    serial = Node(
            package="serial",
            executable="serial_node"
    )
    armor_detector = Node(
            package="detector",
            executable="detector"
            )
    armor_predictor = Node(
            package="predictor",
            executable="predictor"
    )


    launch_description = LaunchDescription(
            [camera, serial, armor_detector, armor_predictor])

    return launch_description
