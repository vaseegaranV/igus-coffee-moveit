// generated from rosidl_generator_c/resource/idl__type_support.h.em
// with input from igus_rebel_msgs:srv/SetDigitalOutput.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "igus_rebel_msgs/srv/set_digital_output.h"


#ifndef IGUS_REBEL_MSGS__SRV__DETAIL__SET_DIGITAL_OUTPUT__TYPE_SUPPORT_H_
#define IGUS_REBEL_MSGS__SRV__DETAIL__SET_DIGITAL_OUTPUT__TYPE_SUPPORT_H_

#include "rosidl_typesupport_interface/macros.h"

#include "igus_rebel_msgs/msg/rosidl_generator_c__visibility_control.h"

#ifdef __cplusplus
extern "C"
{
#endif

#include "rosidl_runtime_c/message_type_support_struct.h"

// Forward declare the get type support functions for this type.
ROSIDL_GENERATOR_C_PUBLIC_igus_rebel_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c,
  igus_rebel_msgs,
  srv,
  SetDigitalOutput_Request
)(void);

// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"

// Forward declare the get type support functions for this type.
ROSIDL_GENERATOR_C_PUBLIC_igus_rebel_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c,
  igus_rebel_msgs,
  srv,
  SetDigitalOutput_Response
)(void);

// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"

// Forward declare the get type support functions for this type.
ROSIDL_GENERATOR_C_PUBLIC_igus_rebel_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c,
  igus_rebel_msgs,
  srv,
  SetDigitalOutput_Event
)(void);

#include "rosidl_runtime_c/service_type_support_struct.h"

// Forward declare the get type support functions for this type.
ROSIDL_GENERATOR_C_PUBLIC_igus_rebel_msgs
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
  rosidl_typesupport_c,
  igus_rebel_msgs,
  srv,
  SetDigitalOutput
)(void);

// Forward declare the function to create a service event message for this type.
ROSIDL_GENERATOR_C_PUBLIC_igus_rebel_msgs
void *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c,
  igus_rebel_msgs,
  srv,
  SetDigitalOutput
)(
  const rosidl_service_introspection_info_t * info,
  rcutils_allocator_t * allocator,
  const void * request_message,
  const void * response_message);

// Forward declare the function to destroy a service event message for this type.
ROSIDL_GENERATOR_C_PUBLIC_igus_rebel_msgs
bool
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c,
  igus_rebel_msgs,
  srv,
  SetDigitalOutput
)(
  void * event_msg,
  rcutils_allocator_t * allocator);

#ifdef __cplusplus
}
#endif

#endif  // IGUS_REBEL_MSGS__SRV__DETAIL__SET_DIGITAL_OUTPUT__TYPE_SUPPORT_H_
