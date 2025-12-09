cmake_minimum_required(VERSION 3.8)
project(video_recorder_pkg)

# Derleyici ayarlari
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 1. Bagimliliklari Bul
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED)

# Include dizinleri
include_directories(
  include
  ${OpenCV_INCLUDE_DIRS}
)

# 2. Executable: Video Writer Node
add_executable(video_writer_node src/video_writer_node.cpp)
ament_target_dependencies(video_writer_node
  rclcpp
  std_msgs
  sensor_msgs
  cv_bridge
)
target_link_libraries(video_writer_node ${OpenCV_LIBRARIES})

# 3. Executable: Control Node
add_executable(video_recorder_control_node src/video_recorder_control_node.cpp)
ament_target_dependencies(video_recorder_control_node
  rclcpp
  std_msgs
)

# 4. Install (D?KKAT: Burada launch k?sm? YOK)
install(TARGETS
  video_writer_node
  video_recorder_control_node
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
