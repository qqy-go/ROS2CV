#!/bin/bash
export ROS_LOG_DIR=/home/ares/workspace/dev_ws/log
source /opt/intel/openvino2022/setupvars.sh
source /opt/ros/foxy/setup.sh
source /home/ares/workspace/dev_ws/install/setup.bash
cd /home/ares/workspace/dev_ws
PID=`ps -ef | grep "ros2 launch robot_startup ares_cv.launch.py" | grep -v grep | awk '{print $2}'`
if [ "$PIDS" != "" ]; then
        echo "ros_cli is running!!!!!!!"
else
	ros2 launch robot_startup ares_cv.launch.py > /home/ares/workspace/dev_ws/running.log
fi
