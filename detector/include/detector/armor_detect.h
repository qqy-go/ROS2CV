#include <rclcpp/rclcpp.hpp>
#include <camera_info_manager/camera_info_manager.hpp>
#include "image_transport/image_transport.h"
#include "sensor_msgs/msg/image.h"
#include "cv_bridge/cv_bridge.h"
#include "PNPSolver.hpp"
#include "ovinference.h"
#include "my_interfaces/msg/armor.hpp"


class ArmorDetect : public rclcpp::Node{

public:
    explicit ArmorDetect(const std::string& node_name);
    ~ArmorDetect()=default;
    
private:

    int8_t locked_id = -1;
    int lose_cnt = 0;
    int lock_cnt = 0;
 

    sensor_msgs::msg::Image image_mag;
    std::shared_ptr<image_transport::CameraSubscriber> camera_sub_;
    std_msgs::msg::Header pub_header_;

    image_transport::Publisher display_pub_;

    std::shared_ptr<OvInference> ovinfer;
    std::unique_ptr<PNPSolver> pnpsolver;
    sensor_msgs::msg::Image::SharedPtr processed_msg_;
    sensor_msgs::msg::CameraInfo camera_info_msg_;     //camera info message
    // std::shared_ptr<my_interfaces::msg::Armor> campoint_msg_;
    rclcpp::Subscription<sensor_msgs::msg::CameraInfo>::SharedPtr camerainfo_sub_;
    rclcpp::Publisher<my_interfaces::msg::Armor>::SharedPtr campoint_pub_;
    
    std_msgs::msg::Header hdr;

    void imageCallback(const sensor_msgs::msg::Image::ConstSharedPtr & image_msg);
    
    void color_check(const char color, std::vector<OvInference::Detection>& results);
    void armor_sort(OvInference::Detection& final_obj, std::vector<OvInference::Detection>& results, cv::Mat& src);
    void draw_target(const OvInference::Detection& obj, cv::Mat& src);


};