// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from igus_rebel_msgs:msg/DigitalOutput.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "igus_rebel_msgs/msg/digital_output.hpp"


#ifndef IGUS_REBEL_MSGS__MSG__DETAIL__DIGITAL_OUTPUT__BUILDER_HPP_
#define IGUS_REBEL_MSGS__MSG__DETAIL__DIGITAL_OUTPUT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "igus_rebel_msgs/msg/detail/digital_output__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace igus_rebel_msgs
{

namespace msg
{

namespace builder
{

class Init_DigitalOutput_is_on
{
public:
  explicit Init_DigitalOutput_is_on(::igus_rebel_msgs::msg::DigitalOutput & msg)
  : msg_(msg)
  {}
  ::igus_rebel_msgs::msg::DigitalOutput is_on(::igus_rebel_msgs::msg::DigitalOutput::_is_on_type arg)
  {
    msg_.is_on = std::move(arg);
    return std::move(msg_);
  }

private:
  ::igus_rebel_msgs::msg::DigitalOutput msg_;
};

class Init_DigitalOutput_output
{
public:
  Init_DigitalOutput_output()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DigitalOutput_is_on output(::igus_rebel_msgs::msg::DigitalOutput::_output_type arg)
  {
    msg_.output = std::move(arg);
    return Init_DigitalOutput_is_on(msg_);
  }

private:
  ::igus_rebel_msgs::msg::DigitalOutput msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::igus_rebel_msgs::msg::DigitalOutput>()
{
  return igus_rebel_msgs::msg::builder::Init_DigitalOutput_output();
}

}  // namespace igus_rebel_msgs

#endif  // IGUS_REBEL_MSGS__MSG__DETAIL__DIGITAL_OUTPUT__BUILDER_HPP_
