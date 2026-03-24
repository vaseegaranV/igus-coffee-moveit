// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from igus_rebel_msgs:msg/DigitalOutput.idl
// generated code does not contain a copyright notice
#include "igus_rebel_msgs/msg/detail/digital_output__rosidl_typesupport_fastrtps_cpp.hpp"
#include "igus_rebel_msgs/msg/detail/digital_output__functions.h"
#include "igus_rebel_msgs/msg/detail/digital_output__struct.hpp"

#include <cstddef>
#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/serialization_helpers.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

namespace igus_rebel_msgs
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{


bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_igus_rebel_msgs
cdr_serialize(
  const igus_rebel_msgs::msg::DigitalOutput & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: output
  cdr << ros_message.output;

  // Member: is_on
  cdr << (ros_message.is_on ? true : false);

  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_igus_rebel_msgs
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  igus_rebel_msgs::msg::DigitalOutput & ros_message)
{
  // Member: output
  cdr >> ros_message.output;

  // Member: is_on
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.is_on = tmp ? true : false;
  }

  return true;
}  // NOLINT(readability/fn_size)


size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_igus_rebel_msgs
get_serialized_size(
  const igus_rebel_msgs::msg::DigitalOutput & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: output
  {
    size_t item_size = sizeof(ros_message.output);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Member: is_on
  {
    size_t item_size = sizeof(ros_message.is_on);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}


size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_igus_rebel_msgs
max_serialized_size_DigitalOutput(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // Member: output
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // Member: is_on
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = igus_rebel_msgs::msg::DigitalOutput;
    is_plain =
      (
      offsetof(DataType, is_on) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_igus_rebel_msgs
cdr_serialize_key(
  const igus_rebel_msgs::msg::DigitalOutput & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: output
  cdr << ros_message.output;

  // Member: is_on
  cdr << (ros_message.is_on ? true : false);

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_igus_rebel_msgs
get_serialized_size_key(
  const igus_rebel_msgs::msg::DigitalOutput & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: output
  {
    size_t item_size = sizeof(ros_message.output);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Member: is_on
  {
    size_t item_size = sizeof(ros_message.is_on);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_igus_rebel_msgs
max_serialized_size_key_DigitalOutput(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // Member: output
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: is_on
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = igus_rebel_msgs::msg::DigitalOutput;
    is_plain =
      (
      offsetof(DataType, is_on) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}


static bool _DigitalOutput__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const igus_rebel_msgs::msg::DigitalOutput *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _DigitalOutput__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<igus_rebel_msgs::msg::DigitalOutput *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _DigitalOutput__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const igus_rebel_msgs::msg::DigitalOutput *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _DigitalOutput__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_DigitalOutput(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _DigitalOutput__callbacks = {
  "igus_rebel_msgs::msg",
  "DigitalOutput",
  _DigitalOutput__cdr_serialize,
  _DigitalOutput__cdr_deserialize,
  _DigitalOutput__get_serialized_size,
  _DigitalOutput__max_serialized_size,
  nullptr
};

static rosidl_message_type_support_t _DigitalOutput__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_DigitalOutput__callbacks,
  get_message_typesupport_handle_function,
  &igus_rebel_msgs__msg__DigitalOutput__get_type_hash,
  &igus_rebel_msgs__msg__DigitalOutput__get_type_description,
  &igus_rebel_msgs__msg__DigitalOutput__get_type_description_sources,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace igus_rebel_msgs

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_igus_rebel_msgs
const rosidl_message_type_support_t *
get_message_type_support_handle<igus_rebel_msgs::msg::DigitalOutput>()
{
  return &igus_rebel_msgs::msg::typesupport_fastrtps_cpp::_DigitalOutput__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, igus_rebel_msgs, msg, DigitalOutput)() {
  return &igus_rebel_msgs::msg::typesupport_fastrtps_cpp::_DigitalOutput__handle;
}

#ifdef __cplusplus
}
#endif
