#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/bool.hpp"
#include <pigpio.h>

#include "MagnetController.h"

MagnetControllerNode :: magnetControllerNode() : Node("magnet_controller_node")
{
    gpioSetMode(gpio_pin_, PI_OUTPUT);

    subscription_ = this->create_subscription<std_msgs::msg::Bool>(
            "magnet_control", 10, std::bind(&MagnetControllerNode::control_magnet, this, std::placeholders::_1));
}

MagnetControllerNode :: ~magnetControllerNode()
{
    gpioTerminate();
}

void MagnetControllerNode ::  magnetEnable()
{
    gpioWrite(gpio_pin_, PI_LOW);
    RCLCPP_INFO(this->get_logger(), "Magnet enabled");
}

void MagnetControllerNode ::  magnetEnable(int enablingPeriode)
{
 this->magnetEnable();
 delay(enablingPeriode);
 this->magnetDisable();
}

void MagnetControllerNode :: magnetDisable()
{
    gpioWrite(gpio_pin_, PI_HIGH);
    RCLCPP_INFO(this->get_logger(), "Magnet disabled");
}

void MagnetControllerNode :: MagnetController(const std_msgs::msg::Bool::SharedPtr msg)
{
if (msg->data)
    this->magnetEnable();
else
    this->magnetDisable();
}
