// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from igus_rebel_msgs:msg/DigitalOutput.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "igus_rebel_msgs/msg/digital_output.hpp"


#ifndef IGUS_REBEL_MSGS__MSG__DETAIL__DIGITAL_OUTPUT__TRAITS_HPP_
#define IGUS_REBEL_MSGS__MSG__DETAIL__DIGITAL_OUTPUT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "igus_rebel_msgs/msg/detail/digital_output__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace igus_rebel_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const DigitalOutput & msg,
  std::ostream & out)
{
  out << "{";
  // member: output
  {
    out << "output: ";
    rosidl_generator_traits::value_to_yaml(msg.output, out);
    out << ", ";
  }

  // member: is_on
  {
    out << "is_on: ";
    rosidl_generator_traits::value_to_yaml(msg.is_on, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const DigitalOutput & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: output
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "output: ";
    rosidl_generator_traits::value_to_yaml(msg.output, out);
    out << "\n";
  }

  // member: is_on
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "is_on: ";
    rosidl_generator_traits::value_to_yaml(msg.is_on, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const DigitalOutput & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace igus_rebel_msgs

namespace rosidl_generator_traits
{

[[deprecated("use igus_rebel_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const igus_rebel_msgs::msg::DigitalOutput & msg,
  std::ostream & out, size_t indentation = 0)
{
  igus_rebel_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use igus_rebel_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const igus_rebel_msgs::msg::DigitalOutput & msg)
{
  return igus_rebel_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<igus_rebel_msgs::msg::DigitalOutput>()
{
  return "igus_rebel_msgs::msg::DigitalOutput";
}

template<>
inline const char * name<igus_rebel_msgs::msg::DigitalOutput>()
{
  return "igus_rebel_msgs/msg/DigitalOutput";
}

template<>
struct has_fixed_size<igus_rebel_msgs::msg::DigitalOutput>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<igus_rebel_msgs::msg::DigitalOutput>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<igus_rebel_msgs::msg::DigitalOutput>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // IGUS_REBEL_MSGS__MSG__DETAIL__DIGITAL_OUTPUT__TRAITS_HPP_
