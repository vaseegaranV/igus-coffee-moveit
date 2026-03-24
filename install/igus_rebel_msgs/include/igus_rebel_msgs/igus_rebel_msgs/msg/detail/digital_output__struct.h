// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from igus_rebel_msgs:msg/DigitalOutput.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "igus_rebel_msgs/msg/digital_output.h"


#ifndef IGUS_REBEL_MSGS__MSG__DETAIL__DIGITAL_OUTPUT__STRUCT_H_
#define IGUS_REBEL_MSGS__MSG__DETAIL__DIGITAL_OUTPUT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/DigitalOutput in the package igus_rebel_msgs.
typedef struct igus_rebel_msgs__msg__DigitalOutput
{
  int8_t output;
  bool is_on;
} igus_rebel_msgs__msg__DigitalOutput;

// Struct for a sequence of igus_rebel_msgs__msg__DigitalOutput.
typedef struct igus_rebel_msgs__msg__DigitalOutput__Sequence
{
  igus_rebel_msgs__msg__DigitalOutput * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} igus_rebel_msgs__msg__DigitalOutput__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // IGUS_REBEL_MSGS__MSG__DETAIL__DIGITAL_OUTPUT__STRUCT_H_
