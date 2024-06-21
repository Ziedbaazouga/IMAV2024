
#ifndef DRONE_MAGNETCONTROLLER_H
#define DRONE_MAGNETCONTROLLER_H

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/bool.hpp"
#include <pigpio.h>

class magnetControllerNode : public rclcpp::Node
{
public:
    magnetControllerNode();
    ~magnetControllerNode();
    void magnetEnable();
    void magnetEnable(int enablingPeriode);
    void magnetDisable();
    void magnetController(const std_msgs::msg::Bool::SharedPtr msg);

private :
    rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr subscription_;
    const int gpio_pin_ = 17;
};

#endif //DRONE_MAGNETCONTROLLER_H
