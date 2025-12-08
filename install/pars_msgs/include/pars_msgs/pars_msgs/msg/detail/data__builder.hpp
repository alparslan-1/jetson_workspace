// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from pars_msgs:msg/Data.idl
// generated code does not contain a copyright notice

#ifndef PARS_MSGS__MSG__DETAIL__DATA__BUILDER_HPP_
#define PARS_MSGS__MSG__DETAIL__DATA__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "pars_msgs/msg/detail/data__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace pars_msgs
{

namespace msg
{

namespace builder
{

class Init_Data_iha_hizi
{
public:
  explicit Init_Data_iha_hizi(::pars_msgs::msg::Data & msg)
  : msg_(msg)
  {}
  ::pars_msgs::msg::Data iha_hizi(::pars_msgs::msg::Data::_iha_hizi_type arg)
  {
    msg_.iha_hizi = std::move(arg);
    return std::move(msg_);
  }

private:
  ::pars_msgs::msg::Data msg_;
};

class Init_Data_iha_yonelme
{
public:
  explicit Init_Data_iha_yonelme(::pars_msgs::msg::Data & msg)
  : msg_(msg)
  {}
  Init_Data_iha_hizi iha_yonelme(::pars_msgs::msg::Data::_iha_yonelme_type arg)
  {
    msg_.iha_yonelme = std::move(arg);
    return Init_Data_iha_hizi(msg_);
  }

private:
  ::pars_msgs::msg::Data msg_;
};

class Init_Data_iha_irtifa
{
public:
  explicit Init_Data_iha_irtifa(::pars_msgs::msg::Data & msg)
  : msg_(msg)
  {}
  Init_Data_iha_yonelme iha_irtifa(::pars_msgs::msg::Data::_iha_irtifa_type arg)
  {
    msg_.iha_irtifa = std::move(arg);
    return Init_Data_iha_yonelme(msg_);
  }

private:
  ::pars_msgs::msg::Data msg_;
};

class Init_Data_iha_boylam
{
public:
  explicit Init_Data_iha_boylam(::pars_msgs::msg::Data & msg)
  : msg_(msg)
  {}
  Init_Data_iha_irtifa iha_boylam(::pars_msgs::msg::Data::_iha_boylam_type arg)
  {
    msg_.iha_boylam = std::move(arg);
    return Init_Data_iha_irtifa(msg_);
  }

private:
  ::pars_msgs::msg::Data msg_;
};

class Init_Data_iha_enlem
{
public:
  explicit Init_Data_iha_enlem(::pars_msgs::msg::Data & msg)
  : msg_(msg)
  {}
  Init_Data_iha_boylam iha_enlem(::pars_msgs::msg::Data::_iha_enlem_type arg)
  {
    msg_.iha_enlem = std::move(arg);
    return Init_Data_iha_boylam(msg_);
  }

private:
  ::pars_msgs::msg::Data msg_;
};

class Init_Data_takim_numarasi
{
public:
  Init_Data_takim_numarasi()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Data_iha_enlem takim_numarasi(::pars_msgs::msg::Data::_takim_numarasi_type arg)
  {
    msg_.takim_numarasi = std::move(arg);
    return Init_Data_iha_enlem(msg_);
  }

private:
  ::pars_msgs::msg::Data msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::pars_msgs::msg::Data>()
{
  return pars_msgs::msg::builder::Init_Data_takim_numarasi();
}

}  // namespace pars_msgs

#endif  // PARS_MSGS__MSG__DETAIL__DATA__BUILDER_HPP_
