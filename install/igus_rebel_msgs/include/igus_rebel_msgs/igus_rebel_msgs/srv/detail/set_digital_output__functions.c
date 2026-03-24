// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from igus_rebel_msgs:srv/SetDigitalOutput.idl
// generated code does not contain a copyright notice
#include "igus_rebel_msgs/srv/detail/set_digital_output__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `output`
#include "igus_rebel_msgs/msg/detail/digital_output__functions.h"

bool
igus_rebel_msgs__srv__SetDigitalOutput_Request__init(igus_rebel_msgs__srv__SetDigitalOutput_Request * msg)
{
  if (!msg) {
    return false;
  }
  // output
  if (!igus_rebel_msgs__msg__DigitalOutput__init(&msg->output)) {
    igus_rebel_msgs__srv__SetDigitalOutput_Request__fini(msg);
    return false;
  }
  return true;
}

void
igus_rebel_msgs__srv__SetDigitalOutput_Request__fini(igus_rebel_msgs__srv__SetDigitalOutput_Request * msg)
{
  if (!msg) {
    return;
  }
  // output
  igus_rebel_msgs__msg__DigitalOutput__fini(&msg->output);
}

bool
igus_rebel_msgs__srv__SetDigitalOutput_Request__are_equal(const igus_rebel_msgs__srv__SetDigitalOutput_Request * lhs, const igus_rebel_msgs__srv__SetDigitalOutput_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // output
  if (!igus_rebel_msgs__msg__DigitalOutput__are_equal(
      &(lhs->output), &(rhs->output)))
  {
    return false;
  }
  return true;
}

bool
igus_rebel_msgs__srv__SetDigitalOutput_Request__copy(
  const igus_rebel_msgs__srv__SetDigitalOutput_Request * input,
  igus_rebel_msgs__srv__SetDigitalOutput_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // output
  if (!igus_rebel_msgs__msg__DigitalOutput__copy(
      &(input->output), &(output->output)))
  {
    return false;
  }
  return true;
}

