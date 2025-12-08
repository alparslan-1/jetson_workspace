// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from pkg_srv:srv/MissionControl.idl
// generated code does not contain a copyright notice

#ifndef PKG_SRV__SRV__DETAIL__MISSION_CONTROL__STRUCT_H_
#define PKG_SRV__SRV__DETAIL__MISSION_CONTROL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'state'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/MissionControl in the package pkg_srv.
typedef struct pkg_srv__srv__MissionControl_Request
{
  rosidl_runtime_c__String state;
} pkg_srv__srv__MissionControl_Request;

// Struct for a sequence of pkg_srv__srv__MissionControl_Request.
typedef struct pkg_srv__srv__MissionControl_Request__Sequence
{
  pkg_srv__srv__MissionControl_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} pkg_srv__srv__MissionControl_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'mission_state'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in srv/MissionControl in the package pkg_srv.
typedef struct pkg_srv__srv__MissionControl_Response
{
  rosidl_runtime_c__String mission_state;
} pkg_srv__srv__MissionControl_Response;

// Struct for a sequence of pkg_srv__srv__MissionControl_Response.
typedef struct pkg_srv__srv__MissionControl_Response__Sequence
{
  pkg_srv__srv__MissionControl_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} pkg_srv__srv__MissionControl_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PKG_SRV__SRV__DETAIL__MISSION_CONTROL__STRUCT_H_
