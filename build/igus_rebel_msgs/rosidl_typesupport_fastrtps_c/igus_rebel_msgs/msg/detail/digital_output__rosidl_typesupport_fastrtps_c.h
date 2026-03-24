// generated from rosidl_typesupport_fastrtps_c/resource/idl__rosidl_typesupport_fastrtps_c.h.em
// with input from igus_rebel_msgs:msg/DigitalOutput.idl
// generated code does not contain a copyright notice
#ifndef IGUS_REBEL_MSGS__MSG__DETAIL__DIGITAL_OUTPUT__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
#define IGUS_REBEL_MSGS__MSG__DETAIL__DIGITAL_OUTPUT__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_


#include <stddef.h>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "igus_rebel_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "igus_rebel_msgs/msg/detail/digital_output__struct.h"
#include "fastcdr/Cdr.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_igus_rebel_msgs
bool cdr_serialize_igus_rebel_msgs__msg__DigitalOutput(
  const igus_rebel_msgs__msg__DigitalOutput * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_igus_rebel_msgs
bool cdr_deserialize_igus_rebel_msgs__msg__DigitalOutput(
  eprosima::fastcdr::Cdr &,
  igus_rebel_msgs__msg__DigitalOutput * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_igus_rebel_msgs
size_t get_serialized_size_igus_rebel_msgs__msg__DigitalOutput(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_igus_rebel_msgs
size_t max_serialized_size_igus_rebel_msgs__msg__DigitalOutput(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_igus_rebel_msgs
bool cdr_serialize_key_igus_rebel_msgs__msg__DigitalOutput(
  const igus_rebel_msgs__msg__DigitalOutput * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_igus_rebel_msgs
size_t get_serialized_size_key_igus_rebel_msgs__msg__DigitalOutput(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_igus_rebel_msgs
size_t max_serialized_size_key_igus_rebel_msgs__msg__DigitalOutput(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_igus_rebel_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, igus_rebel_msgs, msg, DigitalOutput)();

#ifdef __cplusplus
}
#endif

#endif  // IGUS_REBEL_MSGS__MSG__DETAIL__DIGITAL_OUTPUT__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
