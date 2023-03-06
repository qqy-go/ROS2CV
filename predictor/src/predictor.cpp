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

    cv::FileStorage fs("./src/predictor/params/params.yaml", cv::FileStorage::READ);

    if(!fs.isOpened()){
        std::cout<<"[ERROR ]predictor open params file error, please check \r\n";
        exit(-1);
    }

    Eigen::MatrixXd A(6,6);
    Eigen::MatrixXd P0(6,6);
    Eigen::MatrixXd H(3,6);
    Eigen::MatrixXd Q(6,6);
    Eigen::MatrixXd R(3,3);
    Eigen::MatrixXd I(6,6);
    A<< 1,0,0,0.5,0,0,
        0,1,0,0,0.5,0,
        0,0,1,0,0,0.5,
        0,0,0,1,0,0,
        0,0,0,0,1,0,
        0,0,0,0,0,1;
    P0.setIdentity(6,6);
    I.setIdentity(6,6);
    H << 1,0,0,0,0,0,
         0,1,0,0,0,0,
         0,0,1,0,0,0;

    Q << fs["sentry_up"]["Q00"], 0,0,0,0,0,
         0,fs["sentry_up"]["Q11"],0,0,0,0,
         0,0,fs["sentry_up"]["Q22"],0,0,0,
         0,0,0,fs["sentry_up"]["Q33"],0,0,
         0,0,0,0,fs["sentry_up"]["Q44"],0,
         0,0,0,0,0,fs["sentry_up"]["Q55"];
    R << fs["sentry_up"]["R00"],0,0,
         0,fs["sentry_up"]["R11"],0,
         0,0,fs["sentry_up"]["R22"];

    std::cout<<"Q "<<Q<<" \r\n R "<<R<<std::endl;

    kf = std::make_shared<KalmanFilter>(A,P0,H,Q,R);
    fs.release();
}

void Predictor::reset() {

    Eigen::VectorXd x0(6) ;
    x0 << current_armor.world_point_.x, current_armor.world_point_.y, current_armor.world_point_.z,0,0,0;
    kf->init(x0, current_armor.time_stamp);
    armor_seq.clear();
}

void Predictor::predict_callback(const std::shared_ptr<my_interfaces::msg::Armor> armor_msg_){
    double time_stamp = armor_msg_->time_stamp;
    cv::Point3f cam = cv::Point3f(armor_msg_->cam_point.x, armor_msg_->cam_point.y, armor_msg_->cam_point.z);
    double pitch, yaw, dis;
    pitch = yaw = dis = 0;
    ///TODO add predictor
    

    // std::cout<<"robot info: "
    //             <<" color: "<<robot_.color
    //             <<" pitch: "<<robot_.ptz_pitch
    //             <<" yaw: "<<robot_.ptz_yaw
    //             <<" bulled speed: "<<robot_.bullet_speed<<std::endl;

    RobotInfo this_robot = robot_;
    
    auto abs_point = anglesolver->cam2abs(cam, this_robot);
    std::cout<<"abs cam_ "<<abs_point<<std::endl;
    ///predict
    current_armor.world_point_ = abs_point;
    current_armor.time_stamp = time_stamp;
    current_armor.id = armor_msg_->id;
    current_armor.distance = sqrt(abs_point.x*abs_point.x + abs_point.y*abs_point.y + abs_point.z*abs_point.z);
    std::cout<<"time_ "<<time_stamp<<"\r\n";

    if(!inited){
        reset();
        inited = true;
    }

    Eigen::VectorXd y0(3);
    y0 << current_armor.world_point_.x, current_armor.world_point_.y, current_armor.world_point_.z;
    kf->predict(y0,current_armor.time_stamp);
    //

    // Eigen::VectorXd Ek(3); //3x1
    // Ek = y0 - kf->H*kf->X_hat_new;
    // Eigen::MatrixXd Dk(3,3);
    // Dk=kf->H*kf->P+kf->R; //3x3
    // auto rk = Ek.transpose()*Dk.inverse()*Ek;
    // std::cout<<"kafang "<<rk<<std::endl;

    // if(rk < evaluate_threshold){
    //     reset();
    //     cv::Point3f result = current_armor.world_point_;
    //     return result;
    // }
    kf->update(y0);
    cv::Point3f result = cv::Point3f (kf->X_hat_new(0) +kf->X_hat_new(3)*current_armor.distance/15.0 ,\
                                    kf->X_hat_new(1)+kf->X_hat_new(4)*current_armor.distance/15.0,\
                                    kf->X_hat_new(2)+kf->X_hat_new(5)*current_armor.distance/15.0);

    auto cam_pred = anglesolver->abs2cam(result,this_robot);

    //
    // anglesolver->getAngle_nofix(cam_pred,pitch,yaw, dis);
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