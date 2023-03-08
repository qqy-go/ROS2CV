// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from my_interfaces:msg/Armor.idl
// generated code does not contain a copyright notice

#ifndef MY_INTERFACES__MSG__DETAIL__ARMOR__STRUCT_H_
#define MY_INTERFACES__MSG__DETAIL__ARMOR__STRUCT_H_

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
// Member 'cam_point'
#include "geometry_msgs/msg/detail/point__struct.h"

/// Struct defined in msg/Armor in the package my_interfaces.
typedef struct my_interfaces__msg__Armor
{
  std_msgs__msg__Header header;
  double time_stamp;
  int8_t id;
  geometry_msgs__msg__Point cam_point;
  float robot_pitch;
  float robot_yaw;
  float bullet_speed;
} my_interfaces__msg__Armor;

// Struct for a sequence of my_interfaces__msg__Armor.
typedef struct my_interfaces__msg__Armor__Sequence
{
  my_interfaces__msg__Armor * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} my_interfaces__msg__Armor__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MY_INTERFACES__MSG__DETAIL__ARMOR__STRUCT_H_
