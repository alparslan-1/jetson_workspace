cmake_minimum_required(VERSION 3.8)
project(qr_detector)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(image_transport REQUIRED)
find_package(cv_bridge REQUIRED)

# Find OpenCV with CUDA support
find_package(OpenCV REQUIRED COMPONENTS core imgproc imgcodecs)
find_package(OpenCV REQUIRED COMPONENTS cudaimgproc cudawarping)

# Include directories
include_directories(include)

# Add executable
add_executable(qr_detection_node src/qr_detection_node.cpp)

# Link libraries
ament_target_dependencies(qr_detection_node
  rclcpp
  std_msgs
  sensor_msgs
  image_transport
  cv_bridge
)

target_link_libraries(qr_detection_node
  ${OpenCV_LIBS}
)

# Install
install(TARGETS
  qr_detection_node
  DESTINATION lib/${PROJECT_NAME}
)

# Install launch files if any
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/launch")
  install(DIRECTORY launch
    DESTINATION share/${PROJECT_NAME}/
  )
endif()

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()

