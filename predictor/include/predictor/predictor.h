#pragma once
#include "rclcpp/rclcpp.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
#include "my_interfaces/msg/robot_status.hpp"
#include "my_interfaces/msg/armor.hpp"
#include "my_interfaces/msg/send_data.hpp"
#include "anglesolver.hpp"
#include "../../../include/data_type.h"
#include "AdaptiveEKF.hpp"


struct Predict {
    /*
     * 此处定义匀速直线运动模型  x1 = x0+v*delta_t
     * x1 = [x,v,]
     */
    template<class T>
    void operator()(const T x0[5], T x1[5]) {
        x1[0] = x0[0] + delta_t * x0[1];  //0.1
        x1[1] = x0[1];  //100
        x1[2] = x0[2] + delta_t * x0[3];  //0.1
        x1[3] = x0[3];  //100
        x1[4] = x0[4];  //0.01
    }
    double delta_t;
};

//  xyz
// pitch  y / (x2 + z2)
//yaw  x/z
template<class T>
void xyz2pyd(T xyz[3], T pyd[3]) {
    /*
     * 工具函数：将 xyz 转化为 pitch、yaw、distance
     */
    pyd[0] = ceres::atan2(xyz[1], ceres::sqrt(xyz[0] * xyz[0] + xyz[2] * xyz[2]));  // pitch
    pyd[1] = ceres::atan2(xyz[0], xyz[2]);  // yaw
    pyd[2] = ceres::sqrt(xyz[0] * xyz[0] + xyz[1] * xyz[1] + xyz[2] * xyz[2]);  // distance
}

struct Measure {
    /*
     * 工具函数的类封装
     */
    template<class T>
    void operator()(const T x[5], T y[3]) {
        T x_[3] = {x[0], x[2], x[4]};
        xyz2pyd(x_, y);
    }
};

class Predictor : public rclcpp::Node 
{


private:
    double pitch_last, yaw_last, dis_last;
    int id_last;

    double last_time;
    double last_dis = 0;

    AdaptiveEKF<5, 3> ekf; 


    RobotInfo robot_;
    float evaluate_threshold = 1000.0;
    bool inited = false;
    std::vector<Armor> armor_seq;
    Armor current_armor;
    std::unique_ptr<AngleSolver> anglesolver;
    rclcpp::Subscription<my_interfaces::msg::Armor>::SharedPtr armor_sub_;
    rclcpp::Publisher<my_interfaces::msg::SendData>::SharedPtr data_pub_;
    void predict_callback(const std::shared_ptr<my_interfaces::msg::Armor> armor_msg_);


public:

    explicit Predictor(const std::string& node_name);
    ~Predictor()=default;

    void reset();
    cv::Point3f predict(const Armor& armor);
};
