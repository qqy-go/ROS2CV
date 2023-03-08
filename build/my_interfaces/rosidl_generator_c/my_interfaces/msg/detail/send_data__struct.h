// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from my_interfaces:msg/SendData.idl
// generated code does not contain a copyright notice

#ifndef MY_INTERFACES__MSG__DETAIL__SEND_DATA__STRUCT_H_
#define MY_INTERFACES__MSG__DETAIL__SEND_DATA__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"

/// Struct defined in msg/SendData in the package my_interfaces.
typedef struct my_interfaces__msg__SendData
{
  std_msgs__msg__Header header;
  int8_t tg_num;
  double pitch;
  double yaw;
  double dis;
} my_interfaces__msg__SendData;

// Struct for a sequence of my_interfaces__msg__SendData.
typedef struct my_interfaces__msg__SendData__Sequence
{
  my_interfaces__msg__SendData * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} my_interfaces__msg__SendData__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MY_INTERFACES__MSG__DETAIL__SEND_DATA__STRUCT_H_
