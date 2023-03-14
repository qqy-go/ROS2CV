#ifndef __PNP_
#define __PNP_
#include <opencv2/opencv.hpp>
#include "ovinference.h"


class PNPSolver{
public:

    explicit PNPSolver(const std::array<double, 9>& camera_matrix, const std::vector<double>& distortion):
    K_(cv::Mat(3, 3, CV_64F, const_cast<double *>(camera_matrix.data())).clone()), \
    D_(cv::Mat(1, 5, CV_64F, const_cast<double *>(distortion.data())).clone()){
        std::cout<<"K "<<K_<<" d "<<D_<<std::endl;
    }

    cv::Point3f get_cam_point(const OvInference::Detection& obj){
        if(obj.class_id<0)
            return cv::Point3f(0,0,0);
        object_corners.clear();
        image_points.clear();
        cv::Point3f tmp_point;
        if(obj.class_id==0||obj.class_id==9||obj.class_id==1||
                obj.class_id==10||obj.class_id==8||obj.class_id==17){
            for (int i = 0; i < 4; i++){
                tmp_point = {armor_big_pt[i][0],armor_big_pt[i][1],0};
                object_corners.push_back(tmp_point);
            }
        }else{
            for(int i=0; i<4; i++){
                tmp_point = {armor_small_pt[i][0],armor_small_pt[i][1], 0};
                object_corners.push_back(tmp_point);
            }
        }
        image_points = {obj.obj.p1,obj.obj.p2,obj.obj.p3,obj.obj.p4};

        cv::Mat rvec, tvec;
        cv::solvePnP(cv::Mat(object_corners), cv::Mat(image_points), K_, D_, rvec, tvec, false);
        double X = tvec.at<double>(2, 0);
        double Y = -tvec.at<double>(0, 0);
        double Z = -tvec.at<double>(1, 0);
        return cv::Point3f(X, Y, Z);

    }
    

private:

    const cv::Mat K_;
    const cv::Mat D_;

    std::vector<cv::Point3f> object_corners;
    std::vector<cv::Point2f> image_points;
    const float armor_small_pt[4][2] = {
        -0.0675, 0.0275,
        -0.0675, -0.0275,
        0.0675, -0.0275,
        0.0675, 0.0275,
    };

    const float armor_big_pt[4][2] = {
        -0.1125, 0.0275,    //lu
        -0.1125, -0.0275,    //上
        0.1125, -0.0275,   //左
        0.1125, 0.0275,   //下
    };
    

};





#endif
