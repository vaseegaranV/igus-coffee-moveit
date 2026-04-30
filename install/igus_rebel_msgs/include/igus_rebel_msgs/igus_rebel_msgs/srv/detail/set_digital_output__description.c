// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from igus_rebel_msgs:srv/SetDigitalOutput.idl
// generated code does not contain a copyright notice

#include "igus_rebel_msgs/srv/detail/set_digital_output__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_igus_rebel_msgs
const rosidl_type_hash_t *
igus_rebel_msgs__srv__SetDigitalOutput__get_type_hash(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x47, 0x1d, 0xee, 0x03, 0x2f, 0xa2, 0x37, 0xfe,
      0x89, 0xde, 0x95, 0xff, 0xeb, 0xbc, 0xe8, 0x2d,
      0xbf, 0x98, 0x0d, 0x46, 0x75, 0xdb, 0xda, 0xac,
      0xc5, 0x5a, 0xd6, 0x14, 0xf1, 0xde, 0x62, 0xce,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_igus_rebel_msgs
const rosidl_type_hash_t *
igus_rebel_msgs__srv__SetDigitalOutput_Request__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xa3, 0x19, 0x7f, 0xf8, 0x95, 0x78, 0x4c, 0x31,
      0xa6, 0xf0, 0xef, 0x5a, 0xec, 0x19, 0xa3, 0x6c,
      0x72, 0x4b, 0x57, 0xfd, 0xfb, 0x85, 0x19, 0x07,
      0x73, 0xe1, 0x53, 0x01, 0x78, 0x61, 0xd8, 0x8e,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_igus_rebel_msgs
const rosidl_type_hash_t *
igus_rebel_msgs__srv__SetDigitalOutput_Response__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x3b, 0xbc, 0x80, 0x94, 0xd1, 0xe0, 0x70, 0x88,
      0xb8, 0x7f, 0xbf, 0x54, 0x6e, 0x47, 0x69, 0xf9,
      0x95, 0x47, 0x7c, 0xe5, 0x84, 0xa3, 0x9a, 0xdb,
      0x24, 0x7c, 0xf1, 0x57, 0xd8, 0x16, 0x7a, 0x96,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_igus_rebel_msgs
const rosidl_type_hash_t *
igus_rebel_msgs__srv__SetDigitalOutput_Event__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x4e, 0xe2, 0x37, 0xd9, 0x2e, 0xcf, 0x9a, 0xa3,
      0xd6, 0x69, 0xae, 0x1e, 0xdc, 0xbc, 0x7b, 0xa7,
      0x8d, 0x13, 0xa6, 0x0c, 0xec, 0x2c, 0x1b, 0x58,
      0x73, 0x1c, 0x38, 0xcb, 0x44, 0x84, 0x21, 0xc8,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "service_msgs/msg/detail/service_event_info__functions.h"
#include "builtin_interfaces/msg/detail/time__functions.h"
#include "igus_rebel_msgs/msg/detail/digital_output__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t builtin_interfaces__msg__Time__EXPECTED_HASH = {1, {
    0xb1, 0x06, 0x23, 0x5e, 0x25, 0xa4, 0xc5, 0xed,
    0x35, 0x09, 0x8a, 0xa0, 0xa6, 0x1a, 0x3e, 0xe9,
    0xc9, 0xb1, 0x8d, 0x19, 0x7f, 0x39, 0x8b, 0x0e,
    0x42, 0x06, 0xce, 0xa9, 0xac, 0xf9, 0xc1, 0x97,
  }};
static const rosidl_type_hash_t igus_rebel_msgs__msg__DigitalOutput__EXPECTED_HASH = {1, {
    0x9e, 0x6e, 0xcf, 0x26, 0x79, 0xca, 0x56, 0xd0,
    0x7e, 0x04, 0x1a, 0xc6, 0x25, 0x4a, 0xc2, 0x9d,
    0x64, 0x93, 0x10, 0x5e, 0x77, 0x1e, 0x31, 0xd2,
    0x76, 0xe1, 0x4f, 0xf8, 0xe5, 0x50, 0x8c, 0x47,
  }};
