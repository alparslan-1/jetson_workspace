// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from pkg_srv:srv/MissionControl.idl
// generated code does not contain a copyright notice

#ifndef PKG_SRV__SRV__DETAIL__MISSION_CONTROL__TRAITS_HPP_
#define PKG_SRV__SRV__DETAIL__MISSION_CONTROL__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "pkg_srv/srv/detail/mission_control__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace pkg_srv
{

namespace srv
{

inline void to_flow_style_yaml(
  const MissionControl_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: state
  {
    out << "state: ";
    rosidl_generator_traits::value_to_yaml(msg.state, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MissionControl_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "state: ";
    rosidl_generator_traits::value_to_yaml(msg.state, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MissionControl_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace pkg_srv

namespace rosidl_generator_traits
{

[[deprecated("use pkg_srv::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const pkg_srv::srv::MissionControl_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  pkg_srv::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use pkg_srv::srv::to_yaml() instead")]]
inline std::string to_yaml(const pkg_srv::srv::MissionControl_Request & msg)
{
  return pkg_srv::srv::to_yaml(msg);
}

template<>
inline const char * data_type<pkg_srv::srv::MissionControl_Request>()
{
  return "pkg_srv::srv::MissionControl_Request";
}

template<>
inline const char * name<pkg_srv::srv::MissionControl_Request>()
{
  return "pkg_srv/srv/MissionControl_Request";
}

template<>
struct has_fixed_size<pkg_srv::srv::MissionControl_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<pkg_srv::srv::MissionControl_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<pkg_srv::srv::MissionControl_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace pkg_srv
{

namespace srv
{

inline void to_flow_style_yaml(
  const MissionControl_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: mission_state
  {
    out << "mission_state: ";
    rosidl_generator_traits::value_to_yaml(msg.mission_state, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MissionControl_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: mission_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mission_state: ";
    rosidl_generator_traits::value_to_yaml(msg.mission_state, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MissionControl_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace pkg_srv

namespace rosidl_generator_traits
{

[[deprecated("use pkg_srv::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const pkg_srv::srv::MissionControl_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  pkg_srv::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use pkg_srv::srv::to_yaml() instead")]]
inline std::string to_yaml(const pkg_srv::srv::MissionControl_Response & msg)
{
  return pkg_srv::srv::to_yaml(msg);
}

template<>
inline const char * data_type<pkg_srv::srv::MissionControl_Response>()
{
  return "pkg_srv::srv::MissionControl_Response";
}

template<>
inline const char * name<pkg_srv::srv::MissionControl_Response>()
{
  return "pkg_srv/srv/MissionControl_Response";
}

template<>
struct has_fixed_size<pkg_srv::srv::MissionControl_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<pkg_srv::srv::MissionControl_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<pkg_srv::srv::MissionControl_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<pkg_srv::srv::MissionControl>()
{
  return "pkg_srv::srv::MissionControl";
}

template<>
inline const char * name<pkg_srv::srv::MissionControl>()
{
  return "pkg_srv/srv/MissionControl";
}

template<>
struct has_fixed_size<pkg_srv::srv::MissionControl>
  : std::integral_constant<
    bool,
    has_fixed_size<pkg_srv::srv::MissionControl_Request>::value &&
    has_fixed_size<pkg_srv::srv::MissionControl_Response>::value
  >
{
};

template<>
struct has_bounded_size<pkg_srv::srv::MissionControl>
  : std::integral_constant<
    bool,
    has_bounded_size<pkg_srv::srv::MissionControl_Request>::value &&
    has_bounded_size<pkg_srv::srv::MissionControl_Response>::value
  >
{
};

template<>
struct is_service<pkg_srv::srv::MissionControl>
  : std::true_type
{
};

template<>
struct is_service_request<pkg_srv::srv::MissionControl_Request>
  : std::true_type
{
};

template<>
struct is_service_response<pkg_srv::srv::MissionControl_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // PKG_SRV__SRV__DETAIL__MISSION_CONTROL__TRAITS_HPP_
