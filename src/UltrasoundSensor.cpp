#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/range.hpp>
#include <pigpio.h>

#include "UltrasoundSensor.h"

UltrasonicSensorNode :: UltrasonicSensorNode() : Node("ultrasonic_sensor_node")
{
    gpioInitialise();
    gpioSetMode(trigger, PI_OUTPUT);
    gpioSetMode(echo, PI_INPUT);
    digitalWrite(trigger, LOW);
    delay(500);

    // Create a publisher
    publisher_ = this->create_publisher<sensor_msgs::msg::Range>("ultrasonic_range", 10);
}

void  UltrasonicSensorNode :: distance(int timeout)
{
    delay(10);

    digitalWrite(trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger, LOW);

    now=micros();

    while (digitalRead(echo) == LOW && micros()-now<timeout);
    recordPulseLength();

    travelTimeUsec = endTimeUsec - startTimeUsec;
    distanceMeters = 100*((travelTimeUsec/1000000.0)*340.29)/2;

    auto message = sensor_msgs::msg::Range();
    message.header.stamp = this->now();
    message.header.frame_id = "ultrasound_sensor_frame";
    message.radiation_type = sensor_msgs::msg::Range::ULTRASOUND;
    message.field_of_view = 0.0523599; // Example value, 3 degrees in radians
    message.min_range = 0.02; // Example value, 2 cm
    message.max_range = 4.0; // Example value, 4 m
    message.range =  distanceMeters;
    publisher_->publish(message);

    std::cout<<distanceMeters<<std::endl;
}

void UltrasonicSensorNode :: recordPulseLength()
{
    startTimeUsec = micros();
    while ( digitalRead(echo) == HIGH );
    endTimeUsec = micros();
}
