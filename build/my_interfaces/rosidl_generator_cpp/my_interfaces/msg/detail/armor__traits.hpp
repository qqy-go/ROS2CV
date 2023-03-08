// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from my_interfaces:msg/Armor.idl
// generated code does not contain a copyright notice

#ifndef MY_INTERFACES__MSG__DETAIL__ARMOR__TRAITS_HPP_
#define MY_INTERFACES__MSG__DETAIL__ARMOR__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "my_interfaces/msg/detail/armor__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'cam_point'
#include "geometry_msgs/msg/detail/point__traits.hpp"

namespace my_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const Armor & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: time_stamp
  {
    out << "time_stamp: ";
    rosidl_generator_traits::value_to_yaml(msg.time_stamp, out);
    out << ", ";
  }

  // member: id
  {
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << ", ";
  }

  // member: cam_point
  {
    out << "cam_point: ";
    to_flow_style_yaml(msg.cam_point, out);
    out << ", ";
  }

  // member: robot_pitch
  {
    out << "robot_pitch: ";
    rosidl_generator_traits::value_to_yaml(msg.robot_pitch, out);
    out << ", ";
  }

  // member: robot_yaw
  {
    out << "robot_yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.robot_yaw, out);
    out << ", ";
  }

  // member: bullet_speed
  {
    out << "bullet_speed: ";
    rosidl_generator_traits::value_to_yaml(msg.bullet_speed, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Armor & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: time_stamp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "time_stamp: ";
    rosidl_generator_traits::value_to_yaml(msg.time_stamp, out);
    out << "\n";
  }

  // member: id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << "\n";
  }

  // member: cam_point
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cam_point:\n";
    to_block_style_yaml(msg.cam_point, out, indentation + 2);
  }

  // member: robot_pitch
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "robot_pitch: ";
    rosidl_generator_traits::value_to_yaml(msg.robot_pitch, out);
    out << "\n";
  }

  // member: robot_yaw
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "robot_yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.robot_yaw, out);
    out << "\n";
  }

  // member: bullet_speed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "bullet_speed: ";
    rosidl_generator_traits::value_to_yaml(msg.bullet_speed, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Armor & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace my_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use my_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const my_interfaces::msg::Armor & msg,
  std::ostream & out, size_t indentation = 0)
{
  my_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use my_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const my_interfaces::msg::Armor & msg)
{
  return my_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<my_interfaces::msg::Armor>()
{
  return "my_interfaces::msg::Armor";
}

template<>
inline const char * name<my_interfaces::msg::Armor>()
{
  return "my_interfaces/msg/Armor";
}

template<>
struct has_fixed_size<my_interfaces::msg::Armor>
  : std::integral_constant<bool, has_fixed_size<geometry_msgs::msg::Point>::value && has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<my_interfaces::msg::Armor>
  : std::integral_constant<bool, has_bounded_size<geometry_msgs::msg::Point>::value && has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<my_interfaces::msg::Armor>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MY_INTERFACES__MSG__DETAIL__ARMOR__TRAITS_HPP_
