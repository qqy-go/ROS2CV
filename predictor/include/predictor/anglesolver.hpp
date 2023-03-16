#pragma once

#include <eigen3/Eigen/Eigen>
#include "../../../include/data_type.h"
using namespace Eigen;

class AngleSolver{
public:
    explicit AngleSolver(){
        // cv::FileStorage fs1("../params/params.yaml",cv::FileStorage::READ);
        // if(!fs1.isOpened()){
        //     std::cout<<"[ERROR ] read params file failed"<<std::endl;
        //     exit(-1);
        // }
        // fs1["sentry_up"]["pitch_diff"]>>pitch_diff;
        // fs1["sentry_up"]["yaw_diff"]>>yaw_diff;
        // std::cout<<pitch_diff<<" "<<yaw_diff<<std::endl;
        // fs1.release();

        trans <<1,0,0,  0.01,   //                     x
                0,1,0,  -0.1788,   //-0.0455             y
                0,0,1,  0.0056,  //0.1415              //z
                0,0,0,  1;
    }
    ~AngleSolver()=default;

    cv::Point3f cam2abs(const cv::Point3f& camPoint, const RobotInfo& robot) {
        getRotX(-robot.ptz_pitch);
        getRotY(robot.ptz_roll);
        getRotZ(robot.ptz_yaw);
        getRotZ_cam2imu(-3.14159/2);



        pointMat << camPoint.x, camPoint.y, camPoint.z, 1;
        auto result =   RotY*RotX*RotZ*trans*RotZ2*pointMat; // ZXY
        return cv::Point3f (result(0,0),result(1,0),result(2,0));
    }

    cv::Point3f abs2cam(const cv::Point3f& absPoint, const RobotInfo& robot) {
        getRotX(-robot.ptz_pitch);
        getRotY(robot.ptz_roll);
        getRotZ(robot.ptz_yaw);
        getRotZ_cam2imu(-3.14159/2);

        absPointMat << absPoint.x, absPoint.y, absPoint.z ,1;
        auto T = RotY*RotX*RotZ*trans*RotZ2;
        auto camPointMat = T.inverse()*absPointMat;
        return cv::Point3f (camPointMat(0,0),camPointMat(1,0),camPointMat(2,0));

    }

//     void getAngle(const cv::Point3f& cam_, double &pitch, double &yaw, double &Dis, RobotInfo stm) {
//         cv::Point3f gun_ = cam2gun(cam_, cam2gunDiff);
//         pitch = atan(gun_.y / sqrt(gun_.x * gun_.x + gun_.z * gun_.z));//more big more down
//         yaw = atan(gun_.x / gun_.z); //more big more right
//         Dis = sqrt(gun_.x * gun_.x + gun_.z * gun_.z +gun_.y*gun_.y);

//         double ptz_pitch = stm.ptz_pitch;
//         double d_speed = stm.bullet_speed;


//         //std::cout<<"ppppppppppppppppppppppppp "<<ptz_pitch<<std::endl;
//         double abs_pitch = -1 * pitch - ptz_pitch;
//         //abs_pitch = pitch + ptz_pitch;
//         int if_fix = 1;
//         if (if_fix) {
//             //abs_pitch = -abs_pitch;
//             double angle_fix = 0.5 *
//                                (asin((9.8 * Dis * pow(cos(abs_pitch), 2)) / pow(d_speed, 2) - sin(abs_pitch)) +
//                                 abs_pitch);
// //        std::cout << "angle fix " << angle_fix << std::endl;
//             abs_pitch += angle_fix;
//         }
//         pitch = -abs_pitch - ptz_pitch;

//         pitch += pitch_diff;//-0.010
//         yaw += yaw_diff;//-0.023
//     }

    void getAngle_nofix(const cv::Point3f& cam_, double &pitch, double &yaw, double &Dis) {
        // cv::Point3f gun_ = cam2gun(cam_, cam2gunDiff);
        pitch = atan(cam_.z / sqrt(cam_.x * cam_.x + cam_.y * cam_.y));//more big more down
        yaw = atan(cam_.y / cam_.x); //more big more right
        Dis = sqrt(cam_.x * cam_.x + cam_.z * cam_.z +cam_.y*cam_.y);
    }

private:



    float pitch_diff;
    float yaw_diff;

    cv::Point3f cam2gunDiff = cv::Point3f(0, -0.0395, 0.0805);
    cv::Point3f gun2ptzDiff = cv::Point3f(0, -0.006, 0.061);

    Matrix<double, 4, 4> trans;
    Matrix<double,4, 4> RotX;
    Matrix<double, 4,4> RotY;
    Matrix<double , 4, 4>RotZ;
     Matrix<double , 4, 4>RotZ2;
    Matrix<double , 4, 4>Rot;
    Matrix<double, 4,1> pointMat;
    Matrix<double, 4,1> absPointMat;

    inline void getRotX(double pitch) {
        RotX << 1,             0,             0, 0,
                0, cos(pitch), -sin(pitch), 0,
                0, sin(pitch), cos(pitch),  0,
                0,             0,             0,  1;
    }
    inline void getRotY(double yaw) {
        RotY << cos(yaw), 0, sin(yaw), 0,
                0,           1,           0, 0,
                -sin(yaw), 0, cos(yaw), 0,
                0,            0,          0, 1;
    }
    inline void getRotZ(double roll) {
        RotZ << cos(roll), -sin(roll), 0, 0,
                sin(roll), cos(roll), 0, 0,
                0,                       0, 1, 0,
                0,                       0, 0, 1;
    }

    inline void getRotZ_cam2imu(double roll) {
        RotZ2 << cos(roll), -sin(roll), 0, 0,
                sin(roll), cos(roll), 0, 0,
                0,                       0, 1, 0,
                0,                       0, 0, 1;
    }

    cv::Point3f cam2gun(cv::Point3f cam_, cv::Point3f diff) {
        return cv::Point3f(cam_.x + diff.x, cam_.y + diff.y, cam_.z + diff.z);
    }

    cv::Point3f gun2cam(cv::Point3f gun_, cv::Point3f diff) {
        return cv::Point3f(gun_.x - diff.x, gun_.y - diff.y, gun_.z - diff.z);
    }

    cv::Point3f gun2ptz(cv::Point3f gun_, cv::Point3f diff) {
        return cv::Point3f(gun_.x + diff.x, gun_.y + diff.y, +gun_.z + diff.z);
    }


};