// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from igus_rebel_msgs:msg/DigitalOutput.idl
// generated code does not contain a copyright notice

#include "igus_rebel_msgs/msg/detail/digital_output__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_igus_rebel_msgs
const rosidl_type_hash_t *
igus_rebel_msgs__msg__DigitalOutput__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x9e, 0x6e, 0xcf, 0x26, 0x79, 0xca, 0x56, 0xd0,
      0x7e, 0x04, 0x1a, 0xc6, 0x25, 0x4a, 0xc2, 0x9d,
      0x64, 0x93, 0x10, 0x5e, 0x77, 0x1e, 0x31, 0xd2,
      0x76, 0xe1, 0x4f, 0xf8, 0xe5, 0x50, 0x8c, 0x47,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char igus_rebel_msgs__msg__DigitalOutput__TYPE_NAME[] = "igus_rebel_msgs/msg/DigitalOutput";

// Define type names, field names, and default values
static char igus_rebel_msgs__msg__DigitalOutput__FIELD_NAME__output[] = "output";
static char igus_rebel_msgs__msg__DigitalOutput__FIELD_NAME__is_on[] = "is_on";

static rosidl_runtime_c__type_description__Field igus_rebel_msgs__msg__DigitalOutput__FIELDS[] = {
  {
    {igus_rebel_msgs__msg__DigitalOutput__FIELD_NAME__output, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {igus_rebel_msgs__msg__DigitalOutput__FIELD_NAME__is_on, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
igus_rebel_msgs__msg__DigitalOutput__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {igus_rebel_msgs__msg__DigitalOutput__TYPE_NAME, 33, 33},
      {igus_rebel_msgs__msg__DigitalOutput__FIELDS, 2, 2},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "int8 output\n"
  "bool is_on";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
igus_rebel_msgs__msg__DigitalOutput__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {igus_rebel_msgs__msg__DigitalOutput__TYPE_NAME, 33, 33},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 23, 23},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
igus_rebel_msgs__msg__DigitalOutput__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *igus_rebel_msgs__msg__DigitalOutput__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
