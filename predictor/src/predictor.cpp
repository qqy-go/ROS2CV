#include "../include/predictor/predictor.h"


Predictor::Predictor(const std::string& node_name) : rclcpp::Node(node_name){
    RCLCPP_INFO(this->get_logger(), "This is %s",node_name.c_str());
    armor_sub_ = this->create_subscription<my_interfaces::msg::Armor>("/detector/cam_point", 10, \
    std::bind(&Predictor::predict_callback, this, std::placeholders::_1));
    data_pub_ = this->create_publisher<my_interfaces::msg::SendData>("/predictor/send_data", 10);
     robot_sub_ = this->create_subscription<my_interfaces::msg::RobotStatus>("/serial/robotinfo",10,\
    std::bind(&Predictor::robotCallback, this, std::placeholders::_1));
    anglesolver = std::make_unique<AngleSolver>();
    pitch_last = dis_last = yaw_last = 0;
    id_last = -1;
}


void Predictor::predict_callback(const std::shared_ptr<my_interfaces::msg::Armor> armor_msg_){
    cv::Point3f cam = cv::Point3f(armor_msg_->cam_point.x, armor_msg_->cam_point.y, armor_msg_->cam_point.z);
    double pitch, yaw, dis;
    pitch = yaw = dis = 0;
    ///TODO add predictor
    anglesolver->getAngle_nofix(cam,pitch,yaw, dis);

    auto send = my_interfaces::msg::SendData();

    if(armor_msg_->id > -1){
        send.tg_num = 1;
        pitch_last = pitch;
        yaw_last = yaw;
        dis_last = dis;
        id_last = armor_msg_->id;
    }
    else{
        if(id_last>-1){
            pitch = pitch_last;
            yaw = yaw_last;
            dis = dis_last;
            send.tg_num = 1;
            pitch_last = dis_last = yaw_last = 0;
            id_last = -1;
        }else{
            send.tg_num = 0;
            pitch = yaw = dis = 0;

        }
        
    }


    send.pitch = pitch;
    send.yaw = yaw;
    send.dis = dis;
    data_pub_->publish(send);

}


void Predictor::robotCallback(const std::shared_ptr<my_interfaces::msg::RobotStatus> robot_msg){
    robot_.color = robot_msg->color;
    robot_.ptz_pitch = robot_msg->pitch;
    robot_.ptz_yaw = robot_msg->yaw;
    robot_.bullet_speed = robot_msg->bullet_speed;
}

int main(int argc, char** argv){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Predictor>("predict_node");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;

}