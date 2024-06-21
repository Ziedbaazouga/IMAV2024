#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/range.hpp>
#include <pigpio.h>

#include "UltrasoundSensor.h"

void testUltrasoundSensor()
{
    rclcpp::init(0, nullptr);
    rclcpp::spin(std::make_shared<UltrasonicSensorNode>());
    rclcpp::shutdown();
}

void testMagnetController()
{
    rclcpp::init(0, nullptr);
    auto node = std::make_shared<MagnetControllerNode>();
    node->magnetEnable(5);
    rclcpp::shutdown();

}

int main(int argc, char *argv[])
{
    testUltrasoundSensor();
    testMagnetController();

    return 0;
}
