// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from my_interfaces:msg/RobotStatus.idl
// generated code does not contain a copyright notice

#ifndef MY_INTERFACES__MSG__DETAIL__ROBOT_STATUS__BUILDER_HPP_
#define MY_INTERFACES__MSG__DETAIL__ROBOT_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "my_interfaces/msg/detail/robot_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace my_interfaces
{

namespace msg
{

namespace builder
{

class Init_RobotStatus_bullet_speed
{
public:
  explicit Init_RobotStatus_bullet_speed(::my_interfaces::msg::RobotStatus & msg)
  : msg_(msg)
  {}
  ::my_interfaces::msg::RobotStatus bullet_speed(::my_interfaces::msg::RobotStatus::_bullet_speed_type arg)
  {
    msg_.bullet_speed = std::move(arg);
    return std::move(msg_);
  }

private:
  ::my_interfaces::msg::RobotStatus msg_;
};

class Init_RobotStatus_yaw
{
public:
  explicit Init_RobotStatus_yaw(::my_interfaces::msg::RobotStatus & msg)
  : msg_(msg)
  {}
  Init_RobotStatus_bullet_speed yaw(::my_interfaces::msg::RobotStatus::_yaw_type arg)
  {
    msg_.yaw = std::move(arg);
    return Init_RobotStatus_bullet_speed(msg_);
  }

private:
  ::my_interfaces::msg::RobotStatus msg_;
};

class Init_RobotStatus_pitch
{
public:
  explicit Init_RobotStatus_pitch(::my_interfaces::msg::RobotStatus & msg)
  : msg_(msg)
  {}
  Init_RobotStatus_yaw pitch(::my_interfaces::msg::RobotStatus::_pitch_type arg)
  {
    msg_.pitch = std::move(arg);
    return Init_RobotStatus_yaw(msg_);
  }

private:
  ::my_interfaces::msg::RobotStatus msg_;
};

class Init_RobotStatus_color
{
public:
  explicit Init_RobotStatus_color(::my_interfaces::msg::RobotStatus & msg)
  : msg_(msg)
  {}
  Init_RobotStatus_pitch color(::my_interfaces::msg::RobotStatus::_color_type arg)
  {
    msg_.color = std::move(arg);
    return Init_RobotStatus_pitch(msg_);
  }

private:
  ::my_interfaces::msg::RobotStatus msg_;
};

class Init_RobotStatus_header
{
public:
  Init_RobotStatus_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RobotStatus_color header(::my_interfaces::msg::RobotStatus::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_RobotStatus_color(msg_);
  }

private:
  ::my_interfaces::msg::RobotStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::my_interfaces::msg::RobotStatus>()
{
  return my_interfaces::msg::builder::Init_RobotStatus_header();
}

}  // namespace my_interfaces

#endif  // MY_INTERFACES__MSG__DETAIL__ROBOT_STATUS__BUILDER_HPP_