static const rosidl_type_hash_t service_msgs__msg__ServiceEventInfo__EXPECTED_HASH = {1, {
    0x41, 0xbc, 0xbb, 0xe0, 0x7a, 0x75, 0xc9, 0xb5,
    0x2b, 0xc9, 0x6b, 0xfd, 0x5c, 0x24, 0xd7, 0xf0,
    0xfc, 0x0a, 0x08, 0xc0, 0xcb, 0x79, 0x21, 0xb3,
    0x37, 0x3c, 0x57, 0x32, 0x34, 0x5a, 0x6f, 0x45,
  }};
#endif

static char igus_rebel_msgs__srv__SetDigitalOutput__TYPE_NAME[] = "igus_rebel_msgs/srv/SetDigitalOutput";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";
static char igus_rebel_msgs__msg__DigitalOutput__TYPE_NAME[] = "igus_rebel_msgs/msg/DigitalOutput";
static char igus_rebel_msgs__srv__SetDigitalOutput_Event__TYPE_NAME[] = "igus_rebel_msgs/srv/SetDigitalOutput_Event";
static char igus_rebel_msgs__srv__SetDigitalOutput_Request__TYPE_NAME[] = "igus_rebel_msgs/srv/SetDigitalOutput_Request";
static char igus_rebel_msgs__srv__SetDigitalOutput_Response__TYPE_NAME[] = "igus_rebel_msgs/srv/SetDigitalOutput_Response";
static char service_msgs__msg__ServiceEventInfo__TYPE_NAME[] = "service_msgs/msg/ServiceEventInfo";

// Define type names, field names, and default values
static char igus_rebel_msgs__srv__SetDigitalOutput__FIELD_NAME__request_message[] = "request_message";
static char igus_rebel_msgs__srv__SetDigitalOutput__FIELD_NAME__response_message[] = "response_message";
static char igus_rebel_msgs__srv__SetDigitalOutput__FIELD_NAME__event_message[] = "event_message";

