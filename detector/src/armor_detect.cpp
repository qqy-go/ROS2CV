#include "../include/detector/armor_detect.h"
#include "opencv2/opencv.hpp"
#include "../../include/data_type.h"
#include "../../include/Tictoc.hpp"
#include "boost/bind.hpp"


ArmorDetect::ArmorDetect(const std::string& name) : Node(name){
    RCLCPP_INFO(this->get_logger(), "This is %s",name.c_str());
    // camera_sub_ = std::make_shared<image_transport::CameraSubscriber>(this, "/camera/image_raw", 
    // std::bind(&ArmorDetect::imageCallback,this,std::placeholders::_1), "raw",rmw_qos_profile_sensor_data);

    display_pub_ = image_transport::create_publisher(this, "/detector/image_display",rmw_qos_profile_default);

    ovinfer = std::make_shared<OvInference>("./src/detector/model/rm-net16.xml");
    camerainfo_sub_ = this->create_subscription<sensor_msgs::msg::CameraInfo>("/camera/camera_info",rclcpp::SensorDataQoS(),
     [this](sensor_msgs::msg::CameraInfo::ConstSharedPtr camera_info){
        pnpsolver = std::make_unique<PNPSolver>(camera_info->k, camera_info->d);
        camerainfo_sub_.reset();
     });
   
    campoint_pub_ = this->create_publisher<my_interfaces::msg::Armor>("/detector/cam_point",rclcpp::SensorDataQoS());

    image_sub_ = std::make_shared<message_filters::Subscriber<sensor_msgs::msg::Image>>(this,"/camera/image_raw",rmw_qos_profile_sensor_data);
    robot_sub_ = std::make_shared<message_filters::Subscriber<my_interfaces::msg::RobotStatus>>(this,"/serial/robotinfo");
    sync_ = std::make_shared<message_filters::Synchronizer<camimuSyncPolicy>>(camimuSyncPolicy(10),*image_sub_, *robot_sub_);
    sync_->registerCallback(boost::bind(&ArmorDetect::combineCallback,this,_1,_2));

}

void ArmorDetect::color_check(const char color, std::vector<OvInference::Detection> &results) {
    int IF_WE_RED = -1;
    if(color == 'r')
        IF_WE_RED = 1;
    for (auto i = results.begin(); i != results.end();) {
        if(IF_WE_RED){
            if(i->class_id<9)
                i = results.erase(i);
            else
                ++i;
        }else {
            if(i->class_id>9)
                i = results.erase(i);
            else
                ++i;
        }
    }

}

void ArmorDetect::armor_sort(OvInference::Detection &final_obj, std::vector <OvInference::Detection> &results, cv::Mat& src) {
    if(results.size() == 0){
        lose_cnt++;
        if(lose_cnt>3){
            lose_cnt = 0;
            locked_id=-1; //lose
        }
    }else
        lose_cnt = 0;

    if(results.size() == 1){
        final_obj = results[0];
        locked_id = final_obj.class_id;
    }
    else{
        if(locked_id == -1){ //already has not locked id yet
            double min_dis = 10000;
            int min_idx = -1;
            for (int i = 0; i < results.size(); ++i) {
                double obj_center_x = 0.25*(results[i].obj.p1.x+results[i].obj.p2.x+results[i].obj.p3.x+results[i].obj.p4.x);
                double obj_center_y = 0.25*(results[i].obj.p1.y+results[i].obj.p2.y+results[i].obj.p3.y+results[i].obj.p4.y);
                double dis = fabs(obj_center_x - src.cols/2)+ fabs(obj_center_y-src.rows/2);
                if(dis < min_dis){
                    min_dis = dis;
                    min_idx = i;
                }
            }
            if(min_idx>=0){
                final_obj = results[min_idx];
                lock_cnt++;
                if(lock_cnt>3){
                    locked_id = final_obj.class_id;
                    lock_cnt = 0;
                }

            }
        }else{
            for (const auto re : results){
                if(re.class_id == locked_id){
                    final_obj = re;
                    break;
                }
            }
            lose_cnt++;
        }
    }
}


void ArmorDetect::draw_target(const OvInference::Detection &obj, cv::Mat &src) {
    cv::line(src, obj.obj.p1, obj.obj.p3, cv::Scalar(0, 0, 255), 3);
    cv::line(src, obj.obj.p2, obj.obj.p4, cv::Scalar(0, 0, 255), 3);
    cv::line(src, obj.obj.p1, obj.obj.p2, cv::Scalar(0, 0, 255), 3);
    cv::line(src, obj.obj.p3, obj.obj.p4, cv::Scalar(0, 0, 255), 3);
}



// void ArmorDetect::imageCallback(const sensor_msgs::msg::Image::ConstSharedPtr & image_msg){


//     try {
//         //log info
//         // RCLCPP_INFO(this->get_logger(), "get raw image");

