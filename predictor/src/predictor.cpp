#include "../include/predictor/predictor.h"


Predictor::Predictor(const std::string& node_name) : rclcpp::Node(node_name){
    
    RCLCPP_INFO(this->get_logger(), "This is %s",node_name.c_str());
    armor_sub_ = this->create_subscription<my_interfaces::msg::Armor>("/detector/cam_point", 10, \
    std::bind(&Predictor::predict_callback, this, std::placeholders::_1));
    data_pub_ = this->create_publisher<my_interfaces::msg::SendData>("/predictor/send_data", 10);

    anglesolver = std::make_unique<AngleSolver>();
    pitch_last = dis_last = yaw_last = 0;
    id_last = -1;

    cv::FileStorage fin("./src/predictor/params/params.yaml", cv::FileStorage::READ);

    if(!fin.isOpened()){
        std::cout<<"[ERROR ]predictor open params file error, please check \r\n";
        exit(-1);
    }

    fin["sentry_up"]["Q00"] >> ekf.Q(0, 0);
    fin["sentry_up"]["Q11"] >> ekf.Q(1, 1);
    fin["sentry_up"]["Q22"] >> ekf.Q(2, 2);
    fin["sentry_up"]["Q33"] >> ekf.Q(3, 3);
    fin["sentry_up"]["Q44"] >> ekf.Q(4, 4);
        // 观测过程协方差
    fin["sentry_up"]["R00"] >> ekf.R(0, 0);
    fin["sentry_up"]["R11"] >> ekf.R(1, 1);
    fin["sentry_up"]["R22"] >> ekf.R(2, 2);

    fin.release();
}

void Predictor::reset() {

    
    last_dis = current_armor.distance;
    Eigen::Matrix<double, 5, 1> Xr;
    Xr << current_armor.world_point_.x, 0, current_armor.world_point_.y, 0, current_armor.world_point_.z;
    ekf.init(Xr);
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

    robot_.ptz_pitch = armor_msg_->robot_pitch;
    robot_.ptz_yaw = armor_msg_->robot_yaw;
    robot_.ptz_roll = armor_msg_->robot_roll;
    robot_.bullet_speed = armor_msg_->bullet_speed;
    
    auto abs_point = anglesolver->cam2abs(cam, robot_);
  
    // RCLCPP_INFO(this->get_logger(), "abs point x: %lf , y: %lf , z:%lf",abs_point.x, abs_point.y,abs_point.z);
    // std::cout<<"abs cam_ "<<abs_point<<std::endl;


    //imu_abs to motion_abs
    //model meanings: x->left; y->up; z->forward
    abs2motion(abs_point, current_armor.world_point_);
    ///predict
    current_armor.time_stamp = time_stamp;
    current_armor.id = armor_msg_->id;
    current_armor.distance = sqrt(current_armor.world_point_.x*current_armor.world_point_.x + current_armor.world_point_.y*current_armor.world_point_.y + \
                                current_armor.world_point_.z*current_armor.world_point_.z);
    // std::cout<<"time_ "<<time_stamp<<"\r\n";

    // found armor case

    if(current_armor.id>-1){

        if(!inited){
            reset();
            last_time = time_stamp;
            inited = true;
        }

        last_dis = current_armor.distance;

        double delta_t = time_stamp - last_time;
        std::cout<<"delta t "<<delta_t<<std::endl;
        last_time = time_stamp;

        Predict predictfunc;
        Measure measure;

        Eigen::Matrix<double, 5, 1> Xr;
        Xr << current_armor.world_point_.x, 0, current_armor.world_point_.y, 0, current_armor.world_point_.z; //input

        Eigen::Matrix<double, 3, 1> Yr;
        measure(Xr.data(), Yr.data());  //convert xyz to pitch yaw 

        predictfunc.delta_t = delta_t;
        ekf.predict(predictfunc);//predict

        
        //TODO: add evaluation to check 

        Eigen::Matrix<double, 5, 1> Xe = ekf.update(measure, Yr);//best evalute

        double predict_time = current_armor.distance/armor_msg_->bullet_speed + 0.001;

        predictfunc.delta_t = predict_time;//use measure speed to predict next
        Eigen::Matrix<double, 5, 1> Xp;

        predictfunc(Xe.data(), Xp.data()); //use ekf v to predict next position
        Eigen::Vector3d p_pw{Xp(0, 0), Xp(2, 0), Xp(4, 0)};

        auto result = cv::Point3f(p_pw(0,0),p_pw(1,0),p_pw(2,0));
        cv::Point3f abs_pred;
        //get final abs
        motion2abs(result, abs_pred);

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
        


        auto cam_pred = anglesolver->abs2cam(abs_pred,robot_);
        anglesolver->getAngle_nofix(cam_pred,pitch,yaw, dis);


        // if armor continue check
        
        if(armor_seq.size()){
            if(current_armor.time_stamp - armor_seq.back().time_stamp > 2){
                std::cout<<"reset!!"<<std::endl;
                inited = false;
            }

        }
        armor_seq.push_back(current_armor);
        if(armor_seq.size()>200){armor_seq.erase(armor_seq.begin());}
    }else{
        anglesolver->getAngle_nofix(cam,pitch,yaw, dis);

    }


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
    // std::cout<<"[cam final angle ] "<<" pitch "<<pitch<<" yaw "<<yaw<<" dis "<<dis<<std::endl;
    RCLCPP_INFO(this->get_logger(), "cam pitch: %lf , yaw : %lf",pitch, yaw);
}


int main(int argc, char** argv){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Predictor>("predict_node");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;

}