cmake_minimum_required(VERSION 3.8)
project(detector)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(OpenCV REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(image_transport REQUIRED)
find_package(camera_info_manager REQUIRED)
set(InferenceEngine_DIR "/opt/intel/openvino2022/runtime/cmake")
find_package(InferenceEngine)
set(ngraph_DIR "/opt/intel/openvino2022/runtime/cmake")
find_package(ngraph REQUIRED)
find_package(my_interfaces REQUIRED)
include_directories(
        #OpenVINO推理引擎的头文件
        /opt/intel/openvino2022/runtime/include/
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

add_executable(detector src/ovinference.cpp src/armor_detect.cpp include/detector/ovinference.h)
target_include_directories(detector PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
  target_compile_features(detector PUBLIC c_std_99 cxx_std_17)

ament_target_dependencies(detector rclcpp sensor_msgs image_transport cv_bridge OpenCV camera_info_manager my_interfaces)
target_link_libraries(detector  openvino::runtime)
install(TARGETS
        detector
        DESTINATION lib/${PROJECT_NAME})

ament_package()