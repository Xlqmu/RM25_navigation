// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from nav2_msgs:srv/ReloadDockDatabase.idl
// generated code does not contain a copyright notice

#ifndef NAV2_MSGS__SRV__DETAIL__RELOAD_DOCK_DATABASE__STRUCT_HPP_
#define NAV2_MSGS__SRV__DETAIL__RELOAD_DOCK_DATABASE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__nav2_msgs__srv__ReloadDockDatabase_Request __attribute__((deprecated))
#else
# define DEPRECATED__nav2_msgs__srv__ReloadDockDatabase_Request __declspec(deprecated)
#endif

namespace nav2_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct ReloadDockDatabase_Request_
{
  using Type = ReloadDockDatabase_Request_<ContainerAllocator>;

  explicit ReloadDockDatabase_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->filepath = "";
    }
  }

  explicit ReloadDockDatabase_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : filepath(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->filepath = "";
    }
  }

  // field types and members
  using _filepath_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _filepath_type filepath;

  // setters for named parameter idiom
  Type & set__filepath(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->filepath = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    nav2_msgs::srv::ReloadDockDatabase_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const nav2_msgs::srv::ReloadDockDatabase_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<nav2_msgs::srv::ReloadDockDatabase_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<nav2_msgs::srv::ReloadDockDatabase_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      nav2_msgs::srv::ReloadDockDatabase_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<nav2_msgs::srv::ReloadDockDatabase_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      nav2_msgs::srv::ReloadDockDatabase_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<nav2_msgs::srv::ReloadDockDatabase_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<nav2_msgs::srv::ReloadDockDatabase_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<nav2_msgs::srv::ReloadDockDatabase_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__nav2_msgs__srv__ReloadDockDatabase_Request
    std::shared_ptr<nav2_msgs::srv::ReloadDockDatabase_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__nav2_msgs__srv__ReloadDockDatabase_Request
    std::shared_ptr<nav2_msgs::srv::ReloadDockDatabase_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ReloadDockDatabase_Request_ & other) const
  {
    if (this->filepath != other.filepath) {
      return false;
    }
    return true;
  }
  bool operator!=(const ReloadDockDatabase_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ReloadDockDatabase_Request_

// alias to use template instance with default allocator
using ReloadDockDatabase_Request =
  nav2_msgs::srv::ReloadDockDatabase_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace nav2_msgs


#ifndef _WIN32
# define DEPRECATED__nav2_msgs__srv__ReloadDockDatabase_Response __attribute__((deprecated))
#else
# define DEPRECATED__nav2_msgs__srv__ReloadDockDatabase_Response __declspec(deprecated)
#endif

namespace nav2_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct ReloadDockDatabase_Response_
{
  using Type = ReloadDockDatabase_Response_<ContainerAllocator>;

  explicit ReloadDockDatabase_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
    }
  }

  explicit ReloadDockDatabase_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;

  // setters for named parameter idiom
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    nav2_msgs::srv::ReloadDockDatabase_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const nav2_msgs::srv::ReloadDockDatabase_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<nav2_msgs::srv::ReloadDockDatabase_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<nav2_msgs::srv::ReloadDockDatabase_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      nav2_msgs::srv::ReloadDockDatabase_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<nav2_msgs::srv::ReloadDockDatabase_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      nav2_msgs::srv::ReloadDockDatabase_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<nav2_msgs::srv::ReloadDockDatabase_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<nav2_msgs::srv::ReloadDockDatabase_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<nav2_msgs::srv::ReloadDockDatabase_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__nav2_msgs__srv__ReloadDockDatabase_Response
    std::shared_ptr<nav2_msgs::srv::ReloadDockDatabase_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__nav2_msgs__srv__ReloadDockDatabase_Response
    std::shared_ptr<nav2_msgs::srv::ReloadDockDatabase_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ReloadDockDatabase_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    return true;
  }
  bool operator!=(const ReloadDockDatabase_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ReloadDockDatabase_Response_

// alias to use template instance with default allocator
using ReloadDockDatabase_Response =
  nav2_msgs::srv::ReloadDockDatabase_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace nav2_msgs

namespace nav2_msgs
{

namespace srv
{

struct ReloadDockDatabase
{
  using Request = nav2_msgs::srv::ReloadDockDatabase_Request;
  using Response = nav2_msgs::srv::ReloadDockDatabase_Response;
};

}  // namespace srv

}  // namespace nav2_msgs

#endif  // NAV2_MSGS__SRV__DETAIL__RELOAD_DOCK_DATABASE__STRUCT_HPP_
