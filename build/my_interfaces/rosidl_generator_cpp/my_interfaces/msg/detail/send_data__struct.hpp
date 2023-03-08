// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from my_interfaces:msg/SendData.idl
// generated code does not contain a copyright notice

#ifndef MY_INTERFACES__MSG__DETAIL__SEND_DATA__STRUCT_HPP_
#define MY_INTERFACES__MSG__DETAIL__SEND_DATA__STRUCT_HPP_

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

#ifndef _WIN32
# define DEPRECATED__my_interfaces__msg__SendData __attribute__((deprecated))
#else
# define DEPRECATED__my_interfaces__msg__SendData __declspec(deprecated)
#endif

namespace my_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct SendData_
{
  using Type = SendData_<ContainerAllocator>;

  explicit SendData_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->tg_num = 0;
      this->pitch = 0.0;
      this->yaw = 0.0;
      this->dis = 0.0;
    }
  }

  explicit SendData_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->tg_num = 0;
      this->pitch = 0.0;
      this->yaw = 0.0;
      this->dis = 0.0;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _tg_num_type =
    int8_t;
  _tg_num_type tg_num;
  using _pitch_type =
    double;
  _pitch_type pitch;
  using _yaw_type =
    double;
  _yaw_type yaw;
  using _dis_type =
    double;
  _dis_type dis;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__tg_num(
    const int8_t & _arg)
  {
    this->tg_num = _arg;
    return *this;
  }
  Type & set__pitch(
    const double & _arg)
  {
    this->pitch = _arg;
    return *this;
  }
  Type & set__yaw(
    const double & _arg)
  {
    this->yaw = _arg;
    return *this;
  }
  Type & set__dis(
    const double & _arg)
  {
    this->dis = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    my_interfaces::msg::SendData_<ContainerAllocator> *;
  using ConstRawPtr =
    const my_interfaces::msg::SendData_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<my_interfaces::msg::SendData_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<my_interfaces::msg::SendData_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      my_interfaces::msg::SendData_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<my_interfaces::msg::SendData_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      my_interfaces::msg::SendData_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<my_interfaces::msg::SendData_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<my_interfaces::msg::SendData_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<my_interfaces::msg::SendData_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__my_interfaces__msg__SendData
    std::shared_ptr<my_interfaces::msg::SendData_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__my_interfaces__msg__SendData
    std::shared_ptr<my_interfaces::msg::SendData_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SendData_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->tg_num != other.tg_num) {
      return false;
    }
    if (this->pitch != other.pitch) {
      return false;
    }
    if (this->yaw != other.yaw) {
      return false;
    }
    if (this->dis != other.dis) {
      return false;
    }
    return true;
  }
  bool operator!=(const SendData_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SendData_

// alias to use template instance with default allocator
using SendData =
  my_interfaces::msg::SendData_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace my_interfaces

#endif  // MY_INTERFACES__MSG__DETAIL__SEND_DATA__STRUCT_HPP_
