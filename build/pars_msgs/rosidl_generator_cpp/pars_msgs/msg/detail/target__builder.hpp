// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from pars_msgs:msg/Target.idl
// generated code does not contain a copyright notice

#ifndef PARS_MSGS__MSG__DETAIL__TARGET__BUILDER_HPP_
#define PARS_MSGS__MSG__DETAIL__TARGET__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "pars_msgs/msg/detail/target__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace pars_msgs
{

namespace msg
{

namespace builder
{

class Init_Target_hedef_boyut
{
public:
  explicit Init_Target_hedef_boyut(::pars_msgs::msg::Target & msg)
  : msg_(msg)
  {}
  ::pars_msgs::msg::Target hedef_boyut(::pars_msgs::msg::Target::_hedef_boyut_type arg)
  {
    msg_.hedef_boyut = std::move(arg);
    return std::move(msg_);
  }

private:
  ::pars_msgs::msg::Target msg_;
};

class Init_Target_image_height
{
public:
  explicit Init_Target_image_height(::pars_msgs::msg::Target & msg)
  : msg_(msg)
  {}
  Init_Target_hedef_boyut image_height(::pars_msgs::msg::Target::_image_height_type arg)
  {
    msg_.image_height = std::move(arg);
    return Init_Target_hedef_boyut(msg_);
  }

private:
  ::pars_msgs::msg::Target msg_;
};

class Init_Target_image_width
{
public:
  explicit Init_Target_image_width(::pars_msgs::msg::Target & msg)
  : msg_(msg)
  {}
  Init_Target_image_height image_width(::pars_msgs::msg::Target::_image_width_type arg)
  {
    msg_.image_width = std::move(arg);
    return Init_Target_image_height(msg_);
  }

private:
  ::pars_msgs::msg::Target msg_;
};

class Init_Target_y_center
{
public:
  explicit Init_Target_y_center(::pars_msgs::msg::Target & msg)
  : msg_(msg)
  {}
  Init_Target_image_width y_center(::pars_msgs::msg::Target::_y_center_type arg)
  {
    msg_.y_center = std::move(arg);
    return Init_Target_image_width(msg_);
  }

private:
  ::pars_msgs::msg::Target msg_;
};

class Init_Target_x_center
{
public:
  explicit Init_Target_x_center(::pars_msgs::msg::Target & msg)
  : msg_(msg)
  {}
  Init_Target_y_center x_center(::pars_msgs::msg::Target::_x_center_type arg)
  {
    msg_.x_center = std::move(arg);
    return Init_Target_y_center(msg_);
  }

private:
  ::pars_msgs::msg::Target msg_;
};

class Init_Target_target_detected
{
public:
  Init_Target_target_detected()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Target_x_center target_detected(::pars_msgs::msg::Target::_target_detected_type arg)
  {
    msg_.target_detected = std::move(arg);
    return Init_Target_x_center(msg_);
  }

private:
  ::pars_msgs::msg::Target msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::pars_msgs::msg::Target>()
{
  return pars_msgs::msg::builder::Init_Target_target_detected();
}

}  // namespace pars_msgs

#endif  // PARS_MSGS__MSG__DETAIL__TARGET__BUILDER_HPP_
