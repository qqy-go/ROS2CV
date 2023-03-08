// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from my_interfaces:msg/Armor.idl
// generated code does not contain a copyright notice

#ifndef MY_INTERFACES__MSG__DETAIL__ARMOR__STRUCT_HPP_
#define MY_INTERFACES__MSG__DETAIL__ARMOR__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"
// Member 'cam_point'
#include "geometry_msgs/msg/detail/point__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__my_interfaces__msg__Armor __attribute__((deprecated))
#else
# define DEPRECATED__my_interfaces__msg__Armor __declspec(deprecated)
#endif

namespace my_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Armor_
{
  using Type = Armor_<ContainerAllocator>;

  explicit Armor_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    cam_point(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->time_stamp = 0.0;
      this->id = 0;
      this->robot_pitch = 0.0f;
      this->robot_yaw = 0.0f;
      this->bullet_speed = 0.0f;
    }
  }

  explicit Armor_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    cam_point(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->time_stamp = 0.0;
      this->id = 0;
      this->robot_pitch = 0.0f;
      this->robot_yaw = 0.0f;
      this->bullet_speed = 0.0f;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _time_stamp_type =
    double;
  _time_stamp_type time_stamp;
  using _id_type =
    int8_t;
  _id_type id;
  using _cam_point_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _cam_point_type cam_point;
  using _robot_pitch_type =
    float;
  _robot_pitch_type robot_pitch;
  using _robot_yaw_type =
    float;
  _robot_yaw_type robot_yaw;
  using _bullet_speed_type =
    float;
  _bullet_speed_type bullet_speed;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__time_stamp(
    const double & _arg)
  {
    this->time_stamp = _arg;
    return *this;
  }
  Type & set__id(
    const int8_t & _arg)
  {
    this->id = _arg;
    return *this;
  }
  Type & set__cam_point(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->cam_point = _arg;
    return *this;
  }
  Type & set__robot_pitch(
    const float & _arg)
  {
    this->robot_pitch = _arg;
    return *this;
  }
  Type & set__robot_yaw(
    const float & _arg)
  {
    this->robot_yaw = _arg;
    return *this;
  }
  Type & set__bullet_speed(
    const float & _arg)
  {
    this->bullet_speed = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    my_interfaces::msg::Armor_<ContainerAllocator> *;
  using ConstRawPtr =
    const my_interfaces::msg::Armor_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<my_interfaces::msg::Armor_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<my_interfaces::msg::Armor_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      my_interfaces::msg::Armor_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<my_interfaces::msg::Armor_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      my_interfaces::msg::Armor_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<my_interfaces::msg::Armor_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<my_interfaces::msg::Armor_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<my_interfaces::msg::Armor_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__my_interfaces__msg__Armor
    std::shared_ptr<my_interfaces::msg::Armor_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__my_interfaces__msg__Armor
    std::shared_ptr<my_interfaces::msg::Armor_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Armor_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->time_stamp != other.time_stamp) {
      return false;
    }
    if (this->id != other.id) {
      return false;
    }
    if (this->cam_point != other.cam_point) {
      return false;
    }
    if (this->robot_pitch != other.robot_pitch) {
      return false;
    }
    if (this->robot_yaw != other.robot_yaw) {
      return false;
    }
    if (this->bullet_speed != other.bullet_speed) {
      return false;
    }
    return true;
  }
  bool operator!=(const Armor_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Armor_

// alias to use template instance with default allocator
using Armor =
  my_interfaces::msg::Armor_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace my_interfaces

#endif  // MY_INTERFACES__MSG__DETAIL__ARMOR__STRUCT_HPP_
