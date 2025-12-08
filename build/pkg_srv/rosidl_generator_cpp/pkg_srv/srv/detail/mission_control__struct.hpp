// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from pkg_srv:srv/MissionControl.idl
// generated code does not contain a copyright notice

#ifndef PKG_SRV__SRV__DETAIL__MISSION_CONTROL__STRUCT_HPP_
#define PKG_SRV__SRV__DETAIL__MISSION_CONTROL__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__pkg_srv__srv__MissionControl_Request __attribute__((deprecated))
#else
# define DEPRECATED__pkg_srv__srv__MissionControl_Request __declspec(deprecated)
#endif

namespace pkg_srv
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct MissionControl_Request_
{
  using Type = MissionControl_Request_<ContainerAllocator>;

  explicit MissionControl_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->state = "";
    }
  }

  explicit MissionControl_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : state(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->state = "";
    }
  }

  // field types and members
  using _state_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _state_type state;

  // setters for named parameter idiom
  Type & set__state(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->state = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    pkg_srv::srv::MissionControl_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const pkg_srv::srv::MissionControl_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<pkg_srv::srv::MissionControl_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<pkg_srv::srv::MissionControl_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      pkg_srv::srv::MissionControl_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<pkg_srv::srv::MissionControl_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      pkg_srv::srv::MissionControl_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<pkg_srv::srv::MissionControl_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<pkg_srv::srv::MissionControl_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<pkg_srv::srv::MissionControl_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__pkg_srv__srv__MissionControl_Request
    std::shared_ptr<pkg_srv::srv::MissionControl_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__pkg_srv__srv__MissionControl_Request
    std::shared_ptr<pkg_srv::srv::MissionControl_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MissionControl_Request_ & other) const
  {
    if (this->state != other.state) {
      return false;
    }
    return true;
  }
  bool operator!=(const MissionControl_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MissionControl_Request_

// alias to use template instance with default allocator
using MissionControl_Request =
  pkg_srv::srv::MissionControl_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace pkg_srv


#ifndef _WIN32
# define DEPRECATED__pkg_srv__srv__MissionControl_Response __attribute__((deprecated))
#else
# define DEPRECATED__pkg_srv__srv__MissionControl_Response __declspec(deprecated)
#endif

namespace pkg_srv
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct MissionControl_Response_
{
  using Type = MissionControl_Response_<ContainerAllocator>;

  explicit MissionControl_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->mission_state = "";
    }
  }

  explicit MissionControl_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : mission_state(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->mission_state = "";
    }
  }

  // field types and members
  using _mission_state_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _mission_state_type mission_state;

  // setters for named parameter idiom
  Type & set__mission_state(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->mission_state = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    pkg_srv::srv::MissionControl_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const pkg_srv::srv::MissionControl_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<pkg_srv::srv::MissionControl_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<pkg_srv::srv::MissionControl_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      pkg_srv::srv::MissionControl_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<pkg_srv::srv::MissionControl_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      pkg_srv::srv::MissionControl_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<pkg_srv::srv::MissionControl_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<pkg_srv::srv::MissionControl_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<pkg_srv::srv::MissionControl_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__pkg_srv__srv__MissionControl_Response
    std::shared_ptr<pkg_srv::srv::MissionControl_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__pkg_srv__srv__MissionControl_Response
    std::shared_ptr<pkg_srv::srv::MissionControl_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MissionControl_Response_ & other) const
  {
    if (this->mission_state != other.mission_state) {
      return false;
    }
    return true;
  }
  bool operator!=(const MissionControl_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MissionControl_Response_

// alias to use template instance with default allocator
using MissionControl_Response =
  pkg_srv::srv::MissionControl_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace pkg_srv

namespace pkg_srv
{

namespace srv
{

struct MissionControl
{
  using Request = pkg_srv::srv::MissionControl_Request;
  using Response = pkg_srv::srv::MissionControl_Response;
};

}  // namespace srv

}  // namespace pkg_srv

#endif  // PKG_SRV__SRV__DETAIL__MISSION_CONTROL__STRUCT_HPP_
