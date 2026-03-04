from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        # Birinci Node'un
        Node(
            package='pkg_srv',
            executable='mission_control_server',
            name='mission_control_server_node'
        ),
        # ?kinci Node'un
        Node(
            package='siha_camera_pkg',
            executable='camera_publisher',
            name='camera_publisher_node'
        ),
        Node(
            package='video_recorder_pkg',
            executable='video_recorder_control_node',
            name='video_recorder_control_node'
        ),
        Node(
            package='video_recorder_pkg',
            executable='video_writer_node',
            name='video_writer_node'
        ),
        Node(
            package='qr_detector',
            executable='qr_detection_node',
            name='qr_detection_node'
        ),
        Node(
            package='atmaca_vision',
            executable='target_detection_node',
            name='target_detection_node'
        ),
        # Sisteme dahil etmek istedi?in di?er node'lar? buraya eklemeye devam edebilirsin
    ])
