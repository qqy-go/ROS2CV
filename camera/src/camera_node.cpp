#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.h"
#include "camera/camera_api.h"
#include "cv_bridge/cv_bridge.h"
#include "image_transport/image_transport.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <camera_info_manager/camera_info_manager.hpp>
#include <sensor_msgs/msg/camera_info.hpp>

class Camera : public rclcpp::Node{

public:
    explicit Camera(const std::string& name, const int image_width, const int image_height) : Node(name)
    {

        RCLCPP_INFO(this -> get_logger(),"This is %s.",name.c_str());
        width = image_width;
        height = image_height;
        camera_pub_ = image_transport::create_camera_publisher(this, "/camera/image_raw", rmw_qos_profile_sensor_data); //rqt cn not receive sensor data 
        camera_info_manager_ =
      std::make_unique<camera_info_manager::CameraInfoManager>(this, "daheng159",
      "file:///home/ares/workspace/dev_ws/src/camera/params/daheng159.yaml");
    
        camera_info_msg_ = camera_info_manager_->getCameraInfo();
        //create timer
        camera_timer_ = this->create_wall_timer(std::chrono::milliseconds(5),std::bind(&Camera::camera_publish_callback,this));

        //Industry Camera init
        GX_STATUS status = Config();
        if (status != GX_STATUS_SUCCESS) {
            RCLCPP_ERROR(this-> get_logger(), "Config Camera Faile...");
            exit(-1);
        }
        cam0_info.sn_str = "KE0200120159";
        cam0_info.SN = &cam0_info.sn_str[0];

        cam0 = std::make_unique<MercureDriver>(cam0_info);
        cam0->InitCamera();
        if (cam0->status != GX_STATUS_SUCCESS) {
            RCLCPP_ERROR(this-> get_logger(), "Initial Camera Faile...");
            exit(-1);
        }
        
        status = GXStreamOn(cam0->hDevice_);
        if(status != GX_STATUS_SUCCESS){
            RCLCPP_ERROR(this-> get_logger(), "Camera start stream error!!!");
            exit(-1);
        }
        image_msg_.data.reserve(width * height *3);
        image_msg_.header.frame_id = "daheng__";
        image_msg_.encoding = "bgr8";    
    }

    ~Camera(){
        GXStreamOff(cam0->hDevice_);
        cam0->StopCamera();
    };
    

    private:

    int width,height;
    
    camera_config cam0_info;          //struct
    std::unique_ptr<MercureDriver> cam0;
    sensor_msgs::msg::Image image_msg_;
    image_transport::CameraPublisher camera_pub_;
    sensor_msgs::msg::CameraInfo camera_info_msg_;
    std::unique_ptr<camera_info_manager::CameraInfoManager> camera_info_manager_;
    rclcpp::TimerBase::SharedPtr camera_timer_;
    PGX_FRAME_BUFFER pFrameBuffer;

    void camera_publish_callback(){
        GX_STATUS status = GXDQBuf(cam0->hDevice_, &pFrameBuffer, 1000);
        if(status == GX_STATUS_SUCCESS){
            if(pFrameBuffer->nStatus == GX_FRAME_STATUS_SUCCESS){
                DX_BAYER_CONVERT_TYPE cvtype = RAW2RGB_NEIGHBOUR;           //选择插值算法
                DX_PIXEL_COLOR_FILTER nBayerType = BAYERBG;              //选择图像Bayer格式
                VxInt32 DxStatus = DxRaw8toRGB24(const_cast<void *>(pFrameBuffer->pImgBuf), image_msg_.data.data(), pFrameBuffer->nWidth,
                                                 pFrameBuffer->nHeight, cvtype, nBayerType, false);
                if(DxStatus == DX_OK){
                    
                    // camera_info_msg_.header.stamp.sec= image_msg_.header.stamp.sec = tic->this_time(); //TODO :check if use or not
                    camera_info_msg_.header.stamp= image_msg_.header.stamp = this->get_clock()->now(); //TODO :check if use or not
                    image_msg_.height = pFrameBuffer->nHeight;
                    image_msg_.width = pFrameBuffer->nWidth;
                    image_msg_.step = pFrameBuffer->nWidth * 3;             //three channels 
                    image_msg_.data.resize(pFrameBuffer->nWidth * pFrameBuffer->nHeight * 3);
                    camera_pub_.publish(image_msg_, camera_info_msg_);       
                }
            }
            status = GXQBuf(cam0->hDevice_, pFrameBuffer);
        }
    
    }

};




int main(int argc, char** argv){
    rclcpp::init(argc, argv);
    
    auto node = std::make_shared<Camera>("camera_node", 960, 768);
    rclcpp::spin(node);
    rclcpp::shutdown();

}