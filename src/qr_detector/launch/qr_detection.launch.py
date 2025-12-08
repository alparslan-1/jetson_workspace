#!/usr/bin/env python3
"""
QR Detection Node Launch File
"""

from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='qr_detector',
            executable='qr_detection_node',
            name='qr_detection_node',
            output='screen',
            parameters=[]
        )
    ])

