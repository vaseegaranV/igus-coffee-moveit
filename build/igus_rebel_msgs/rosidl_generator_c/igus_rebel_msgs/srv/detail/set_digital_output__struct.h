// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from igus_rebel_msgs:srv/SetDigitalOutput.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "igus_rebel_msgs/srv/set_digital_output.h"


#ifndef IGUS_REBEL_MSGS__SRV__DETAIL__SET_DIGITAL_OUTPUT__STRUCT_H_
#define IGUS_REBEL_MSGS__SRV__DETAIL__SET_DIGITAL_OUTPUT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'output'
#include "igus_rebel_msgs/msg/detail/digital_output__struct.h"

/// Struct defined in srv/SetDigitalOutput in the package igus_rebel_msgs.
typedef struct igus_rebel_msgs__srv__SetDigitalOutput_Request
{
  igus_rebel_msgs__msg__DigitalOutput output;
} igus_rebel_msgs__srv__SetDigitalOutput_Request;

// Struct for a sequence of igus_rebel_msgs__srv__SetDigitalOutput_Request.
typedef struct igus_rebel_msgs__srv__SetDigitalOutput_Request__Sequence
{
  igus_rebel_msgs__srv__SetDigitalOutput_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} igus_rebel_msgs__srv__SetDigitalOutput_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'message'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/SetDigitalOutput in the package igus_rebel_msgs.
typedef struct igus_rebel_msgs__srv__SetDigitalOutput_Response
{
  bool success;
  rosidl_runtime_c__String message;
} igus_rebel_msgs__srv__SetDigitalOutput_Response;

// Struct for a sequence of igus_rebel_msgs__srv__SetDigitalOutput_Response.
typedef struct igus_rebel_msgs__srv__SetDigitalOutput_Response__Sequence
{
  igus_rebel_msgs__srv__SetDigitalOutput_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} igus_rebel_msgs__srv__SetDigitalOutput_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  igus_rebel_msgs__srv__SetDigitalOutput_Event__request__MAX_SIZE = 1
};
// response
enum
{
  igus_rebel_msgs__srv__SetDigitalOutput_Event__response__MAX_SIZE = 1
};

/// Struct defined in srv/SetDigitalOutput in the package igus_rebel_msgs.
typedef struct igus_rebel_msgs__srv__SetDigitalOutput_Event
{
  service_msgs__msg__ServiceEventInfo info;
  igus_rebel_msgs__srv__SetDigitalOutput_Request__Sequence request;
  igus_rebel_msgs__srv__SetDigitalOutput_Response__Sequence response;
} igus_rebel_msgs__srv__SetDigitalOutput_Event;

// Struct for a sequence of igus_rebel_msgs__srv__SetDigitalOutput_Event.
typedef struct igus_rebel_msgs__srv__SetDigitalOutput_Event__Sequence
{
  igus_rebel_msgs__srv__SetDigitalOutput_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} igus_rebel_msgs__srv__SetDigitalOutput_Event__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // IGUS_REBEL_MSGS__SRV__DETAIL__SET_DIGITAL_OUTPUT__STRUCT_H_
