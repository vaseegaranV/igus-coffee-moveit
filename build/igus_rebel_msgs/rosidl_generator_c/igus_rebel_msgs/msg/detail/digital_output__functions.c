// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from igus_rebel_msgs:msg/DigitalOutput.idl
// generated code does not contain a copyright notice
#include "igus_rebel_msgs/msg/detail/digital_output__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
igus_rebel_msgs__msg__DigitalOutput__init(igus_rebel_msgs__msg__DigitalOutput * msg)
{
  if (!msg) {
    return false;
  }
  // output
  // is_on
  return true;
}

void
igus_rebel_msgs__msg__DigitalOutput__fini(igus_rebel_msgs__msg__DigitalOutput * msg)
{
  if (!msg) {
    return;
  }
  // output
  // is_on
}

bool
igus_rebel_msgs__msg__DigitalOutput__are_equal(const igus_rebel_msgs__msg__DigitalOutput * lhs, const igus_rebel_msgs__msg__DigitalOutput * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // output
  if (lhs->output != rhs->output) {
    return false;
  }
  // is_on
  if (lhs->is_on != rhs->is_on) {
    return false;
  }
  return true;
}

bool
igus_rebel_msgs__msg__DigitalOutput__copy(
  const igus_rebel_msgs__msg__DigitalOutput * input,
  igus_rebel_msgs__msg__DigitalOutput * output)
{
  if (!input || !output) {
    return false;
  }
  // output
  output->output = input->output;
  // is_on
  output->is_on = input->is_on;
  return true;
}

igus_rebel_msgs__msg__DigitalOutput *
igus_rebel_msgs__msg__DigitalOutput__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  igus_rebel_msgs__msg__DigitalOutput * msg = (igus_rebel_msgs__msg__DigitalOutput *)allocator.allocate(sizeof(igus_rebel_msgs__msg__DigitalOutput), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(igus_rebel_msgs__msg__DigitalOutput));
  bool success = igus_rebel_msgs__msg__DigitalOutput__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
igus_rebel_msgs__msg__DigitalOutput__destroy(igus_rebel_msgs__msg__DigitalOutput * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    igus_rebel_msgs__msg__DigitalOutput__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
igus_rebel_msgs__msg__DigitalOutput__Sequence__init(igus_rebel_msgs__msg__DigitalOutput__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  igus_rebel_msgs__msg__DigitalOutput * data = NULL;

  if (size) {
    data = (igus_rebel_msgs__msg__DigitalOutput *)allocator.zero_allocate(size, sizeof(igus_rebel_msgs__msg__DigitalOutput), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = igus_rebel_msgs__msg__DigitalOutput__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        igus_rebel_msgs__msg__DigitalOutput__fini(&data[i - 1]);
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
igus_rebel_msgs__msg__DigitalOutput__Sequence__fini(igus_rebel_msgs__msg__DigitalOutput__Sequence * array)
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
      igus_rebel_msgs__msg__DigitalOutput__fini(&array->data[i]);
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

igus_rebel_msgs__msg__DigitalOutput__Sequence *
igus_rebel_msgs__msg__DigitalOutput__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  igus_rebel_msgs__msg__DigitalOutput__Sequence * array = (igus_rebel_msgs__msg__DigitalOutput__Sequence *)allocator.allocate(sizeof(igus_rebel_msgs__msg__DigitalOutput__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = igus_rebel_msgs__msg__DigitalOutput__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
igus_rebel_msgs__msg__DigitalOutput__Sequence__destroy(igus_rebel_msgs__msg__DigitalOutput__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    igus_rebel_msgs__msg__DigitalOutput__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
igus_rebel_msgs__msg__DigitalOutput__Sequence__are_equal(const igus_rebel_msgs__msg__DigitalOutput__Sequence * lhs, const igus_rebel_msgs__msg__DigitalOutput__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!igus_rebel_msgs__msg__DigitalOutput__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
igus_rebel_msgs__msg__DigitalOutput__Sequence__copy(
  const igus_rebel_msgs__msg__DigitalOutput__Sequence * input,
  igus_rebel_msgs__msg__DigitalOutput__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(igus_rebel_msgs__msg__DigitalOutput);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    igus_rebel_msgs__msg__DigitalOutput * data =
      (igus_rebel_msgs__msg__DigitalOutput *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!igus_rebel_msgs__msg__DigitalOutput__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          igus_rebel_msgs__msg__DigitalOutput__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!igus_rebel_msgs__msg__DigitalOutput__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
