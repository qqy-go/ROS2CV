// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from my_interfaces:msg/SendData.idl
// generated code does not contain a copyright notice

#ifndef MY_INTERFACES__MSG__DETAIL__SEND_DATA__BUILDER_HPP_
#define MY_INTERFACES__MSG__DETAIL__SEND_DATA__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "my_interfaces/msg/detail/send_data__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace my_interfaces
{

namespace msg
{

namespace builder
{

class Init_SendData_dis
{
public:
  explicit Init_SendData_dis(::my_interfaces::msg::SendData & msg)
  : msg_(msg)
  {}
  ::my_interfaces::msg::SendData dis(::my_interfaces::msg::SendData::_dis_type arg)
  {
    msg_.dis = std::move(arg);
    return std::move(msg_);
  }

private:
  ::my_interfaces::msg::SendData msg_;
};

class Init_SendData_yaw
{
public:
  explicit Init_SendData_yaw(::my_interfaces::msg::SendData & msg)
  : msg_(msg)
  {}
  Init_SendData_dis yaw(::my_interfaces::msg::SendData::_yaw_type arg)
  {
    msg_.yaw = std::move(arg);
    return Init_SendData_dis(msg_);
  }

private:
  ::my_interfaces::msg::SendData msg_;
};

class Init_SendData_pitch
{
public:
  explicit Init_SendData_pitch(::my_interfaces::msg::SendData & msg)
  : msg_(msg)
  {}
  Init_SendData_yaw pitch(::my_interfaces::msg::SendData::_pitch_type arg)
  {
    msg_.pitch = std::move(arg);
    return Init_SendData_yaw(msg_);
  }

private:
  ::my_interfaces::msg::SendData msg_;
};

class Init_SendData_tg_num
{
public:
  explicit Init_SendData_tg_num(::my_interfaces::msg::SendData & msg)
  : msg_(msg)
  {}
  Init_SendData_pitch tg_num(::my_interfaces::msg::SendData::_tg_num_type arg)
  {
    msg_.tg_num = std::move(arg);
    return Init_SendData_pitch(msg_);
  }

private:
  ::my_interfaces::msg::SendData msg_;
};

class Init_SendData_header
{
public:
  Init_SendData_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SendData_tg_num header(::my_interfaces::msg::SendData::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_SendData_tg_num(msg_);
  }

private:
  ::my_interfaces::msg::SendData msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::my_interfaces::msg::SendData>()
{
  return my_interfaces::msg::builder::Init_SendData_header();
}

}  // namespace my_interfaces

#endif  // MY_INTERFACES__MSG__DETAIL__SEND_DATA__BUILDER_HPP_
