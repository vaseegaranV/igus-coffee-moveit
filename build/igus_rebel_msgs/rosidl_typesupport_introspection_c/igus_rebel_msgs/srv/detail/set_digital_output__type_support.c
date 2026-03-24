// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from igus_rebel_msgs:srv/SetDigitalOutput.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "igus_rebel_msgs/srv/detail/set_digital_output__rosidl_typesupport_introspection_c.h"
#include "igus_rebel_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "igus_rebel_msgs/srv/detail/set_digital_output__functions.h"
#include "igus_rebel_msgs/srv/detail/set_digital_output__struct.h"


// Include directives for member types
// Member `output`
#include "igus_rebel_msgs/msg/digital_output.h"
// Member `output`
#include "igus_rebel_msgs/msg/detail/digital_output__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void igus_rebel_msgs__srv__SetDigitalOutput_Request__rosidl_typesupport_introspection_c__SetDigitalOutput_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  igus_rebel_msgs__srv__SetDigitalOutput_Request__init(message_memory);
}

void igus_rebel_msgs__srv__SetDigitalOutput_Request__rosidl_typesupport_introspection_c__SetDigitalOutput_Request_fini_function(void * message_memory)
{
  igus_rebel_msgs__srv__SetDigitalOutput_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember igus_rebel_msgs__srv__SetDigitalOutput_Request__rosidl_typesupport_introspection_c__SetDigitalOutput_Request_message_member_array[1] = {
  {
    "output",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(igus_rebel_msgs__srv__SetDigitalOutput_Request, output),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers igus_rebel_msgs__srv__SetDigitalOutput_Request__rosidl_typesupport_introspection_c__SetDigitalOutput_Request_message_members = {
  "igus_rebel_msgs__srv",  // message namespace
  "SetDigitalOutput_Request",  // message name
  1,  // number of fields
  sizeof(igus_rebel_msgs__srv__SetDigitalOutput_Request),
  false,  // has_any_key_member_
  igus_rebel_msgs__srv__SetDigitalOutput_Request__rosidl_typesupport_introspection_c__SetDigitalOutput_Request_message_member_array,  // message members
  igus_rebel_msgs__srv__SetDigitalOutput_Request__rosidl_typesupport_introspection_c__SetDigitalOutput_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  igus_rebel_msgs__srv__SetDigitalOutput_Request__rosidl_typesupport_introspection_c__SetDigitalOutput_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t igus_rebel_msgs__srv__SetDigitalOutput_Request__rosidl_typesupport_introspection_c__SetDigitalOutput_Request_message_type_support_handle = {
  0,
  &igus_rebel_msgs__srv__SetDigitalOutput_Request__rosidl_typesupport_introspection_c__SetDigitalOutput_Request_message_members,
  get_message_typesupport_handle_function,
  &igus_rebel_msgs__srv__SetDigitalOutput_Request__get_type_hash,
  &igus_rebel_msgs__srv__SetDigitalOutput_Request__get_type_description,
  &igus_rebel_msgs__srv__SetDigitalOutput_Request__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_igus_rebel_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, igus_rebel_msgs, srv, SetDigitalOutput_Request)() {
  igus_rebel_msgs__srv__SetDigitalOutput_Request__rosidl_typesupport_introspection_c__SetDigitalOutput_Request_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, igus_rebel_msgs, msg, DigitalOutput)();
  if (!igus_rebel_msgs__srv__SetDigitalOutput_Request__rosidl_typesupport_introspection_c__SetDigitalOutput_Request_message_type_support_handle.typesupport_identifier) {
    igus_rebel_msgs__srv__SetDigitalOutput_Request__rosidl_typesupport_introspection_c__SetDigitalOutput_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &igus_rebel_msgs__srv__SetDigitalOutput_Request__rosidl_typesupport_introspection_c__SetDigitalOutput_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "igus_rebel_msgs/srv/detail/set_digital_output__rosidl_typesupport_introspection_c.h"
// already included above
// #include "igus_rebel_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "igus_rebel_msgs/srv/detail/set_digital_output__functions.h"
// already included above
// #include "igus_rebel_msgs/srv/detail/set_digital_output__struct.h"


// Include directives for member types
// Member `message`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void igus_rebel_msgs__srv__SetDigitalOutput_Response__rosidl_typesupport_introspection_c__SetDigitalOutput_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  igus_rebel_msgs__srv__SetDigitalOutput_Response__init(message_memory);
}

void igus_rebel_msgs__srv__SetDigitalOutput_Response__rosidl_typesupport_introspection_c__SetDigitalOutput_Response_fini_function(void * message_memory)
{
  igus_rebel_msgs__srv__SetDigitalOutput_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember igus_rebel_msgs__srv__SetDigitalOutput_Response__rosidl_typesupport_introspection_c__SetDigitalOutput_Response_message_member_array[2] = {
  {
    "success",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(igus_rebel_msgs__srv__SetDigitalOutput_Response, success),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "message",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(igus_rebel_msgs__srv__SetDigitalOutput_Response, message),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers igus_rebel_msgs__srv__SetDigitalOutput_Response__rosidl_typesupport_introspection_c__SetDigitalOutput_Response_message_members = {
  "igus_rebel_msgs__srv",  // message namespace
  "SetDigitalOutput_Response",  // message name
  2,  // number of fields
  sizeof(igus_rebel_msgs__srv__SetDigitalOutput_Response),
  false,  // has_any_key_member_
  igus_rebel_msgs__srv__SetDigitalOutput_Response__rosidl_typesupport_introspection_c__SetDigitalOutput_Response_message_member_array,  // message members
  igus_rebel_msgs__srv__SetDigitalOutput_Response__rosidl_typesupport_introspection_c__SetDigitalOutput_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  igus_rebel_msgs__srv__SetDigitalOutput_Response__rosidl_typesupport_introspection_c__SetDigitalOutput_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t igus_rebel_msgs__srv__SetDigitalOutput_Response__rosidl_typesupport_introspection_c__SetDigitalOutput_Response_message_type_support_handle = {
  0,
  &igus_rebel_msgs__srv__SetDigitalOutput_Response__rosidl_typesupport_introspection_c__SetDigitalOutput_Response_message_members,
  get_message_typesupport_handle_function,
  &igus_rebel_msgs__srv__SetDigitalOutput_Response__get_type_hash,
  &igus_rebel_msgs__srv__SetDigitalOutput_Response__get_type_description,
  &igus_rebel_msgs__srv__SetDigitalOutput_Response__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_igus_rebel_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, igus_rebel_msgs, srv, SetDigitalOutput_Response)() {
  if (!igus_rebel_msgs__srv__SetDigitalOutput_Response__rosidl_typesupport_introspection_c__SetDigitalOutput_Response_message_type_support_handle.typesupport_identifier) {
    igus_rebel_msgs__srv__SetDigitalOutput_Response__rosidl_typesupport_introspection_c__SetDigitalOutput_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &igus_rebel_msgs__srv__SetDigitalOutput_Response__rosidl_typesupport_introspection_c__SetDigitalOutput_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "igus_rebel_msgs/srv/detail/set_digital_output__rosidl_typesupport_introspection_c.h"
// already included above
// #include "igus_rebel_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "igus_rebel_msgs/srv/detail/set_digital_output__functions.h"
// already included above
// #include "igus_rebel_msgs/srv/detail/set_digital_output__struct.h"


// Include directives for member types
// Member `info`
#include "service_msgs/msg/service_event_info.h"
// Member `info`
#include "service_msgs/msg/detail/service_event_info__rosidl_typesupport_introspection_c.h"
// Member `request`
// Member `response`
#include "igus_rebel_msgs/srv/set_digital_output.h"
// Member `request`
// Member `response`
// already included above
// #include "igus_rebel_msgs/srv/detail/set_digital_output__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void igus_rebel_msgs__srv__SetDigitalOutput_Event__rosidl_typesupport_introspection_c__SetDigitalOutput_Event_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  igus_rebel_msgs__srv__SetDigitalOutput_Event__init(message_memory);
}

void igus_rebel_msgs__srv__SetDigitalOutput_Event__rosidl_typesupport_introspection_c__SetDigitalOutput_Event_fini_function(void * message_memory)
{
  igus_rebel_msgs__srv__SetDigitalOutput_Event__fini(message_memory);
}

size_t igus_rebel_msgs__srv__SetDigitalOutput_Event__rosidl_typesupport_introspection_c__size_function__SetDigitalOutput_Event__request(
  const void * untyped_member)
{
  const igus_rebel_msgs__srv__SetDigitalOutput_Request__Sequence * member =
    (const igus_rebel_msgs__srv__SetDigitalOutput_Request__Sequence *)(untyped_member);
  return member->size;
}

const void * igus_rebel_msgs__srv__SetDigitalOutput_Event__rosidl_typesupport_introspection_c__get_const_function__SetDigitalOutput_Event__request(
  const void * untyped_member, size_t index)
{
  const igus_rebel_msgs__srv__SetDigitalOutput_Request__Sequence * member =
    (const igus_rebel_msgs__srv__SetDigitalOutput_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void * igus_rebel_msgs__srv__SetDigitalOutput_Event__rosidl_typesupport_introspection_c__get_function__SetDigitalOutput_Event__request(
  void * untyped_member, size_t index)
{
  igus_rebel_msgs__srv__SetDigitalOutput_Request__Sequence * member =
    (igus_rebel_msgs__srv__SetDigitalOutput_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void igus_rebel_msgs__srv__SetDigitalOutput_Event__rosidl_typesupport_introspection_c__fetch_function__SetDigitalOutput_Event__request(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const igus_rebel_msgs__srv__SetDigitalOutput_Request * item =
    ((const igus_rebel_msgs__srv__SetDigitalOutput_Request *)
    igus_rebel_msgs__srv__SetDigitalOutput_Event__rosidl_typesupport_introspection_c__get_const_function__SetDigitalOutput_Event__request(untyped_member, index));
  igus_rebel_msgs__srv__SetDigitalOutput_Request * value =
    (igus_rebel_msgs__srv__SetDigitalOutput_Request *)(untyped_value);
  *value = *item;
}

void igus_rebel_msgs__srv__SetDigitalOutput_Event__rosidl_typesupport_introspection_c__assign_function__SetDigitalOutput_Event__request(
  void * untyped_member, size_t index, const void * untyped_value)
{
  igus_rebel_msgs__srv__SetDigitalOutput_Request * item =
    ((igus_rebel_msgs__srv__SetDigitalOutput_Request *)
    igus_rebel_msgs__srv__SetDigitalOutput_Event__rosidl_typesupport_introspection_c__get_function__SetDigitalOutput_Event__request(untyped_member, index));
  const igus_rebel_msgs__srv__SetDigitalOutput_Request * value =
    (const igus_rebel_msgs__srv__SetDigitalOutput_Request *)(untyped_value);
  *item = *value;
}

bool igus_rebel_msgs__srv__SetDigitalOutput_Event__rosidl_typesupport_introspection_c__resize_function__SetDigitalOutput_Event__request(
  void * untyped_member, size_t size)
{
  igus_rebel_msgs__srv__SetDigitalOutput_Request__Sequence * member =
    (igus_rebel_msgs__srv__SetDigitalOutput_Request__Sequence *)(untyped_member);
  igus_rebel_msgs__srv__SetDigitalOutput_Request__Sequence__fini(member);
  return igus_rebel_msgs__srv__SetDigitalOutput_Request__Sequence__init(member, size);
}

size_t igus_rebel_msgs__srv__SetDigitalOutput_Event__rosidl_typesupport_introspection_c__size_function__SetDigitalOutput_Event__response(
  const void * untyped_member)
{
  const igus_rebel_msgs__srv__SetDigitalOutput_Response__Sequence * member =
    (const igus_rebel_msgs__srv__SetDigitalOutput_Response__Sequence *)(untyped_member);
  return member->size;
}

const void * igus_rebel_msgs__srv__SetDigitalOutput_Event__rosidl_typesupport_introspection_c__get_const_function__SetDigitalOutput_Event__response(
  const void * untyped_member, size_t index)
{
  const igus_rebel_msgs__srv__SetDigitalOutput_Response__Sequence * member =
    (const igus_rebel_msgs__srv__SetDigitalOutput_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void * igus_rebel_msgs__srv__SetDigitalOutput_Event__rosidl_typesupport_introspection_c__get_function__SetDigitalOutput_Event__response(
  void * untyped_member, size_t index)
{
  igus_rebel_msgs__srv__SetDigitalOutput_Response__Sequence * member =
    (igus_rebel_msgs__srv__SetDigitalOutput_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void igus_rebel_msgs__srv__SetDigitalOutput_Event__rosidl_typesupport_introspection_c__fetch_function__SetDigitalOutput_Event__response(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const igus_rebel_msgs__srv__SetDigitalOutput_Response * item =
    ((const igus_rebel_msgs__srv__SetDigitalOutput_Response *)
    igus_rebel_msgs__srv__SetDigitalOutput_Event__rosidl_typesupport_introspection_c__get_const_function__SetDigitalOutput_Event__response(untyped_member, index));
  igus_rebel_msgs__srv__SetDigitalOutput_Response * value =
    (igus_rebel_msgs__srv__SetDigitalOutput_Response *)(untyped_value);
  *value = *item;
}

void igus_rebel_msgs__srv__SetDigitalOutput_Event__rosidl_typesupport_introspection_c__assign_function__SetDigitalOutput_Event__response(
  void * untyped_member, size_t index, const void * untyped_value)
{
  igus_rebel_msgs__srv__SetDigitalOutput_Response * item =
    ((igus_rebel_msgs__srv__SetDigitalOutput_Response *)
    igus_rebel_msgs__srv__SetDigitalOutput_Event__rosidl_typesupport_introspection_c__get_function__SetDigitalOutput_Event__response(untyped_member, index));
  const igus_rebel_msgs__srv__SetDigitalOutput_Response * value =
    (const igus_rebel_msgs__srv__SetDigitalOutput_Response *)(untyped_value);
  *item = *value;
}

bool igus_rebel_msgs__srv__SetDigitalOutput_Event__rosidl_typesupport_introspection_c__resize_function__SetDigitalOutput_Event__response(
  void * untyped_member, size_t size)
{
  igus_rebel_msgs__srv__SetDigitalOutput_Response__Sequence * member =
    (igus_rebel_msgs__srv__SetDigitalOutput_Response__Sequence *)(untyped_member);
  igus_rebel_msgs__srv__SetDigitalOutput_Response__Sequence__fini(member);
  return igus_rebel_msgs__srv__SetDigitalOutput_Response__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember igus_rebel_msgs__srv__SetDigitalOutput_Event__rosidl_typesupport_introspection_c__SetDigitalOutput_Event_message_member_array[3] = {
  {
    "info",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(igus_rebel_msgs__srv__SetDigitalOutput_Event, info),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "request",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(igus_rebel_msgs__srv__SetDigitalOutput_Event, request),  // bytes offset in struct
    NULL,  // default value
    igus_rebel_msgs__srv__SetDigitalOutput_Event__rosidl_typesupport_introspection_c__size_function__SetDigitalOutput_Event__request,  // size() function pointer
    igus_rebel_msgs__srv__SetDigitalOutput_Event__rosidl_typesupport_introspection_c__get_const_function__SetDigitalOutput_Event__request,  // get_const(index) function pointer
    igus_rebel_msgs__srv__SetDigitalOutput_Event__rosidl_typesupport_introspection_c__get_function__SetDigitalOutput_Event__request,  // get(index) function pointer
    igus_rebel_msgs__srv__SetDigitalOutput_Event__rosidl_typesupport_introspection_c__fetch_function__SetDigitalOutput_Event__request,  // fetch(index, &value) function pointer
    igus_rebel_msgs__srv__SetDigitalOutput_Event__rosidl_typesupport_introspection_c__assign_function__SetDigitalOutput_Event__request,  // assign(index, value) function pointer
    igus_rebel_msgs__srv__SetDigitalOutput_Event__rosidl_typesupport_introspection_c__resize_function__SetDigitalOutput_Event__request  // resize(index) function pointer
  },
  {
    "response",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(igus_rebel_msgs__srv__SetDigitalOutput_Event, response),  // bytes offset in struct
    NULL,  // default value
    igus_rebel_msgs__srv__SetDigitalOutput_Event__rosidl_typesupport_introspection_c__size_function__SetDigitalOutput_Event__response,  // size() function pointer
    igus_rebel_msgs__srv__SetDigitalOutput_Event__rosidl_typesupport_introspection_c__get_const_function__SetDigitalOutput_Event__response,  // get_const(index) function pointer
    igus_rebel_msgs__srv__SetDigitalOutput_Event__rosidl_typesupport_introspection_c__get_function__SetDigitalOutput_Event__response,  // get(index) function pointer
    igus_rebel_msgs__srv__SetDigitalOutput_Event__rosidl_typesupport_introspection_c__fetch_function__SetDigitalOutput_Event__response,  // fetch(index, &value) function pointer
    igus_rebel_msgs__srv__SetDigitalOutput_Event__rosidl_typesupport_introspection_c__assign_function__SetDigitalOutput_Event__response,  // assign(index, value) function pointer
    igus_rebel_msgs__srv__SetDigitalOutput_Event__rosidl_typesupport_introspection_c__resize_function__SetDigitalOutput_Event__response  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers igus_rebel_msgs__srv__SetDigitalOutput_Event__rosidl_typesupport_introspection_c__SetDigitalOutput_Event_message_members = {
  "igus_rebel_msgs__srv",  // message namespace
  "SetDigitalOutput_Event",  // message name
  3,  // number of fields
  sizeof(igus_rebel_msgs__srv__SetDigitalOutput_Event),
  false,  // has_any_key_member_
  igus_rebel_msgs__srv__SetDigitalOutput_Event__rosidl_typesupport_introspection_c__SetDigitalOutput_Event_message_member_array,  // message members
  igus_rebel_msgs__srv__SetDigitalOutput_Event__rosidl_typesupport_introspection_c__SetDigitalOutput_Event_init_function,  // function to initialize message memory (memory has to be allocated)
  igus_rebel_msgs__srv__SetDigitalOutput_Event__rosidl_typesupport_introspection_c__SetDigitalOutput_Event_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t igus_rebel_msgs__srv__SetDigitalOutput_Event__rosidl_typesupport_introspection_c__SetDigitalOutput_Event_message_type_support_handle = {
  0,
  &igus_rebel_msgs__srv__SetDigitalOutput_Event__rosidl_typesupport_introspection_c__SetDigitalOutput_Event_message_members,
  get_message_typesupport_handle_function,
  &igus_rebel_msgs__srv__SetDigitalOutput_Event__get_type_hash,
  &igus_rebel_msgs__srv__SetDigitalOutput_Event__get_type_description,
  &igus_rebel_msgs__srv__SetDigitalOutput_Event__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_igus_rebel_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, igus_rebel_msgs, srv, SetDigitalOutput_Event)() {
  igus_rebel_msgs__srv__SetDigitalOutput_Event__rosidl_typesupport_introspection_c__SetDigitalOutput_Event_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, service_msgs, msg, ServiceEventInfo)();
  igus_rebel_msgs__srv__SetDigitalOutput_Event__rosidl_typesupport_introspection_c__SetDigitalOutput_Event_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, igus_rebel_msgs, srv, SetDigitalOutput_Request)();
  igus_rebel_msgs__srv__SetDigitalOutput_Event__rosidl_typesupport_introspection_c__SetDigitalOutput_Event_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, igus_rebel_msgs, srv, SetDigitalOutput_Response)();
  if (!igus_rebel_msgs__srv__SetDigitalOutput_Event__rosidl_typesupport_introspection_c__SetDigitalOutput_Event_message_type_support_handle.typesupport_identifier) {
    igus_rebel_msgs__srv__SetDigitalOutput_Event__rosidl_typesupport_introspection_c__SetDigitalOutput_Event_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &igus_rebel_msgs__srv__SetDigitalOutput_Event__rosidl_typesupport_introspection_c__SetDigitalOutput_Event_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "igus_rebel_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "igus_rebel_msgs/srv/detail/set_digital_output__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers igus_rebel_msgs__srv__detail__set_digital_output__rosidl_typesupport_introspection_c__SetDigitalOutput_service_members = {
  "igus_rebel_msgs__srv",  // service namespace
  "SetDigitalOutput",  // service name
  // the following fields are initialized below on first access
  NULL,  // request message
  // igus_rebel_msgs__srv__detail__set_digital_output__rosidl_typesupport_introspection_c__SetDigitalOutput_Request_message_type_support_handle,
  NULL,  // response message
  // igus_rebel_msgs__srv__detail__set_digital_output__rosidl_typesupport_introspection_c__SetDigitalOutput_Response_message_type_support_handle
  NULL  // event_message
  // igus_rebel_msgs__srv__detail__set_digital_output__rosidl_typesupport_introspection_c__SetDigitalOutput_Response_message_type_support_handle
};


static rosidl_service_type_support_t igus_rebel_msgs__srv__detail__set_digital_output__rosidl_typesupport_introspection_c__SetDigitalOutput_service_type_support_handle = {
  0,
  &igus_rebel_msgs__srv__detail__set_digital_output__rosidl_typesupport_introspection_c__SetDigitalOutput_service_members,
  get_service_typesupport_handle_function,
  &igus_rebel_msgs__srv__SetDigitalOutput_Request__rosidl_typesupport_introspection_c__SetDigitalOutput_Request_message_type_support_handle,
  &igus_rebel_msgs__srv__SetDigitalOutput_Response__rosidl_typesupport_introspection_c__SetDigitalOutput_Response_message_type_support_handle,
  &igus_rebel_msgs__srv__SetDigitalOutput_Event__rosidl_typesupport_introspection_c__SetDigitalOutput_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    igus_rebel_msgs,
    srv,
    SetDigitalOutput
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    igus_rebel_msgs,
    srv,
    SetDigitalOutput
  ),
  &igus_rebel_msgs__srv__SetDigitalOutput__get_type_hash,
  &igus_rebel_msgs__srv__SetDigitalOutput__get_type_description,
  &igus_rebel_msgs__srv__SetDigitalOutput__get_type_description_sources,
};

// Forward declaration of message type support functions for service members
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, igus_rebel_msgs, srv, SetDigitalOutput_Request)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, igus_rebel_msgs, srv, SetDigitalOutput_Response)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, igus_rebel_msgs, srv, SetDigitalOutput_Event)(void);

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_igus_rebel_msgs
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, igus_rebel_msgs, srv, SetDigitalOutput)(void) {
  if (!igus_rebel_msgs__srv__detail__set_digital_output__rosidl_typesupport_introspection_c__SetDigitalOutput_service_type_support_handle.typesupport_identifier) {
    igus_rebel_msgs__srv__detail__set_digital_output__rosidl_typesupport_introspection_c__SetDigitalOutput_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)igus_rebel_msgs__srv__detail__set_digital_output__rosidl_typesupport_introspection_c__SetDigitalOutput_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, igus_rebel_msgs, srv, SetDigitalOutput_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, igus_rebel_msgs, srv, SetDigitalOutput_Response)()->data;
  }
  if (!service_members->event_members_) {
    service_members->event_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, igus_rebel_msgs, srv, SetDigitalOutput_Event)()->data;
  }

  return &igus_rebel_msgs__srv__detail__set_digital_output__rosidl_typesupport_introspection_c__SetDigitalOutput_service_type_support_handle;
}
