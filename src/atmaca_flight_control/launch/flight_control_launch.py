import os
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='atmaca_flight_control',  # Paketinin adı (CMakeLists.txt başındaki project adı)
            executable='target_navigation_node', # CMakeLists'te 'add_executable' ile verdiğimiz isim
            name='navigation_node',            # Çalışırken terminalde/loglarda görünecek isim
            output='screen'                   # Logları ekrana bas
        ),
        Node(
            package='atmaca_flight_control',
            executable='hedef_gps',
            name='hedef_gps_node',
            output='screen'
        ),
        Node(
            package='atmaca_flight_control',
            executable='sahte_hedef',
            name='sahte_hedef',
            output='screen'
        ),
    ])  