static rosidl_runtime_c__type_description__Field igus_rebel_msgs__srv__SetDigitalOutput__FIELDS[] = {
  {
    {igus_rebel_msgs__srv__SetDigitalOutput__FIELD_NAME__request_message, 15, 15},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {igus_rebel_msgs__srv__SetDigitalOutput_Request__TYPE_NAME, 44, 44},
    },
    {NULL, 0, 0},
  },
  {
    {igus_rebel_msgs__srv__SetDigitalOutput__FIELD_NAME__response_message, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {igus_rebel_msgs__srv__SetDigitalOutput_Response__TYPE_NAME, 45, 45},
    },
    {NULL, 0, 0},
  },
  {
    {igus_rebel_msgs__srv__SetDigitalOutput__FIELD_NAME__event_message, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {igus_rebel_msgs__srv__SetDigitalOutput_Event__TYPE_NAME, 42, 42},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription igus_rebel_msgs__srv__SetDigitalOutput__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {igus_rebel_msgs__msg__DigitalOutput__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
  {
    {igus_rebel_msgs__srv__SetDigitalOutput_Event__TYPE_NAME, 42, 42},
    {NULL, 0, 0},
  },
  {
    {igus_rebel_msgs__srv__SetDigitalOutput_Request__TYPE_NAME, 44, 44},
    {NULL, 0, 0},
  },
  {
    {igus_rebel_msgs__srv__SetDigitalOutput_Response__TYPE_NAME, 45, 45},
    {NULL, 0, 0},
  },
  {
    {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
igus_rebel_msgs__srv__SetDigitalOutput__get_type_description(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {igus_rebel_msgs__srv__SetDigitalOutput__TYPE_NAME, 36, 36},
      {igus_rebel_msgs__srv__SetDigitalOutput__FIELDS, 3, 3},
    },
    {igus_rebel_msgs__srv__SetDigitalOutput__REFERENCED_TYPE_DESCRIPTIONS, 6, 6},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&igus_rebel_msgs__msg__DigitalOutput__EXPECTED_HASH, igus_rebel_msgs__msg__DigitalOutput__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = igus_rebel_msgs__msg__DigitalOutput__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[2].fields = igus_rebel_msgs__srv__SetDigitalOutput_Event__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[3].fields = igus_rebel_msgs__srv__SetDigitalOutput_Request__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[4].fields = igus_rebel_msgs__srv__SetDigitalOutput_Response__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&service_msgs__msg__ServiceEventInfo__EXPECTED_HASH, service_msgs__msg__ServiceEventInfo__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[5].fields = service_msgs__msg__ServiceEventInfo__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char igus_rebel_msgs__srv__SetDigitalOutput_Request__FIELD_NAME__output[] = "output";

static rosidl_runtime_c__type_description__Field igus_rebel_msgs__srv__SetDigitalOutput_Request__FIELDS[] = {
  {
    {igus_rebel_msgs__srv__SetDigitalOutput_Request__FIELD_NAME__output, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {igus_rebel_msgs__msg__DigitalOutput__TYPE_NAME, 33, 33},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription igus_rebel_msgs__srv__SetDigitalOutput_Request__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {igus_rebel_msgs__msg__DigitalOutput__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
igus_rebel_msgs__srv__SetDigitalOutput_Request__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {igus_rebel_msgs__srv__SetDigitalOutput_Request__TYPE_NAME, 44, 44},
      {igus_rebel_msgs__srv__SetDigitalOutput_Request__FIELDS, 1, 1},
    },
    {igus_rebel_msgs__srv__SetDigitalOutput_Request__REFERENCED_TYPE_DESCRIPTIONS, 1, 1},
  };
  if (!constructed) {
    assert(0 == memcmp(&igus_rebel_msgs__msg__DigitalOutput__EXPECTED_HASH, igus_rebel_msgs__msg__DigitalOutput__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = igus_rebel_msgs__msg__DigitalOutput__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char igus_rebel_msgs__srv__SetDigitalOutput_Response__FIELD_NAME__success[] = "success";
static char igus_rebel_msgs__srv__SetDigitalOutput_Response__FIELD_NAME__message[] = "message";

static rosidl_runtime_c__type_description__Field igus_rebel_msgs__srv__SetDigitalOutput_Response__FIELDS[] = {
  {
    {igus_rebel_msgs__srv__SetDigitalOutput_Response__FIELD_NAME__success, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {igus_rebel_msgs__srv__SetDigitalOutput_Response__FIELD_NAME__message, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
igus_rebel_msgs__srv__SetDigitalOutput_Response__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {igus_rebel_msgs__srv__SetDigitalOutput_Response__TYPE_NAME, 45, 45},
      {igus_rebel_msgs__srv__SetDigitalOutput_Response__FIELDS, 2, 2},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char igus_rebel_msgs__srv__SetDigitalOutput_Event__FIELD_NAME__info[] = "info";
static char igus_rebel_msgs__srv__SetDigitalOutput_Event__FIELD_NAME__request[] = "request";
static char igus_rebel_msgs__srv__SetDigitalOutput_Event__FIELD_NAME__response[] = "response";

static rosidl_runtime_c__type_description__Field igus_rebel_msgs__srv__SetDigitalOutput_Event__FIELDS[] = {
  {
    {igus_rebel_msgs__srv__SetDigitalOutput_Event__FIELD_NAME__info, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    },
    {NULL, 0, 0},
  },
  {
    {igus_rebel_msgs__srv__SetDigitalOutput_Event__FIELD_NAME__request, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE,
      1,
      0,
      {igus_rebel_msgs__srv__SetDigitalOutput_Request__TYPE_NAME, 44, 44},
    },
    {NULL, 0, 0},
  },
  {
    {igus_rebel_msgs__srv__SetDigitalOutput_Event__FIELD_NAME__response, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE,
      1,
      0,
      {igus_rebel_msgs__srv__SetDigitalOutput_Response__TYPE_NAME, 45, 45},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription igus_rebel_msgs__srv__SetDigitalOutput_Event__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {igus_rebel_msgs__msg__DigitalOutput__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
  {
    {igus_rebel_msgs__srv__SetDigitalOutput_Request__TYPE_NAME, 44, 44},
    {NULL, 0, 0},
  },
  {
    {igus_rebel_msgs__srv__SetDigitalOutput_Response__TYPE_NAME, 45, 45},
    {NULL, 0, 0},
  },
  {
    {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
igus_rebel_msgs__srv__SetDigitalOutput_Event__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {igus_rebel_msgs__srv__SetDigitalOutput_Event__TYPE_NAME, 42, 42},
      {igus_rebel_msgs__srv__SetDigitalOutput_Event__FIELDS, 3, 3},
    },
    {igus_rebel_msgs__srv__SetDigitalOutput_Event__REFERENCED_TYPE_DESCRIPTIONS, 5, 5},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&igus_rebel_msgs__msg__DigitalOutput__EXPECTED_HASH, igus_rebel_msgs__msg__DigitalOutput__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = igus_rebel_msgs__msg__DigitalOutput__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[2].fields = igus_rebel_msgs__srv__SetDigitalOutput_Request__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[3].fields = igus_rebel_msgs__srv__SetDigitalOutput_Response__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&service_msgs__msg__ServiceEventInfo__EXPECTED_HASH, service_msgs__msg__ServiceEventInfo__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[4].fields = service_msgs__msg__ServiceEventInfo__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "DigitalOutput output\n"
  "---\n"
  "bool success\n"
  "string message";

static char srv_encoding[] = "srv";
static char implicit_encoding[] = "implicit";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
igus_rebel_msgs__srv__SetDigitalOutput__get_individual_type_description_source(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {igus_rebel_msgs__srv__SetDigitalOutput__TYPE_NAME, 36, 36},
    {srv_encoding, 3, 3},
    {toplevel_type_raw_source, 52, 52},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
igus_rebel_msgs__srv__SetDigitalOutput_Request__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {igus_rebel_msgs__srv__SetDigitalOutput_Request__TYPE_NAME, 44, 44},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
igus_rebel_msgs__srv__SetDigitalOutput_Response__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {igus_rebel_msgs__srv__SetDigitalOutput_Response__TYPE_NAME, 45, 45},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
igus_rebel_msgs__srv__SetDigitalOutput_Event__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {igus_rebel_msgs__srv__SetDigitalOutput_Event__TYPE_NAME, 42, 42},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
igus_rebel_msgs__srv__SetDigitalOutput__get_type_description_sources(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[7];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 7, 7};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *igus_rebel_msgs__srv__SetDigitalOutput__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *igus_rebel_msgs__msg__DigitalOutput__get_individual_type_description_source(NULL);
    sources[3] = *igus_rebel_msgs__srv__SetDigitalOutput_Event__get_individual_type_description_source(NULL);
    sources[4] = *igus_rebel_msgs__srv__SetDigitalOutput_Request__get_individual_type_description_source(NULL);
    sources[5] = *igus_rebel_msgs__srv__SetDigitalOutput_Response__get_individual_type_description_source(NULL);
    sources[6] = *service_msgs__msg__ServiceEventInfo__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
igus_rebel_msgs__srv__SetDigitalOutput_Request__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[2];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 2, 2};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *igus_rebel_msgs__srv__SetDigitalOutput_Request__get_individual_type_description_source(NULL),
    sources[1] = *igus_rebel_msgs__msg__DigitalOutput__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
igus_rebel_msgs__srv__SetDigitalOutput_Response__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *igus_rebel_msgs__srv__SetDigitalOutput_Response__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
igus_rebel_msgs__srv__SetDigitalOutput_Event__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[6];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 6, 6};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *igus_rebel_msgs__srv__SetDigitalOutput_Event__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *igus_rebel_msgs__msg__DigitalOutput__get_individual_type_description_source(NULL);
    sources[3] = *igus_rebel_msgs__srv__SetDigitalOutput_Request__get_individual_type_description_source(NULL);
    sources[4] = *igus_rebel_msgs__srv__SetDigitalOutput_Response__get_individual_type_description_source(NULL);
    sources[5] = *service_msgs__msg__ServiceEventInfo__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
