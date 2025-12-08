// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from pars_msgs:msg/Data.idl
// generated code does not contain a copyright notice

#ifndef PARS_MSGS__MSG__DETAIL__DATA__TRAITS_HPP_
#define PARS_MSGS__MSG__DETAIL__DATA__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "pars_msgs/msg/detail/data__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace pars_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const Data & msg,
  std::ostream & out)
{
  out << "{";
  // member: takim_numarasi
  {
    out << "takim_numarasi: ";
    rosidl_generator_traits::value_to_yaml(msg.takim_numarasi, out);
    out << ", ";
  }

  // member: iha_enlem
  {
    out << "iha_enlem: ";
    rosidl_generator_traits::value_to_yaml(msg.iha_enlem, out);
    out << ", ";
  }

  // member: iha_boylam
  {
    out << "iha_boylam: ";
    rosidl_generator_traits::value_to_yaml(msg.iha_boylam, out);
    out << ", ";
  }

  // member: iha_irtifa
  {
    out << "iha_irtifa: ";
    rosidl_generator_traits::value_to_yaml(msg.iha_irtifa, out);
    out << ", ";
  }

  // member: iha_yonelme
  {
    out << "iha_yonelme: ";
    rosidl_generator_traits::value_to_yaml(msg.iha_yonelme, out);
    out << ", ";
  }

  // member: iha_hizi
  {
    out << "iha_hizi: ";
    rosidl_generator_traits::value_to_yaml(msg.iha_hizi, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Data & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: takim_numarasi
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "takim_numarasi: ";
    rosidl_generator_traits::value_to_yaml(msg.takim_numarasi, out);
    out << "\n";
  }

  // member: iha_enlem
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "iha_enlem: ";
    rosidl_generator_traits::value_to_yaml(msg.iha_enlem, out);
    out << "\n";
  }

  // member: iha_boylam
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "iha_boylam: ";
    rosidl_generator_traits::value_to_yaml(msg.iha_boylam, out);
    out << "\n";
  }

  // member: iha_irtifa
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "iha_irtifa: ";
    rosidl_generator_traits::value_to_yaml(msg.iha_irtifa, out);
    out << "\n";
  }

  // member: iha_yonelme
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "iha_yonelme: ";
    rosidl_generator_traits::value_to_yaml(msg.iha_yonelme, out);
    out << "\n";
  }

  // member: iha_hizi
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "iha_hizi: ";
    rosidl_generator_traits::value_to_yaml(msg.iha_hizi, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Data & msg, bool use_flow_style = false)
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
  const pars_msgs::msg::Data & msg,
  std::ostream & out, size_t indentation = 0)
{
  pars_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use pars_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const pars_msgs::msg::Data & msg)
{
  return pars_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<pars_msgs::msg::Data>()
{
  return "pars_msgs::msg::Data";
}

template<>
inline const char * name<pars_msgs::msg::Data>()
{
  return "pars_msgs/msg/Data";
}

template<>
struct has_fixed_size<pars_msgs::msg::Data>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<pars_msgs::msg::Data>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<pars_msgs::msg::Data>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // PARS_MSGS__MSG__DETAIL__DATA__TRAITS_HPP_
