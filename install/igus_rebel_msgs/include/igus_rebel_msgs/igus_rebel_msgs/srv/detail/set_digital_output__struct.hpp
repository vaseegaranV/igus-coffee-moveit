// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from igus_rebel_msgs:srv/SetDigitalOutput.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "igus_rebel_msgs/srv/set_digital_output.hpp"


#ifndef IGUS_REBEL_MSGS__SRV__DETAIL__SET_DIGITAL_OUTPUT__STRUCT_HPP_
#define IGUS_REBEL_MSGS__SRV__DETAIL__SET_DIGITAL_OUTPUT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'output'
#include "igus_rebel_msgs/msg/detail/digital_output__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__igus_rebel_msgs__srv__SetDigitalOutput_Request __attribute__((deprecated))
#else
# define DEPRECATED__igus_rebel_msgs__srv__SetDigitalOutput_Request __declspec(deprecated)
#endif

namespace igus_rebel_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetDigitalOutput_Request_
{
  using Type = SetDigitalOutput_Request_<ContainerAllocator>;

  explicit SetDigitalOutput_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : output(_init)
  {
    (void)_init;
  }

  explicit SetDigitalOutput_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : output(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _output_type =
    igus_rebel_msgs::msg::DigitalOutput_<ContainerAllocator>;
  _output_type output;

  // setters for named parameter idiom
  Type & set__output(
    const igus_rebel_msgs::msg::DigitalOutput_<ContainerAllocator> & _arg)
  {
    this->output = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    igus_rebel_msgs::srv::SetDigitalOutput_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const igus_rebel_msgs::srv::SetDigitalOutput_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<igus_rebel_msgs::srv::SetDigitalOutput_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<igus_rebel_msgs::srv::SetDigitalOutput_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      igus_rebel_msgs::srv::SetDigitalOutput_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<igus_rebel_msgs::srv::SetDigitalOutput_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      igus_rebel_msgs::srv::SetDigitalOutput_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<igus_rebel_msgs::srv::SetDigitalOutput_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<igus_rebel_msgs::srv::SetDigitalOutput_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<igus_rebel_msgs::srv::SetDigitalOutput_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__igus_rebel_msgs__srv__SetDigitalOutput_Request
    std::shared_ptr<igus_rebel_msgs::srv::SetDigitalOutput_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__igus_rebel_msgs__srv__SetDigitalOutput_Request
    std::shared_ptr<igus_rebel_msgs::srv::SetDigitalOutput_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetDigitalOutput_Request_ & other) const
  {
    if (this->output != other.output) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetDigitalOutput_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetDigitalOutput_Request_

// alias to use template instance with default allocator
using SetDigitalOutput_Request =
  igus_rebel_msgs::srv::SetDigitalOutput_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace igus_rebel_msgs


#ifndef _WIN32
# define DEPRECATED__igus_rebel_msgs__srv__SetDigitalOutput_Response __attribute__((deprecated))
#else
# define DEPRECATED__igus_rebel_msgs__srv__SetDigitalOutput_Response __declspec(deprecated)
#endif

namespace igus_rebel_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetDigitalOutput_Response_
{
  using Type = SetDigitalOutput_Response_<ContainerAllocator>;

  explicit SetDigitalOutput_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
    }
  }

  explicit SetDigitalOutput_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;

  // setters for named parameter idiom
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    igus_rebel_msgs::srv::SetDigitalOutput_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const igus_rebel_msgs::srv::SetDigitalOutput_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<igus_rebel_msgs::srv::SetDigitalOutput_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<igus_rebel_msgs::srv::SetDigitalOutput_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      igus_rebel_msgs::srv::SetDigitalOutput_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<igus_rebel_msgs::srv::SetDigitalOutput_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      igus_rebel_msgs::srv::SetDigitalOutput_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<igus_rebel_msgs::srv::SetDigitalOutput_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<igus_rebel_msgs::srv::SetDigitalOutput_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<igus_rebel_msgs::srv::SetDigitalOutput_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__igus_rebel_msgs__srv__SetDigitalOutput_Response
    std::shared_ptr<igus_rebel_msgs::srv::SetDigitalOutput_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__igus_rebel_msgs__srv__SetDigitalOutput_Response
    std::shared_ptr<igus_rebel_msgs::srv::SetDigitalOutput_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetDigitalOutput_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetDigitalOutput_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetDigitalOutput_Response_

// alias to use template instance with default allocator
using SetDigitalOutput_Response =
  igus_rebel_msgs::srv::SetDigitalOutput_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace igus_rebel_msgs


// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__igus_rebel_msgs__srv__SetDigitalOutput_Event __attribute__((deprecated))
#else
# define DEPRECATED__igus_rebel_msgs__srv__SetDigitalOutput_Event __declspec(deprecated)
#endif

namespace igus_rebel_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetDigitalOutput_Event_
{
  using Type = SetDigitalOutput_Event_<ContainerAllocator>;

  explicit SetDigitalOutput_Event_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_init)
  {
    (void)_init;
  }

  explicit SetDigitalOutput_Event_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _info_type =
    service_msgs::msg::ServiceEventInfo_<ContainerAllocator>;
  _info_type info;
  using _request_type =
    rosidl_runtime_cpp::BoundedVector<igus_rebel_msgs::srv::SetDigitalOutput_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<igus_rebel_msgs::srv::SetDigitalOutput_Request_<ContainerAllocator>>>;
  _request_type request;
  using _response_type =
    rosidl_runtime_cpp::BoundedVector<igus_rebel_msgs::srv::SetDigitalOutput_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<igus_rebel_msgs::srv::SetDigitalOutput_Response_<ContainerAllocator>>>;
  _response_type response;

  // setters for named parameter idiom
  Type & set__info(
    const service_msgs::msg::ServiceEventInfo_<ContainerAllocator> & _arg)
  {
    this->info = _arg;
    return *this;
  }
  Type & set__request(
    const rosidl_runtime_cpp::BoundedVector<igus_rebel_msgs::srv::SetDigitalOutput_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<igus_rebel_msgs::srv::SetDigitalOutput_Request_<ContainerAllocator>>> & _arg)
  {
    this->request = _arg;
    return *this;
  }
  Type & set__response(
    const rosidl_runtime_cpp::BoundedVector<igus_rebel_msgs::srv::SetDigitalOutput_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<igus_rebel_msgs::srv::SetDigitalOutput_Response_<ContainerAllocator>>> & _arg)
  {
    this->response = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    igus_rebel_msgs::srv::SetDigitalOutput_Event_<ContainerAllocator> *;
  using ConstRawPtr =
    const igus_rebel_msgs::srv::SetDigitalOutput_Event_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<igus_rebel_msgs::srv::SetDigitalOutput_Event_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<igus_rebel_msgs::srv::SetDigitalOutput_Event_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      igus_rebel_msgs::srv::SetDigitalOutput_Event_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<igus_rebel_msgs::srv::SetDigitalOutput_Event_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      igus_rebel_msgs::srv::SetDigitalOutput_Event_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<igus_rebel_msgs::srv::SetDigitalOutput_Event_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<igus_rebel_msgs::srv::SetDigitalOutput_Event_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<igus_rebel_msgs::srv::SetDigitalOutput_Event_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__igus_rebel_msgs__srv__SetDigitalOutput_Event
    std::shared_ptr<igus_rebel_msgs::srv::SetDigitalOutput_Event_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__igus_rebel_msgs__srv__SetDigitalOutput_Event
    std::shared_ptr<igus_rebel_msgs::srv::SetDigitalOutput_Event_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetDigitalOutput_Event_ & other) const
  {
    if (this->info != other.info) {
      return false;
    }
    if (this->request != other.request) {
      return false;
    }
    if (this->response != other.response) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetDigitalOutput_Event_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetDigitalOutput_Event_

// alias to use template instance with default allocator
using SetDigitalOutput_Event =
  igus_rebel_msgs::srv::SetDigitalOutput_Event_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace igus_rebel_msgs

namespace igus_rebel_msgs
{

namespace srv
{

struct SetDigitalOutput
{
  using Request = igus_rebel_msgs::srv::SetDigitalOutput_Request;
  using Response = igus_rebel_msgs::srv::SetDigitalOutput_Response;
  using Event = igus_rebel_msgs::srv::SetDigitalOutput_Event;
};

}  // namespace srv

}  // namespace igus_rebel_msgs

#endif  // IGUS_REBEL_MSGS__SRV__DETAIL__SET_DIGITAL_OUTPUT__STRUCT_HPP_
