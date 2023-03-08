// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from my_interfaces:msg/Armor.idl
// generated code does not contain a copyright notice
#include "my_interfaces/msg/detail/armor__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `cam_point`
#include "geometry_msgs/msg/detail/point__functions.h"

bool
my_interfaces__msg__Armor__init(my_interfaces__msg__Armor * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    my_interfaces__msg__Armor__fini(msg);
    return false;
  }
  // time_stamp
  // id
  // cam_point
  if (!geometry_msgs__msg__Point__init(&msg->cam_point)) {
    my_interfaces__msg__Armor__fini(msg);
    return false;
  }
  // robot_pitch
  // robot_yaw
  // bullet_speed
  return true;
}

void
my_interfaces__msg__Armor__fini(my_interfaces__msg__Armor * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // time_stamp
  // id
  // cam_point
  geometry_msgs__msg__Point__fini(&msg->cam_point);
  // robot_pitch
  // robot_yaw
  // bullet_speed
}

bool
my_interfaces__msg__Armor__are_equal(const my_interfaces__msg__Armor * lhs, const my_interfaces__msg__Armor * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // time_stamp
  if (lhs->time_stamp != rhs->time_stamp) {
    return false;
  }
  // id
  if (lhs->id != rhs->id) {
    return false;
  }
  // cam_point
  if (!geometry_msgs__msg__Point__are_equal(
      &(lhs->cam_point), &(rhs->cam_point)))
  {
    return false;
  }
  // robot_pitch
  if (lhs->robot_pitch != rhs->robot_pitch) {
    return false;
  }
  // robot_yaw
  if (lhs->robot_yaw != rhs->robot_yaw) {
    return false;
  }
  // bullet_speed
  if (lhs->bullet_speed != rhs->bullet_speed) {
    return false;
  }
  return true;
}

bool
my_interfaces__msg__Armor__copy(
  const my_interfaces__msg__Armor * input,
  my_interfaces__msg__Armor * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // time_stamp
  output->time_stamp = input->time_stamp;
  // id
  output->id = input->id;
  // cam_point
  if (!geometry_msgs__msg__Point__copy(
      &(input->cam_point), &(output->cam_point)))
  {
    return false;
  }
  // robot_pitch
  output->robot_pitch = input->robot_pitch;
  // robot_yaw
  output->robot_yaw = input->robot_yaw;
  // bullet_speed
  output->bullet_speed = input->bullet_speed;
  return true;
}

my_interfaces__msg__Armor *
my_interfaces__msg__Armor__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  my_interfaces__msg__Armor * msg = (my_interfaces__msg__Armor *)allocator.allocate(sizeof(my_interfaces__msg__Armor), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(my_interfaces__msg__Armor));
  bool success = my_interfaces__msg__Armor__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
my_interfaces__msg__Armor__destroy(my_interfaces__msg__Armor * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    my_interfaces__msg__Armor__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
my_interfaces__msg__Armor__Sequence__init(my_interfaces__msg__Armor__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  my_interfaces__msg__Armor * data = NULL;

  if (size) {
    data = (my_interfaces__msg__Armor *)allocator.zero_allocate(size, sizeof(my_interfaces__msg__Armor), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = my_interfaces__msg__Armor__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        my_interfaces__msg__Armor__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
my_interfaces__msg__Armor__Sequence__fini(my_interfaces__msg__Armor__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      my_interfaces__msg__Armor__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

my_interfaces__msg__Armor__Sequence *
my_interfaces__msg__Armor__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  my_interfaces__msg__Armor__Sequence * array = (my_interfaces__msg__Armor__Sequence *)allocator.allocate(sizeof(my_interfaces__msg__Armor__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = my_interfaces__msg__Armor__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
my_interfaces__msg__Armor__Sequence__destroy(my_interfaces__msg__Armor__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    my_interfaces__msg__Armor__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
my_interfaces__msg__Armor__Sequence__are_equal(const my_interfaces__msg__Armor__Sequence * lhs, const my_interfaces__msg__Armor__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!my_interfaces__msg__Armor__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
my_interfaces__msg__Armor__Sequence__copy(
  const my_interfaces__msg__Armor__Sequence * input,
  my_interfaces__msg__Armor__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(my_interfaces__msg__Armor);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    my_interfaces__msg__Armor * data =
      (my_interfaces__msg__Armor *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!my_interfaces__msg__Armor__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          my_interfaces__msg__Armor__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!my_interfaces__msg__Armor__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
