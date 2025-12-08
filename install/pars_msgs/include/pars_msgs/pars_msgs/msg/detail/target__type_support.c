// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from pars_msgs:msg/Target.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "pars_msgs/msg/detail/target__rosidl_typesupport_introspection_c.h"
#include "pars_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "pars_msgs/msg/detail/target__functions.h"
#include "pars_msgs/msg/detail/target__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void pars_msgs__msg__Target__rosidl_typesupport_introspection_c__Target_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  pars_msgs__msg__Target__init(message_memory);
}

void pars_msgs__msg__Target__rosidl_typesupport_introspection_c__Target_fini_function(void * message_memory)
{
  pars_msgs__msg__Target__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember pars_msgs__msg__Target__rosidl_typesupport_introspection_c__Target_message_member_array[5] = {
  {
    "target_detected",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(pars_msgs__msg__Target, target_detected),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "x_center",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(pars_msgs__msg__Target, x_center),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "y_center",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(pars_msgs__msg__Target, y_center),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "image_width",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(pars_msgs__msg__Target, image_width),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "image_height",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(pars_msgs__msg__Target, image_height),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers pars_msgs__msg__Target__rosidl_typesupport_introspection_c__Target_message_members = {
  "pars_msgs__msg",  // message namespace
  "Target",  // message name
  5,  // number of fields
  sizeof(pars_msgs__msg__Target),
  pars_msgs__msg__Target__rosidl_typesupport_introspection_c__Target_message_member_array,  // message members
  pars_msgs__msg__Target__rosidl_typesupport_introspection_c__Target_init_function,  // function to initialize message memory (memory has to be allocated)
  pars_msgs__msg__Target__rosidl_typesupport_introspection_c__Target_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t pars_msgs__msg__Target__rosidl_typesupport_introspection_c__Target_message_type_support_handle = {
  0,
  &pars_msgs__msg__Target__rosidl_typesupport_introspection_c__Target_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_pars_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, pars_msgs, msg, Target)() {
  if (!pars_msgs__msg__Target__rosidl_typesupport_introspection_c__Target_message_type_support_handle.typesupport_identifier) {
    pars_msgs__msg__Target__rosidl_typesupport_introspection_c__Target_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &pars_msgs__msg__Target__rosidl_typesupport_introspection_c__Target_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
