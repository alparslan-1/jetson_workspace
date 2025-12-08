// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from pars_msgs:msg/Data.idl
// generated code does not contain a copyright notice
#include "pars_msgs/msg/detail/data__rosidl_typesupport_fastrtps_cpp.hpp"
#include "pars_msgs/msg/detail/data__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

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
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: takim_numarasi
  cdr << ros_message.takim_numarasi;
  // Member: iha_enlem
  cdr << ros_message.iha_enlem;
  // Member: iha_boylam
  cdr << ros_message.iha_boylam;
  // Member: iha_irtifa
  cdr << ros_message.iha_irtifa;
  // Member: iha_yonelme
  cdr << ros_message.iha_yonelme;
  // Member: iha_hizi
  cdr << ros_message.iha_hizi;
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_pars_msgs
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  pars_msgs::msg::Data & ros_message)
{
  // Member: takim_numarasi
  cdr >> ros_message.takim_numarasi;

  // Member: iha_enlem
  cdr >> ros_message.iha_enlem;

  // Member: iha_boylam
  cdr >> ros_message.iha_boylam;

  // Member: iha_irtifa
  cdr >> ros_message.iha_irtifa;

  // Member: iha_yonelme
  cdr >> ros_message.iha_yonelme;

  // Member: iha_hizi
  cdr >> ros_message.iha_hizi;

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_pars_msgs
get_serialized_size(
  const pars_msgs::msg::Data & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: takim_numarasi
  {
    size_t item_size = sizeof(ros_message.takim_numarasi);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: iha_enlem
  {
    size_t item_size = sizeof(ros_message.iha_enlem);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: iha_boylam
  {
    size_t item_size = sizeof(ros_message.iha_boylam);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: iha_irtifa
  {
    size_t item_size = sizeof(ros_message.iha_irtifa);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: iha_yonelme
  {
    size_t item_size = sizeof(ros_message.iha_yonelme);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: iha_hizi
  {
    size_t item_size = sizeof(ros_message.iha_hizi);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_pars_msgs
max_serialized_size_Data(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;


  // Member: takim_numarasi
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: iha_enlem
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Member: iha_boylam
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Member: iha_irtifa
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Member: iha_yonelme
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Member: iha_hizi
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  return current_alignment - initial_alignment;
}

static bool _Data__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const pars_msgs::msg::Data *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _Data__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<pars_msgs::msg::Data *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _Data__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const pars_msgs::msg::Data *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _Data__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_Data(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _Data__callbacks = {
  "pars_msgs::msg",
  "Data",
  _Data__cdr_serialize,
  _Data__cdr_deserialize,
  _Data__get_serialized_size,
  _Data__max_serialized_size
};

static rosidl_message_type_support_t _Data__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_Data__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace pars_msgs

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_pars_msgs
const rosidl_message_type_support_t *
get_message_type_support_handle<pars_msgs::msg::Data>()
{
  return &pars_msgs::msg::typesupport_fastrtps_cpp::_Data__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, pars_msgs, msg, Data)() {
  return &pars_msgs::msg::typesupport_fastrtps_cpp::_Data__handle;
}

#ifdef __cplusplus
}
#endif