//         //subscribe camera and camera info
//         auto src = cv_bridge::toCvShare(image_msg, "bgr8")->image;
//         double time_stamp = image_msg->header.stamp.sec + image_msg->header.stamp.nanosec*1e-9;
//         // double time_stamp = double(image_msg->header.stamp.sec)/1000.0;
//         RCLCPP_INFO(this->get_logger(), "sec: %lf ",time_stamp);
//         std::vector<OvInference::Detection> results;
//         ovinfer->infer(src, results);
//         RobotInfo robot_ = {'a',0,0,0};
//         color_check(robot_.color, results);
//         OvInference::Detection final_obj;
//         final_obj.class_id = -1;           //check if armor
//         armor_sort(final_obj, results, src);
//         cv::putText(src,"lock_ed id "+ std::to_string(locked_id),cv::Point (15,30),
//         cv::FONT_HERSHEY_COMPLEX_SMALL,1,cv::Scalar(255,0,0));
//         draw_target(final_obj,src);
//         cv::Point3f cam_ = cv::Point3f(0,0,0);
//         cam_ = pnpsolver->get_cam_point(final_obj);
//         // if(final_obj.class_id > -1){
//         //     std::cout<< "cam_ point "<<cam_<<std::endl;
//         // }
        
//         auto campoint_msg_ = my_interfaces::msg::Armor();
//         campoint_msg_.time_stamp = time_stamp;
//         campoint_msg_.id = final_obj.class_id;
//         campoint_msg_.cam_point.x = cam_.x;
//         campoint_msg_.cam_point.y = cam_.y;
//         campoint_msg_.cam_point.z = cam_.z;
//         campoint_msg_.world_point.x = 0;
//         campoint_msg_.world_point.y = 0;
//         campoint_msg_.world_point.z = 0;

//         campoint_pub_->publish(campoint_msg_);
//         ///TODO: publish processed image, armor information
//         processed_msg_ = cv_bridge::CvImage(hdr,"bgr8",src).toImageMsg();
//         display_pub_.publish(processed_msg_);

//         //convert and publish
        
//     } catch (cv_bridge::Exception & e) {
//         auto logger = rclcpp::get_logger("image_raw");
//         RCLCPP_ERROR(logger, "Could not convert from '%s' to 'bgr8'.", image_msg->encoding.c_str());
//     }   
// }


void ArmorDetect::combineCallback(const sensor_msgs::msg::Image::ConstSharedPtr & image_msg,
    const std::shared_ptr<my_interfaces::msg::RobotStatus const>& robot_msg){

        double image_t = image_msg->header.stamp.sec + image_msg->header.stamp.nanosec*1e-9;
        double serial_t = robot_msg->header.stamp.sec + robot_msg->header.stamp.nanosec*1e-9;
        // double time_stamp = double(image_msg->header.stamp.sec)/1000.0;
        // RCLCPP_INFO(this->get_logger(), "camera sec: %lf ",image_t);
        // RCLCPP_INFO(this->get_logger(), "serial sec: %lf ",serial_t);
        // std::cout<<"\r\n"<<std::endl;



        auto src = cv_bridge::toCvShare(image_msg, "bgr8")->image;
        std::vector<OvInference::Detection> results;
        ovinfer->infer(src, results);
        
        color_check(robot_msg->color, results);
        OvInference::Detection final_obj;
        final_obj.class_id = -1;           //check if armor
        armor_sort(final_obj, results, src);
        cv::putText(src,"lock_ed id "+ std::to_string(locked_id),cv::Point (15,30),
        cv::FONT_HERSHEY_COMPLEX_SMALL,1,cv::Scalar(255,0,0));
        draw_target(final_obj,src);
        cv::Point3f cam_ = cv::Point3f(0,0,0);
        cam_ = pnpsolver->get_cam_point(final_obj);
        if(final_obj.class_id > -1){
            std::cout<< "cam_ point "<<cam_<<std::endl;
        }
        
        auto campoint_msg_ = my_interfaces::msg::Armor();
        campoint_msg_.time_stamp = image_t;
        campoint_msg_.id = final_obj.class_id;
        campoint_msg_.cam_point.x = cam_.x;
        campoint_msg_.cam_point.y = cam_.y;
        campoint_msg_.cam_point.z = cam_.z;
        campoint_msg_.robot_pitch = robot_msg->pitch;
        campoint_msg_.robot_yaw = robot_msg->yaw;
        campoint_msg_.bullet_speed = robot_msg->bullet_speed;
        campoint_msg_.robot_roll = robot_msg->roll;

        campoint_pub_->publish(campoint_msg_);
        ///TODO: publish processed image, armor information
        processed_msg_ = cv_bridge::CvImage(hdr,"bgr8",src).toImageMsg();
        display_pub_.publish(processed_msg_);
    }

int main(int argc, char** argv){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ArmorDetect>("detector_node");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;

}