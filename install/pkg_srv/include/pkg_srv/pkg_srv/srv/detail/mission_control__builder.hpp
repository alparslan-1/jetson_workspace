// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from pkg_srv:srv/MissionControl.idl
// generated code does not contain a copyright notice

#ifndef PKG_SRV__SRV__DETAIL__MISSION_CONTROL__BUILDER_HPP_
#define PKG_SRV__SRV__DETAIL__MISSION_CONTROL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "pkg_srv/srv/detail/mission_control__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace pkg_srv
{

namespace srv
{

namespace builder
{

class Init_MissionControl_Request_state
{
public:
  Init_MissionControl_Request_state()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::pkg_srv::srv::MissionControl_Request state(::pkg_srv::srv::MissionControl_Request::_state_type arg)
  {
    msg_.state = std::move(arg);
    return std::move(msg_);
  }

private:
  ::pkg_srv::srv::MissionControl_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::pkg_srv::srv::MissionControl_Request>()
{
  return pkg_srv::srv::builder::Init_MissionControl_Request_state();
}

}  // namespace pkg_srv


namespace pkg_srv
{

namespace srv
{

namespace builder
{

class Init_MissionControl_Response_mission_state
{
public:
  Init_MissionControl_Response_mission_state()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::pkg_srv::srv::MissionControl_Response mission_state(::pkg_srv::srv::MissionControl_Response::_mission_state_type arg)
  {
    msg_.mission_state = std::move(arg);
    return std::move(msg_);
  }

private:
  ::pkg_srv::srv::MissionControl_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::pkg_srv::srv::MissionControl_Response>()
{
  return pkg_srv::srv::builder::Init_MissionControl_Response_mission_state();
}

}  // namespace pkg_srv

#endif  // PKG_SRV__SRV__DETAIL__MISSION_CONTROL__BUILDER_HPP_
