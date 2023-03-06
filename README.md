# ROS2CV

## Dependencies
- OpenVino2022
- ROS2
- Eigen

## Install
- step1 install openvino

detail contents see: <https://docs.openvino.ai/2022.3/openvino_docs_install_guides_installing_openvino_from_archive_linux.html#doxid-openvino-docs-install-guides-installing-openvino-from-archive-linux>

> Note: This only install runtime, not include develop tools.

```shell
# create install dir
sudo mkdir /opt/intel
# download
cd <user_home>/Downloads   

curl -L https://storage.openvinotoolkit.org/repositories/openvino/packages/2022.3/linux/l_openvino_toolkit_ubuntu20_2022.3.0.9052.9752fafe8eb_x86_64.tgz --output openvino_2022.3.0.tgz   

tar -xf openvino_2022.3.0.tgz   

sudo mv l_openvino_toolkit_ubuntu20_2022.3.0.9052.9752fafe8eb_x86_64 /opt/intel/openvino_2022.3.0   

#install
cd /opt/intel/openvino_2022.3.0/   

sudo -E ./install_dependencies/install_openvino_dependencies.sh

cd /opt/intel 
sudo ln -s openvino_2022.3.0 openvino_2022
# source enviroment
source /opt/intel/openvino2022/setupvars.sh

```

## step2 install ros2

> Detail installatin: <https://docs.ros.org/en/foxy/Installation/Ubuntu-Install-Debians.html>
### set locale
```shell
locale  # check for UTF-8

sudo apt update && sudo apt install locales
sudo locale-gen en_US en_US.UTF-8
sudo update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
export LANG=en_US.UTF-8

locale  # verify settings
```

### Setup Sources
```shell
sudo apt install software-properties-common
sudo add-apt-repository universe

sudo apt update && sudo apt install curl
sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg

echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null

```

### Install ROS2
```shell
sudo apt update && sudo apt upgrade
sudo apt install ros-foxy-desktop python3-argcomplete
sudo apt install ros-dev-tools
```

### Environment Setup
```shell
vim ~/.bashrc

# add this content to your file
# Replace ".bash" with your shell if you're not using bash
# Possible values are: setup.bash, setup.sh, setup.zsh
source /opt/ros/foxy/setup.bash
```

## step3 install eigen

```shell
cd <User>/Downloads   
wget https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.zip   
unzip eigen-3.4.0.zip   
cd eigen-3.4.0.zip   
mkdir build && cd build    
cmake ..   
sudo make install  
```
## Usage
clone this repo
```shell
mkdir -p <your-work-dir>/dev_ws/
cd ./dev_ws/
git clone https://github.com/ge-quanyi/ROS2CV.git
mv ROS2CV src
```
install dependencies
```shell
rosdep init
rosdep update
rosdep install --from-paths src -y --ignore-src
```
build
```shell
cd ..
colcon build 
ros2 launch robot_startup ares_cv.launch.py
chmod +x ./src/script/ros_bridge.sh
./src/script/ros_bridge.sh
```


