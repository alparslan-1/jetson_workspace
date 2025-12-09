// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from pars_msgs:msg/Target.idl
// generated code does not contain a copyright notice

#ifndef PARS_MSGS__MSG__DETAIL__TARGET__STRUCT_H_
#define PARS_MSGS__MSG__DETAIL__TARGET__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/Target in the package pars_msgs.
typedef struct pars_msgs__msg__Target
{
  bool target_detected;
  float x_center;
  float y_center;
  float image_width;
  float image_height;
  float hedef_boyut;
} pars_msgs__msg__Target;

// Struct for a sequence of pars_msgs__msg__Target.
typedef struct pars_msgs__msg__Target__Sequence
{
  pars_msgs__msg__Target * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} pars_msgs__msg__Target__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PARS_MSGS__MSG__DETAIL__TARGET__STRUCT_H_
