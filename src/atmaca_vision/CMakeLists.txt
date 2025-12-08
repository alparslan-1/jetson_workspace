cmake_minimum_required(VERSION 3.8)
project(atmaca_vision)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# --- Dependencies ---
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(image_transport REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)        
find_package(OpenCV REQUIRED)

# --- ONNX Runtime Manuel Ayarlar (D?ZELT?LEN KISIM) ---
# K?t?phanenin bulundu?u ana klas?r? tan?ml?yoruz
set(ONNX_ROOT "/root/bridges/jetson_workspace/onnxruntime-linux-aarch64-1.16.3")

# Header (include) dosyalar?n? bul
find_path(ONNXRUNTIME_INCLUDE_DIR NAMES onnxruntime_cxx_api.h
          PATHS ${ONNX_ROOT}/include
          NO_DEFAULT_PATH)

# Library (.so) dosyas?n? bul
find_library(ONNXRUNTIME_LIBRARY NAMES onnxruntime
             PATHS ${ONNX_ROOT}/lib
             NO_DEFAULT_PATH)

if(NOT ONNXRUNTIME_LIBRARY OR NOT ONNXRUNTIME_INCLUDE_DIR)
  message(FATAL_ERROR "ONNX Runtime k?t?phanesi '${ONNX_ROOT}' adresinde bulunamad?! Yolun do?rulu?unu kontrol edin.")
else()
  message(STATUS "ONNX Runtime bulundu: ${ONNXRUNTIME_LIBRARY}")
endif()
# ------------------------------------------------------

# --- Executables ---
add_executable(camera_publisher_node src/camera_node.cpp)
add_executable(qr_detector_node src/qr_detection_node.cpp)
add_executable(target_detection_node src/target_detection_node.cpp)

# --- Dependencies Linking ---
ament_target_dependencies(camera_publisher_node
  rclcpp
  image_transport
  cv_bridge
  OpenCV
)

ament_target_dependencies(qr_detector_node
  rclcpp
  image_transport
  cv_bridge
  sensor_msgs
  std_msgs      
  geometry_msgs 
  OpenCV
)

ament_target_dependencies(target_detection_node
  rclcpp
  image_transport
  cv_bridge
  sensor_msgs
  std_msgs
  geometry_msgs
)

# --- Target Detection Node Specific Linking ---
target_include_directories(target_detection_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  ${OpenCV_INCLUDE_DIRS}
  ${ONNXRUNTIME_INCLUDE_DIR}
)

target_link_libraries(target_detection_node
  ${OpenCV_LIBRARIES}
  ${ONNXRUNTIME_LIBRARY}
)

# --- Install ---
install(TARGETS
  camera_publisher_node
  qr_detector_node
  target_detection_node 
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
