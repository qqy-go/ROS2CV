#pragma once
#include "rclcpp/rclcpp.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
#include "my_interfaces/msg/robot_status.hpp"
#include "my_interfaces/msg/armor.hpp"
#include "my_interfaces/msg/send_data.hpp"
#include "anglesolver.hpp"
#include "../../../include/data_type.h"
#include "kalmanFilter.hpp"
class Predictor : public rclcpp::Node 
{
private:

    double pitch_last, yaw_last, dis_last;
    int id_last;
    RobotInfo robot_;
    float evaluate_threshold = 1000.0;
    bool inited = false;
    std::vector<Armor> armor_seq;
    Armor current_armor;
    std::unique_ptr<AngleSolver> anglesolver;
     std::shared_ptr<KalmanFilter> kf;
    rclcpp::Subscription<my_interfaces::msg::Armor>::SharedPtr armor_sub_;
    rclcpp::Publisher<my_interfaces::msg::SendData>::SharedPtr data_pub_;
    void predict_callback(const std::shared_ptr<my_interfaces::msg::Armor> armor_msg_);


public:

    explicit Predictor(const std::string& node_name);
    ~Predictor()=default;

    void reset();
    cv::Point3f predict(const Armor& armor);
};
