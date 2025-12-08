// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from pars_msgs:msg/Data.idl
// generated code does not contain a copyright notice

#ifndef PARS_MSGS__MSG__DETAIL__DATA__STRUCT_H_
#define PARS_MSGS__MSG__DETAIL__DATA__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/Data in the package pars_msgs.
/**
  * TeamData -> Data
 */
typedef struct pars_msgs__msg__Data
{
  int32_t takim_numarasi;
  double iha_enlem;
  double iha_boylam;
  double iha_irtifa;
  double iha_yonelme;
  double iha_hizi;
} pars_msgs__msg__Data;

// Struct for a sequence of pars_msgs__msg__Data.
typedef struct pars_msgs__msg__Data__Sequence
{
  pars_msgs__msg__Data * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} pars_msgs__msg__Data__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PARS_MSGS__MSG__DETAIL__DATA__STRUCT_H_
