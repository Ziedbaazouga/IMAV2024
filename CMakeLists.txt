cmake_minimum_required(VERSION 3.5)
project(my_package)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

include_directories(
  include
)

add_executable(sensor_node src/main.cpp src/UltrasoundSensor.cpp src/MagnetController.cpp)
ament_target_dependencies(sensor_node rclcpp std_msgs)

install(TARGETS
  sensor_node
  DESTINATION lib/${PROJECT_NAME})

ament_package()
