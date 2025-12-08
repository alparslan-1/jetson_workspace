// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from pars_msgs:msg/Data.idl
// generated code does not contain a copyright notice

#ifndef PARS_MSGS__MSG__DETAIL__DATA__STRUCT_HPP_
#define PARS_MSGS__MSG__DETAIL__DATA__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__pars_msgs__msg__Data __attribute__((deprecated))
#else
# define DEPRECATED__pars_msgs__msg__Data __declspec(deprecated)
#endif

namespace pars_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Data_
{
  using Type = Data_<ContainerAllocator>;

  explicit Data_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->takim_numarasi = 0l;
      this->iha_enlem = 0.0;
      this->iha_boylam = 0.0;
      this->iha_irtifa = 0.0;
      this->iha_yonelme = 0.0;
      this->iha_hizi = 0.0;
    }
  }

  explicit Data_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->takim_numarasi = 0l;
      this->iha_enlem = 0.0;
      this->iha_boylam = 0.0;
      this->iha_irtifa = 0.0;
      this->iha_yonelme = 0.0;
      this->iha_hizi = 0.0;
    }
  }

  // field types and members
  using _takim_numarasi_type =
    int32_t;
  _takim_numarasi_type takim_numarasi;
  using _iha_enlem_type =
    double;
  _iha_enlem_type iha_enlem;
  using _iha_boylam_type =
    double;
  _iha_boylam_type iha_boylam;
  using _iha_irtifa_type =
    double;
  _iha_irtifa_type iha_irtifa;
  using _iha_yonelme_type =
    double;
  _iha_yonelme_type iha_yonelme;
  using _iha_hizi_type =
    double;
  _iha_hizi_type iha_hizi;

  // setters for named parameter idiom
  Type & set__takim_numarasi(
    const int32_t & _arg)
  {
    this->takim_numarasi = _arg;
    return *this;
  }
  Type & set__iha_enlem(
    const double & _arg)
  {
    this->iha_enlem = _arg;
    return *this;
  }
  Type & set__iha_boylam(
    const double & _arg)
  {
    this->iha_boylam = _arg;
    return *this;
  }
  Type & set__iha_irtifa(
    const double & _arg)
  {
    this->iha_irtifa = _arg;
    return *this;
  }
  Type & set__iha_yonelme(
    const double & _arg)
  {
    this->iha_yonelme = _arg;
    return *this;
  }
  Type & set__iha_hizi(
    const double & _arg)
  {
    this->iha_hizi = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    pars_msgs::msg::Data_<ContainerAllocator> *;
  using ConstRawPtr =
    const pars_msgs::msg::Data_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<pars_msgs::msg::Data_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<pars_msgs::msg::Data_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      pars_msgs::msg::Data_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<pars_msgs::msg::Data_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      pars_msgs::msg::Data_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<pars_msgs::msg::Data_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<pars_msgs::msg::Data_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<pars_msgs::msg::Data_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__pars_msgs__msg__Data
    std::shared_ptr<pars_msgs::msg::Data_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__pars_msgs__msg__Data
    std::shared_ptr<pars_msgs::msg::Data_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Data_ & other) const
  {
    if (this->takim_numarasi != other.takim_numarasi) {
      return false;
    }
    if (this->iha_enlem != other.iha_enlem) {
      return false;
    }
    if (this->iha_boylam != other.iha_boylam) {
      return false;
    }
    if (this->iha_irtifa != other.iha_irtifa) {
      return false;
    }
    if (this->iha_yonelme != other.iha_yonelme) {
      return false;
    }
    if (this->iha_hizi != other.iha_hizi) {
      return false;
    }
    return true;
  }
  bool operator!=(const Data_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Data_

// alias to use template instance with default allocator
using Data =
  pars_msgs::msg::Data_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace pars_msgs

#endif  // PARS_MSGS__MSG__DETAIL__DATA__STRUCT_HPP_
