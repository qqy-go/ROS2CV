// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from my_interfaces:msg/Armor.idl
// generated code does not contain a copyright notice

#ifndef MY_INTERFACES__MSG__DETAIL__ARMOR__BUILDER_HPP_
#define MY_INTERFACES__MSG__DETAIL__ARMOR__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "my_interfaces/msg/detail/armor__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace my_interfaces
{

namespace msg
{

namespace builder
{

class Init_Armor_bullet_speed
{
public:
  explicit Init_Armor_bullet_speed(::my_interfaces::msg::Armor & msg)
  : msg_(msg)
  {}
  ::my_interfaces::msg::Armor bullet_speed(::my_interfaces::msg::Armor::_bullet_speed_type arg)
  {
    msg_.bullet_speed = std::move(arg);
    return std::move(msg_);
  }

private:
  ::my_interfaces::msg::Armor msg_;
};

class Init_Armor_robot_yaw
{
public:
  explicit Init_Armor_robot_yaw(::my_interfaces::msg::Armor & msg)
  : msg_(msg)
  {}
  Init_Armor_bullet_speed robot_yaw(::my_interfaces::msg::Armor::_robot_yaw_type arg)
  {
    msg_.robot_yaw = std::move(arg);
    return Init_Armor_bullet_speed(msg_);
  }

private:
  ::my_interfaces::msg::Armor msg_;
};

class Init_Armor_robot_pitch
{
public:
  explicit Init_Armor_robot_pitch(::my_interfaces::msg::Armor & msg)
  : msg_(msg)
  {}
  Init_Armor_robot_yaw robot_pitch(::my_interfaces::msg::Armor::_robot_pitch_type arg)
  {
    msg_.robot_pitch = std::move(arg);
    return Init_Armor_robot_yaw(msg_);
  }

private:
  ::my_interfaces::msg::Armor msg_;
};

class Init_Armor_cam_point
{
public:
  explicit Init_Armor_cam_point(::my_interfaces::msg::Armor & msg)
  : msg_(msg)
  {}
  Init_Armor_robot_pitch cam_point(::my_interfaces::msg::Armor::_cam_point_type arg)
  {
    msg_.cam_point = std::move(arg);
    return Init_Armor_robot_pitch(msg_);
  }

private:
  ::my_interfaces::msg::Armor msg_;
};

class Init_Armor_id
{
public:
  explicit Init_Armor_id(::my_interfaces::msg::Armor & msg)
  : msg_(msg)
  {}
  Init_Armor_cam_point id(::my_interfaces::msg::Armor::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_Armor_cam_point(msg_);
  }

private:
  ::my_interfaces::msg::Armor msg_;
};

class Init_Armor_time_stamp
{
public:
  explicit Init_Armor_time_stamp(::my_interfaces::msg::Armor & msg)
  : msg_(msg)
  {}
  Init_Armor_id time_stamp(::my_interfaces::msg::Armor::_time_stamp_type arg)
  {
    msg_.time_stamp = std::move(arg);
    return Init_Armor_id(msg_);
  }

private:
  ::my_interfaces::msg::Armor msg_;
};

class Init_Armor_header
{
public:
  Init_Armor_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Armor_time_stamp header(::my_interfaces::msg::Armor::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_Armor_time_stamp(msg_);
  }

private:
  ::my_interfaces::msg::Armor msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::my_interfaces::msg::Armor>()
{
  return my_interfaces::msg::builder::Init_Armor_header();
}

}  // namespace my_interfaces

#endif  // MY_INTERFACES__MSG__DETAIL__ARMOR__BUILDER_HPP_
