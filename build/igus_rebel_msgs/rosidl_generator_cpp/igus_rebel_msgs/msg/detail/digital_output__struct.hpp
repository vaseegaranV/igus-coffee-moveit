// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from igus_rebel_msgs:msg/DigitalOutput.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "igus_rebel_msgs/msg/digital_output.hpp"


#ifndef IGUS_REBEL_MSGS__MSG__DETAIL__DIGITAL_OUTPUT__STRUCT_HPP_
#define IGUS_REBEL_MSGS__MSG__DETAIL__DIGITAL_OUTPUT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__igus_rebel_msgs__msg__DigitalOutput __attribute__((deprecated))
#else
# define DEPRECATED__igus_rebel_msgs__msg__DigitalOutput __declspec(deprecated)
#endif

namespace igus_rebel_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct DigitalOutput_
{
  using Type = DigitalOutput_<ContainerAllocator>;

  explicit DigitalOutput_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->output = 0;
      this->is_on = false;
    }
  }

  explicit DigitalOutput_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->output = 0;
      this->is_on = false;
    }
  }

  // field types and members
  using _output_type =
    int8_t;
  _output_type output;
  using _is_on_type =
    bool;
  _is_on_type is_on;

  // setters for named parameter idiom
  Type & set__output(
    const int8_t & _arg)
  {
    this->output = _arg;
    return *this;
  }
  Type & set__is_on(
    const bool & _arg)
  {
    this->is_on = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    igus_rebel_msgs::msg::DigitalOutput_<ContainerAllocator> *;
  using ConstRawPtr =
    const igus_rebel_msgs::msg::DigitalOutput_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<igus_rebel_msgs::msg::DigitalOutput_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<igus_rebel_msgs::msg::DigitalOutput_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      igus_rebel_msgs::msg::DigitalOutput_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<igus_rebel_msgs::msg::DigitalOutput_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      igus_rebel_msgs::msg::DigitalOutput_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<igus_rebel_msgs::msg::DigitalOutput_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<igus_rebel_msgs::msg::DigitalOutput_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<igus_rebel_msgs::msg::DigitalOutput_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__igus_rebel_msgs__msg__DigitalOutput
    std::shared_ptr<igus_rebel_msgs::msg::DigitalOutput_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__igus_rebel_msgs__msg__DigitalOutput
    std::shared_ptr<igus_rebel_msgs::msg::DigitalOutput_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const DigitalOutput_ & other) const
  {
    if (this->output != other.output) {
      return false;
    }
    if (this->is_on != other.is_on) {
      return false;
    }
    return true;
  }
  bool operator!=(const DigitalOutput_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct DigitalOutput_

// alias to use template instance with default allocator
using DigitalOutput =
  igus_rebel_msgs::msg::DigitalOutput_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace igus_rebel_msgs

#endif  // IGUS_REBEL_MSGS__MSG__DETAIL__DIGITAL_OUTPUT__STRUCT_HPP_
