#pragma once
#include "rclcpp/rclcpp.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
#include "my_interfaces/msg/robot_status.hpp"
#include "my_interfaces/msg/armor.hpp"
#include "my_interfaces/msg/send_data.hpp"
#include "anglesolver.hpp"
#include "../../../include/data_type.h"

class Predictor : public rclcpp::Node 
{
private:

    double pitch_last, yaw_last, dis_last;
    int id_last;
    RobotInfo robot_;
    std::unique_ptr<AngleSolver> anglesolver;
    rclcpp::Subscription<my_interfaces::msg::Armor>::SharedPtr armor_sub_;
    rclcpp::Publisher<my_interfaces::msg::SendData>::SharedPtr data_pub_;
    rclcpp::Subscription<my_interfaces::msg::RobotStatus>::SharedPtr robot_sub_;
    void predict_callback(const std::shared_ptr<my_interfaces::msg::Armor> armor_msg_);
    void robotCallback(const std::shared_ptr<my_interfaces::msg::RobotStatus> robot_msg);

public:

    explicit Predictor(const std::string& node_name);
    ~Predictor()=default;
};
