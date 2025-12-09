cmake_minimum_required(VERSION 3.8)
project(atmaca_flight_control)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_lifecycle REQUIRED)
find_package(lifecycle_msgs REQUIRED)
find_package(px4_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(pars_msgs REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)

# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)
add_executable(telemetry_node src/telemetry_node.cpp)
add_executable(hedef_gps src/hedef_gps.cpp)
add_executable(offboard_node src/offboard.cpp)
add_executable(target_navigation_node src/target_navigation_node.cpp)
add_executable(sahte_hedef src/sahte_hedef.cpp)

target_link_libraries(offboard_node -latomic)
ament_target_dependencies(telemetry_node rclcpp px4_msgs std_msgs)
ament_target_dependencies(offboard_node rclcpp px4_msgs std_msgs)
ament_target_dependencies(hedef_gps pars_msgs rclcpp px4_msgs  )
ament_target_dependencies(target_navigation_node tf2_ros pars_msgs rclcpp rclcpp_lifecycle lifecycle_msgs px4_msgs)
ament_target_dependencies(sahte_hedef pars_msgs rclcpp)

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

install(TARGETS
  target_navigation_node
  telemetry_node
  hedef_gps
  offboard_node
  sahte_hedef
  DESTINATION lib/${PROJECT_NAME}
)
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()