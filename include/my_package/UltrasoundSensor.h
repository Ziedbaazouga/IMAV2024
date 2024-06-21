
#ifndef DRONE_ULTRASOUNDSENSOR_H
#define DRONE_ULTRASOUNDSENSOR_H

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/range.hpp>
#include <pigpio.h>

class UltrasonicSensorNode : public rclcpp::Node
{
public:
    UltrasonicSensorNode() ;
    
private:
    void distance (int timeout);
    void recordPulseLength();
    rclcpp::Publisher<sensor_msgs::msg::Range>::SharedPtr publisher_;
    const int trigger = 18;
    const int echo = 24;
    volatile long startTimeUsec;
    volatile long endTimeUsec;
    double distanceMeters;
    long travelTimeUsec;
    long now;
};

#endif //DRONE_ULTRASOUNDSENSOR_H
