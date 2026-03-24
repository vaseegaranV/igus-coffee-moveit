// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from igus_rebel_msgs:srv/SetDigitalOutput.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "igus_rebel_msgs/srv/set_digital_output.hpp"


#ifndef IGUS_REBEL_MSGS__SRV__DETAIL__SET_DIGITAL_OUTPUT__BUILDER_HPP_
#define IGUS_REBEL_MSGS__SRV__DETAIL__SET_DIGITAL_OUTPUT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "igus_rebel_msgs/srv/detail/set_digital_output__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace igus_rebel_msgs
{

namespace srv
{

namespace builder
{

class Init_SetDigitalOutput_Request_output
{
public:
  Init_SetDigitalOutput_Request_output()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::igus_rebel_msgs::srv::SetDigitalOutput_Request output(::igus_rebel_msgs::srv::SetDigitalOutput_Request::_output_type arg)
  {
    msg_.output = std::move(arg);
    return std::move(msg_);
  }

private:
  ::igus_rebel_msgs::srv::SetDigitalOutput_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::igus_rebel_msgs::srv::SetDigitalOutput_Request>()
{
  return igus_rebel_msgs::srv::builder::Init_SetDigitalOutput_Request_output();
}

}  // namespace igus_rebel_msgs


namespace igus_rebel_msgs
{

namespace srv
{

namespace builder
{

class Init_SetDigitalOutput_Response_message
{
public:
  explicit Init_SetDigitalOutput_Response_message(::igus_rebel_msgs::srv::SetDigitalOutput_Response & msg)
  : msg_(msg)
  {}
  ::igus_rebel_msgs::srv::SetDigitalOutput_Response message(::igus_rebel_msgs::srv::SetDigitalOutput_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::igus_rebel_msgs::srv::SetDigitalOutput_Response msg_;
};

class Init_SetDigitalOutput_Response_success
{
public:
  Init_SetDigitalOutput_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetDigitalOutput_Response_message success(::igus_rebel_msgs::srv::SetDigitalOutput_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_SetDigitalOutput_Response_message(msg_);
  }

private:
  ::igus_rebel_msgs::srv::SetDigitalOutput_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::igus_rebel_msgs::srv::SetDigitalOutput_Response>()
{
  return igus_rebel_msgs::srv::builder::Init_SetDigitalOutput_Response_success();
}

}  // namespace igus_rebel_msgs


namespace igus_rebel_msgs
{

namespace srv
{

namespace builder
{

class Init_SetDigitalOutput_Event_response
{
public:
  explicit Init_SetDigitalOutput_Event_response(::igus_rebel_msgs::srv::SetDigitalOutput_Event & msg)
  : msg_(msg)
  {}
  ::igus_rebel_msgs::srv::SetDigitalOutput_Event response(::igus_rebel_msgs::srv::SetDigitalOutput_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::igus_rebel_msgs::srv::SetDigitalOutput_Event msg_;
};

class Init_SetDigitalOutput_Event_request
{
public:
  explicit Init_SetDigitalOutput_Event_request(::igus_rebel_msgs::srv::SetDigitalOutput_Event & msg)
  : msg_(msg)
  {}
  Init_SetDigitalOutput_Event_response request(::igus_rebel_msgs::srv::SetDigitalOutput_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_SetDigitalOutput_Event_response(msg_);
  }

private:
  ::igus_rebel_msgs::srv::SetDigitalOutput_Event msg_;
};

class Init_SetDigitalOutput_Event_info
{
public:
  Init_SetDigitalOutput_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetDigitalOutput_Event_request info(::igus_rebel_msgs::srv::SetDigitalOutput_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_SetDigitalOutput_Event_request(msg_);
  }

private:
  ::igus_rebel_msgs::srv::SetDigitalOutput_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::igus_rebel_msgs::srv::SetDigitalOutput_Event>()
{
  return igus_rebel_msgs::srv::builder::Init_SetDigitalOutput_Event_info();
}

}  // namespace igus_rebel_msgs

#endif  // IGUS_REBEL_MSGS__SRV__DETAIL__SET_DIGITAL_OUTPUT__BUILDER_HPP_
