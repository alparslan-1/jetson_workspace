// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from pars_msgs:msg/Data.idl
// generated code does not contain a copyright notice

#ifndef PARS_MSGS__MSG__DETAIL__DATA__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define PARS_MSGS__MSG__DETAIL__DATA__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "pars_msgs/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "pars_msgs/msg/detail/data__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace pars_msgs
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_pars_msgs
cdr_serialize(
  const pars_msgs::msg::Data & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_pars_msgs
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  pars_msgs::msg::Data & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_pars_msgs
get_serialized_size(
  const pars_msgs::msg::Data & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_pars_msgs
max_serialized_size_Data(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace pars_msgs

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_pars_msgs
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, pars_msgs, msg, Data)();

#ifdef __cplusplus
}
#endif

#endif  // PARS_MSGS__MSG__DETAIL__DATA__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