igus_rebel_msgs__srv__SetDigitalOutput_Request *
igus_rebel_msgs__srv__SetDigitalOutput_Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  igus_rebel_msgs__srv__SetDigitalOutput_Request * msg = (igus_rebel_msgs__srv__SetDigitalOutput_Request *)allocator.allocate(sizeof(igus_rebel_msgs__srv__SetDigitalOutput_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(igus_rebel_msgs__srv__SetDigitalOutput_Request));
  bool success = igus_rebel_msgs__srv__SetDigitalOutput_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
igus_rebel_msgs__srv__SetDigitalOutput_Request__destroy(igus_rebel_msgs__srv__SetDigitalOutput_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    igus_rebel_msgs__srv__SetDigitalOutput_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
igus_rebel_msgs__srv__SetDigitalOutput_Request__Sequence__init(igus_rebel_msgs__srv__SetDigitalOutput_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  igus_rebel_msgs__srv__SetDigitalOutput_Request * data = NULL;

  if (size) {
    data = (igus_rebel_msgs__srv__SetDigitalOutput_Request *)allocator.zero_allocate(size, sizeof(igus_rebel_msgs__srv__SetDigitalOutput_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = igus_rebel_msgs__srv__SetDigitalOutput_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        igus_rebel_msgs__srv__SetDigitalOutput_Request__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
igus_rebel_msgs__srv__SetDigitalOutput_Request__Sequence__fini(igus_rebel_msgs__srv__SetDigitalOutput_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      igus_rebel_msgs__srv__SetDigitalOutput_Request__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

igus_rebel_msgs__srv__SetDigitalOutput_Request__Sequence *
igus_rebel_msgs__srv__SetDigitalOutput_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  igus_rebel_msgs__srv__SetDigitalOutput_Request__Sequence * array = (igus_rebel_msgs__srv__SetDigitalOutput_Request__Sequence *)allocator.allocate(sizeof(igus_rebel_msgs__srv__SetDigitalOutput_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = igus_rebel_msgs__srv__SetDigitalOutput_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
igus_rebel_msgs__srv__SetDigitalOutput_Request__Sequence__destroy(igus_rebel_msgs__srv__SetDigitalOutput_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    igus_rebel_msgs__srv__SetDigitalOutput_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
igus_rebel_msgs__srv__SetDigitalOutput_Request__Sequence__are_equal(const igus_rebel_msgs__srv__SetDigitalOutput_Request__Sequence * lhs, const igus_rebel_msgs__srv__SetDigitalOutput_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!igus_rebel_msgs__srv__SetDigitalOutput_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
igus_rebel_msgs__srv__SetDigitalOutput_Request__Sequence__copy(
  const igus_rebel_msgs__srv__SetDigitalOutput_Request__Sequence * input,
  igus_rebel_msgs__srv__SetDigitalOutput_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(igus_rebel_msgs__srv__SetDigitalOutput_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    igus_rebel_msgs__srv__SetDigitalOutput_Request * data =
      (igus_rebel_msgs__srv__SetDigitalOutput_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!igus_rebel_msgs__srv__SetDigitalOutput_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          igus_rebel_msgs__srv__SetDigitalOutput_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!igus_rebel_msgs__srv__SetDigitalOutput_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `message`
#include "rosidl_runtime_c/string_functions.h"

bool
igus_rebel_msgs__srv__SetDigitalOutput_Response__init(igus_rebel_msgs__srv__SetDigitalOutput_Response * msg)
{
  if (!msg) {
    return false;
  }
  // success
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    igus_rebel_msgs__srv__SetDigitalOutput_Response__fini(msg);
    return false;
  }
  return true;
}

void
igus_rebel_msgs__srv__SetDigitalOutput_Response__fini(igus_rebel_msgs__srv__SetDigitalOutput_Response * msg)
{
  if (!msg) {
    return;
  }
  // success
  // message
  rosidl_runtime_c__String__fini(&msg->message);
}

bool
igus_rebel_msgs__srv__SetDigitalOutput_Response__are_equal(const igus_rebel_msgs__srv__SetDigitalOutput_Response * lhs, const igus_rebel_msgs__srv__SetDigitalOutput_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // success
  if (lhs->success != rhs->success) {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->message), &(rhs->message)))
  {
    return false;
  }
  return true;
}

bool
igus_rebel_msgs__srv__SetDigitalOutput_Response__copy(
  const igus_rebel_msgs__srv__SetDigitalOutput_Response * input,
  igus_rebel_msgs__srv__SetDigitalOutput_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  output->success = input->success;
  // message
  if (!rosidl_runtime_c__String__copy(
      &(input->message), &(output->message)))
  {
    return false;
  }
  return true;
}

igus_rebel_msgs__srv__SetDigitalOutput_Response *
igus_rebel_msgs__srv__SetDigitalOutput_Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  igus_rebel_msgs__srv__SetDigitalOutput_Response * msg = (igus_rebel_msgs__srv__SetDigitalOutput_Response *)allocator.allocate(sizeof(igus_rebel_msgs__srv__SetDigitalOutput_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(igus_rebel_msgs__srv__SetDigitalOutput_Response));
  bool success = igus_rebel_msgs__srv__SetDigitalOutput_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
igus_rebel_msgs__srv__SetDigitalOutput_Response__destroy(igus_rebel_msgs__srv__SetDigitalOutput_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    igus_rebel_msgs__srv__SetDigitalOutput_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
igus_rebel_msgs__srv__SetDigitalOutput_Response__Sequence__init(igus_rebel_msgs__srv__SetDigitalOutput_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  igus_rebel_msgs__srv__SetDigitalOutput_Response * data = NULL;

  if (size) {
    data = (igus_rebel_msgs__srv__SetDigitalOutput_Response *)allocator.zero_allocate(size, sizeof(igus_rebel_msgs__srv__SetDigitalOutput_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = igus_rebel_msgs__srv__SetDigitalOutput_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        igus_rebel_msgs__srv__SetDigitalOutput_Response__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
igus_rebel_msgs__srv__SetDigitalOutput_Response__Sequence__fini(igus_rebel_msgs__srv__SetDigitalOutput_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      igus_rebel_msgs__srv__SetDigitalOutput_Response__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

igus_rebel_msgs__srv__SetDigitalOutput_Response__Sequence *
igus_rebel_msgs__srv__SetDigitalOutput_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  igus_rebel_msgs__srv__SetDigitalOutput_Response__Sequence * array = (igus_rebel_msgs__srv__SetDigitalOutput_Response__Sequence *)allocator.allocate(sizeof(igus_rebel_msgs__srv__SetDigitalOutput_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = igus_rebel_msgs__srv__SetDigitalOutput_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
igus_rebel_msgs__srv__SetDigitalOutput_Response__Sequence__destroy(igus_rebel_msgs__srv__SetDigitalOutput_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    igus_rebel_msgs__srv__SetDigitalOutput_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
igus_rebel_msgs__srv__SetDigitalOutput_Response__Sequence__are_equal(const igus_rebel_msgs__srv__SetDigitalOutput_Response__Sequence * lhs, const igus_rebel_msgs__srv__SetDigitalOutput_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!igus_rebel_msgs__srv__SetDigitalOutput_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
igus_rebel_msgs__srv__SetDigitalOutput_Response__Sequence__copy(
  const igus_rebel_msgs__srv__SetDigitalOutput_Response__Sequence * input,
  igus_rebel_msgs__srv__SetDigitalOutput_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(igus_rebel_msgs__srv__SetDigitalOutput_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    igus_rebel_msgs__srv__SetDigitalOutput_Response * data =
      (igus_rebel_msgs__srv__SetDigitalOutput_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!igus_rebel_msgs__srv__SetDigitalOutput_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          igus_rebel_msgs__srv__SetDigitalOutput_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!igus_rebel_msgs__srv__SetDigitalOutput_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `info`
#include "service_msgs/msg/detail/service_event_info__functions.h"
// Member `request`
// Member `response`
// already included above
// #include "igus_rebel_msgs/srv/detail/set_digital_output__functions.h"

bool
igus_rebel_msgs__srv__SetDigitalOutput_Event__init(igus_rebel_msgs__srv__SetDigitalOutput_Event * msg)
{
  if (!msg) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__init(&msg->info)) {
    igus_rebel_msgs__srv__SetDigitalOutput_Event__fini(msg);
    return false;
  }
  // request
  if (!igus_rebel_msgs__srv__SetDigitalOutput_Request__Sequence__init(&msg->request, 0)) {
    igus_rebel_msgs__srv__SetDigitalOutput_Event__fini(msg);
    return false;
  }
  // response
  if (!igus_rebel_msgs__srv__SetDigitalOutput_Response__Sequence__init(&msg->response, 0)) {
    igus_rebel_msgs__srv__SetDigitalOutput_Event__fini(msg);
    return false;
  }
  return true;
}

void
igus_rebel_msgs__srv__SetDigitalOutput_Event__fini(igus_rebel_msgs__srv__SetDigitalOutput_Event * msg)
{
  if (!msg) {
    return;
  }
  // info
  service_msgs__msg__ServiceEventInfo__fini(&msg->info);
  // request
  igus_rebel_msgs__srv__SetDigitalOutput_Request__Sequence__fini(&msg->request);
  // response
  igus_rebel_msgs__srv__SetDigitalOutput_Response__Sequence__fini(&msg->response);
}

bool
igus_rebel_msgs__srv__SetDigitalOutput_Event__are_equal(const igus_rebel_msgs__srv__SetDigitalOutput_Event * lhs, const igus_rebel_msgs__srv__SetDigitalOutput_Event * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__are_equal(
      &(lhs->info), &(rhs->info)))
  {
    return false;
  }
  // request
  if (!igus_rebel_msgs__srv__SetDigitalOutput_Request__Sequence__are_equal(
      &(lhs->request), &(rhs->request)))
  {
    return false;
  }
  // response
  if (!igus_rebel_msgs__srv__SetDigitalOutput_Response__Sequence__are_equal(
      &(lhs->response), &(rhs->response)))
  {
    return false;
  }
  return true;
}

bool
igus_rebel_msgs__srv__SetDigitalOutput_Event__copy(
  const igus_rebel_msgs__srv__SetDigitalOutput_Event * input,
  igus_rebel_msgs__srv__SetDigitalOutput_Event * output)
{
  if (!input || !output) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__copy(
      &(input->info), &(output->info)))
  {
    return false;
  }
  // request
  if (!igus_rebel_msgs__srv__SetDigitalOutput_Request__Sequence__copy(
      &(input->request), &(output->request)))
  {
    return false;
  }
  // response
  if (!igus_rebel_msgs__srv__SetDigitalOutput_Response__Sequence__copy(
      &(input->response), &(output->response)))
  {
    return false;
  }
  return true;
}

igus_rebel_msgs__srv__SetDigitalOutput_Event *
igus_rebel_msgs__srv__SetDigitalOutput_Event__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  igus_rebel_msgs__srv__SetDigitalOutput_Event * msg = (igus_rebel_msgs__srv__SetDigitalOutput_Event *)allocator.allocate(sizeof(igus_rebel_msgs__srv__SetDigitalOutput_Event), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(igus_rebel_msgs__srv__SetDigitalOutput_Event));
  bool success = igus_rebel_msgs__srv__SetDigitalOutput_Event__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
igus_rebel_msgs__srv__SetDigitalOutput_Event__destroy(igus_rebel_msgs__srv__SetDigitalOutput_Event * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    igus_rebel_msgs__srv__SetDigitalOutput_Event__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
igus_rebel_msgs__srv__SetDigitalOutput_Event__Sequence__init(igus_rebel_msgs__srv__SetDigitalOutput_Event__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  igus_rebel_msgs__srv__SetDigitalOutput_Event * data = NULL;

  if (size) {
    data = (igus_rebel_msgs__srv__SetDigitalOutput_Event *)allocator.zero_allocate(size, sizeof(igus_rebel_msgs__srv__SetDigitalOutput_Event), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = igus_rebel_msgs__srv__SetDigitalOutput_Event__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        igus_rebel_msgs__srv__SetDigitalOutput_Event__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
igus_rebel_msgs__srv__SetDigitalOutput_Event__Sequence__fini(igus_rebel_msgs__srv__SetDigitalOutput_Event__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      igus_rebel_msgs__srv__SetDigitalOutput_Event__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

igus_rebel_msgs__srv__SetDigitalOutput_Event__Sequence *
igus_rebel_msgs__srv__SetDigitalOutput_Event__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  igus_rebel_msgs__srv__SetDigitalOutput_Event__Sequence * array = (igus_rebel_msgs__srv__SetDigitalOutput_Event__Sequence *)allocator.allocate(sizeof(igus_rebel_msgs__srv__SetDigitalOutput_Event__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = igus_rebel_msgs__srv__SetDigitalOutput_Event__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
igus_rebel_msgs__srv__SetDigitalOutput_Event__Sequence__destroy(igus_rebel_msgs__srv__SetDigitalOutput_Event__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    igus_rebel_msgs__srv__SetDigitalOutput_Event__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
igus_rebel_msgs__srv__SetDigitalOutput_Event__Sequence__are_equal(const igus_rebel_msgs__srv__SetDigitalOutput_Event__Sequence * lhs, const igus_rebel_msgs__srv__SetDigitalOutput_Event__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!igus_rebel_msgs__srv__SetDigitalOutput_Event__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
igus_rebel_msgs__srv__SetDigitalOutput_Event__Sequence__copy(
  const igus_rebel_msgs__srv__SetDigitalOutput_Event__Sequence * input,
  igus_rebel_msgs__srv__SetDigitalOutput_Event__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(igus_rebel_msgs__srv__SetDigitalOutput_Event);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    igus_rebel_msgs__srv__SetDigitalOutput_Event * data =
      (igus_rebel_msgs__srv__SetDigitalOutput_Event *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!igus_rebel_msgs__srv__SetDigitalOutput_Event__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          igus_rebel_msgs__srv__SetDigitalOutput_Event__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!igus_rebel_msgs__srv__SetDigitalOutput_Event__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
