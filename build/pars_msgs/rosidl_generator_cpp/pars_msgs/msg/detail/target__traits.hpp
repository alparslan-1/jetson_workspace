// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from pars_msgs:msg/Target.idl
// generated code does not contain a copyright notice

#ifndef PARS_MSGS__MSG__DETAIL__TARGET__TRAITS_HPP_
#define PARS_MSGS__MSG__DETAIL__TARGET__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "pars_msgs/msg/detail/target__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace pars_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const Target & msg,
  std::ostream & out)
{
  out << "{";
  // member: target_detected
  {
    out << "target_detected: ";
    rosidl_generator_traits::value_to_yaml(msg.target_detected, out);
    out << ", ";
  }

  // member: x_center
  {
    out << "x_center: ";
    rosidl_generator_traits::value_to_yaml(msg.x_center, out);
    out << ", ";
  }

  // member: y_center
  {
    out << "y_center: ";
    rosidl_generator_traits::value_to_yaml(msg.y_center, out);
    out << ", ";
  }

  // member: image_width
  {
    out << "image_width: ";
    rosidl_generator_traits::value_to_yaml(msg.image_width, out);
    out << ", ";
  }

  // member: image_height
  {
    out << "image_height: ";
    rosidl_generator_traits::value_to_yaml(msg.image_height, out);
    out << ", ";
  }

  // member: hedef_boyut
  {
    out << "hedef_boyut: ";
    rosidl_generator_traits::value_to_yaml(msg.hedef_boyut, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Target & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: target_detected
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "target_detected: ";
    rosidl_generator_traits::value_to_yaml(msg.target_detected, out);
    out << "\n";
  }

  // member: x_center
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x_center: ";
    rosidl_generator_traits::value_to_yaml(msg.x_center, out);
    out << "\n";
  }

  // member: y_center
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y_center: ";
    rosidl_generator_traits::value_to_yaml(msg.y_center, out);
    out << "\n";
  }

  // member: image_width
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "image_width: ";
    rosidl_generator_traits::value_to_yaml(msg.image_width, out);
    out << "\n";
  }

  // member: image_height
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "image_height: ";
    rosidl_generator_traits::value_to_yaml(msg.image_height, out);
    out << "\n";
  }

  // member: hedef_boyut
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "hedef_boyut: ";
    rosidl_generator_traits::value_to_yaml(msg.hedef_boyut, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Target & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace pars_msgs

namespace rosidl_generator_traits
{

[[deprecated("use pars_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const pars_msgs::msg::Target & msg,
  std::ostream & out, size_t indentation = 0)
{
  pars_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use pars_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const pars_msgs::msg::Target & msg)
{
  return pars_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<pars_msgs::msg::Target>()
{
  return "pars_msgs::msg::Target";
}

template<>
inline const char * name<pars_msgs::msg::Target>()
{
  return "pars_msgs/msg/Target";
}

template<>
struct has_fixed_size<pars_msgs::msg::Target>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<pars_msgs::msg::Target>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<pars_msgs::msg::Target>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // PARS_MSGS__MSG__DETAIL__TARGET__TRAITS_HPP_
