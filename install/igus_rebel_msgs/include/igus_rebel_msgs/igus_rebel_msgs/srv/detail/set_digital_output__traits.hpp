// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from igus_rebel_msgs:srv/SetDigitalOutput.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "igus_rebel_msgs/srv/set_digital_output.hpp"


#ifndef IGUS_REBEL_MSGS__SRV__DETAIL__SET_DIGITAL_OUTPUT__TRAITS_HPP_
#define IGUS_REBEL_MSGS__SRV__DETAIL__SET_DIGITAL_OUTPUT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "igus_rebel_msgs/srv/detail/set_digital_output__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'output'
#include "igus_rebel_msgs/msg/detail/digital_output__traits.hpp"

namespace igus_rebel_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const SetDigitalOutput_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: output
  {
    out << "output: ";
    to_flow_style_yaml(msg.output, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SetDigitalOutput_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: output
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "output:\n";
    to_block_style_yaml(msg.output, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SetDigitalOutput_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace igus_rebel_msgs

namespace rosidl_generator_traits
{

[[deprecated("use igus_rebel_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const igus_rebel_msgs::srv::SetDigitalOutput_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  igus_rebel_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use igus_rebel_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const igus_rebel_msgs::srv::SetDigitalOutput_Request & msg)
{
  return igus_rebel_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<igus_rebel_msgs::srv::SetDigitalOutput_Request>()
{
  return "igus_rebel_msgs::srv::SetDigitalOutput_Request";
}

template<>
inline const char * name<igus_rebel_msgs::srv::SetDigitalOutput_Request>()
{
  return "igus_rebel_msgs/srv/SetDigitalOutput_Request";
}

template<>
struct has_fixed_size<igus_rebel_msgs::srv::SetDigitalOutput_Request>
  : std::integral_constant<bool, has_fixed_size<igus_rebel_msgs::msg::DigitalOutput>::value> {};

template<>
struct has_bounded_size<igus_rebel_msgs::srv::SetDigitalOutput_Request>
  : std::integral_constant<bool, has_bounded_size<igus_rebel_msgs::msg::DigitalOutput>::value> {};

template<>
struct is_message<igus_rebel_msgs::srv::SetDigitalOutput_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace igus_rebel_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const SetDigitalOutput_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << ", ";
  }

  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SetDigitalOutput_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << "\n";
  }

  // member: message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SetDigitalOutput_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace igus_rebel_msgs

namespace rosidl_generator_traits
{

[[deprecated("use igus_rebel_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const igus_rebel_msgs::srv::SetDigitalOutput_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  igus_rebel_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use igus_rebel_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const igus_rebel_msgs::srv::SetDigitalOutput_Response & msg)
{
  return igus_rebel_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<igus_rebel_msgs::srv::SetDigitalOutput_Response>()
{
  return "igus_rebel_msgs::srv::SetDigitalOutput_Response";
}

template<>
inline const char * name<igus_rebel_msgs::srv::SetDigitalOutput_Response>()
{
  return "igus_rebel_msgs/srv/SetDigitalOutput_Response";
}

template<>
struct has_fixed_size<igus_rebel_msgs::srv::SetDigitalOutput_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<igus_rebel_msgs::srv::SetDigitalOutput_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<igus_rebel_msgs::srv::SetDigitalOutput_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__traits.hpp"

namespace igus_rebel_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const SetDigitalOutput_Event & msg,
  std::ostream & out)
{
  out << "{";
  // member: info
  {
    out << "info: ";
    to_flow_style_yaml(msg.info, out);
    out << ", ";
  }

  // member: request
  {
    if (msg.request.size() == 0) {
      out << "request: []";
    } else {
      out << "request: [";
      size_t pending_items = msg.request.size();
      for (auto item : msg.request) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: response
  {
    if (msg.response.size() == 0) {
      out << "response: []";
    } else {
      out << "response: [";
      size_t pending_items = msg.response.size();
      for (auto item : msg.response) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SetDigitalOutput_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: info
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "info:\n";
    to_block_style_yaml(msg.info, out, indentation + 2);
  }

  // member: request
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.request.size() == 0) {
      out << "request: []\n";
    } else {
      out << "request:\n";
      for (auto item : msg.request) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: response
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.response.size() == 0) {
      out << "response: []\n";
    } else {
      out << "response:\n";
      for (auto item : msg.response) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SetDigitalOutput_Event & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace igus_rebel_msgs

namespace rosidl_generator_traits
{

[[deprecated("use igus_rebel_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const igus_rebel_msgs::srv::SetDigitalOutput_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  igus_rebel_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use igus_rebel_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const igus_rebel_msgs::srv::SetDigitalOutput_Event & msg)
{
  return igus_rebel_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<igus_rebel_msgs::srv::SetDigitalOutput_Event>()
{
  return "igus_rebel_msgs::srv::SetDigitalOutput_Event";
}

template<>
inline const char * name<igus_rebel_msgs::srv::SetDigitalOutput_Event>()
{
  return "igus_rebel_msgs/srv/SetDigitalOutput_Event";
}

template<>
struct has_fixed_size<igus_rebel_msgs::srv::SetDigitalOutput_Event>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<igus_rebel_msgs::srv::SetDigitalOutput_Event>
  : std::integral_constant<bool, has_bounded_size<igus_rebel_msgs::srv::SetDigitalOutput_Request>::value && has_bounded_size<igus_rebel_msgs::srv::SetDigitalOutput_Response>::value && has_bounded_size<service_msgs::msg::ServiceEventInfo>::value> {};

template<>
struct is_message<igus_rebel_msgs::srv::SetDigitalOutput_Event>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<igus_rebel_msgs::srv::SetDigitalOutput>()
{
  return "igus_rebel_msgs::srv::SetDigitalOutput";
}

template<>
inline const char * name<igus_rebel_msgs::srv::SetDigitalOutput>()
{
  return "igus_rebel_msgs/srv/SetDigitalOutput";
}

template<>
struct has_fixed_size<igus_rebel_msgs::srv::SetDigitalOutput>
  : std::integral_constant<
    bool,
    has_fixed_size<igus_rebel_msgs::srv::SetDigitalOutput_Request>::value &&
    has_fixed_size<igus_rebel_msgs::srv::SetDigitalOutput_Response>::value
  >
{
};

template<>
struct has_bounded_size<igus_rebel_msgs::srv::SetDigitalOutput>
  : std::integral_constant<
    bool,
    has_bounded_size<igus_rebel_msgs::srv::SetDigitalOutput_Request>::value &&
    has_bounded_size<igus_rebel_msgs::srv::SetDigitalOutput_Response>::value
  >
{
};

template<>
struct is_service<igus_rebel_msgs::srv::SetDigitalOutput>
  : std::true_type
{
};

template<>
struct is_service_request<igus_rebel_msgs::srv::SetDigitalOutput_Request>
  : std::true_type
{
};

template<>
struct is_service_response<igus_rebel_msgs::srv::SetDigitalOutput_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // IGUS_REBEL_MSGS__SRV__DETAIL__SET_DIGITAL_OUTPUT__TRAITS_HPP_
