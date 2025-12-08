// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from pkg_srv:srv/MissionControl.idl
// generated code does not contain a copyright notice
#include "pkg_srv/srv/detail/mission_control__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `state`
#include "rosidl_runtime_c/string_functions.h"

bool
pkg_srv__srv__MissionControl_Request__init(pkg_srv__srv__MissionControl_Request * msg)
{
  if (!msg) {
    return false;
  }
  // state
  if (!rosidl_runtime_c__String__init(&msg->state)) {
    pkg_srv__srv__MissionControl_Request__fini(msg);
    return false;
  }
  return true;
}

void
pkg_srv__srv__MissionControl_Request__fini(pkg_srv__srv__MissionControl_Request * msg)
{
  if (!msg) {
    return;
  }
  // state
  rosidl_runtime_c__String__fini(&msg->state);
}

bool
pkg_srv__srv__MissionControl_Request__are_equal(const pkg_srv__srv__MissionControl_Request * lhs, const pkg_srv__srv__MissionControl_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // state
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->state), &(rhs->state)))
  {
    return false;
  }
  return true;
}

bool
pkg_srv__srv__MissionControl_Request__copy(
  const pkg_srv__srv__MissionControl_Request * input,
  pkg_srv__srv__MissionControl_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // state
  if (!rosidl_runtime_c__String__copy(
      &(input->state), &(output->state)))
  {
    return false;
  }
  return true;
}

pkg_srv__srv__MissionControl_Request *
pkg_srv__srv__MissionControl_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  pkg_srv__srv__MissionControl_Request * msg = (pkg_srv__srv__MissionControl_Request *)allocator.allocate(sizeof(pkg_srv__srv__MissionControl_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(pkg_srv__srv__MissionControl_Request));
  bool success = pkg_srv__srv__MissionControl_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
pkg_srv__srv__MissionControl_Request__destroy(pkg_srv__srv__MissionControl_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    pkg_srv__srv__MissionControl_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
pkg_srv__srv__MissionControl_Request__Sequence__init(pkg_srv__srv__MissionControl_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  pkg_srv__srv__MissionControl_Request * data = NULL;

  if (size) {
    data = (pkg_srv__srv__MissionControl_Request *)allocator.zero_allocate(size, sizeof(pkg_srv__srv__MissionControl_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = pkg_srv__srv__MissionControl_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        pkg_srv__srv__MissionControl_Request__fini(&data[i - 1]);
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
pkg_srv__srv__MissionControl_Request__Sequence__fini(pkg_srv__srv__MissionControl_Request__Sequence * array)
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
      pkg_srv__srv__MissionControl_Request__fini(&array->data[i]);
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

pkg_srv__srv__MissionControl_Request__Sequence *
pkg_srv__srv__MissionControl_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  pkg_srv__srv__MissionControl_Request__Sequence * array = (pkg_srv__srv__MissionControl_Request__Sequence *)allocator.allocate(sizeof(pkg_srv__srv__MissionControl_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = pkg_srv__srv__MissionControl_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
pkg_srv__srv__MissionControl_Request__Sequence__destroy(pkg_srv__srv__MissionControl_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    pkg_srv__srv__MissionControl_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
pkg_srv__srv__MissionControl_Request__Sequence__are_equal(const pkg_srv__srv__MissionControl_Request__Sequence * lhs, const pkg_srv__srv__MissionControl_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!pkg_srv__srv__MissionControl_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
pkg_srv__srv__MissionControl_Request__Sequence__copy(
  const pkg_srv__srv__MissionControl_Request__Sequence * input,
  pkg_srv__srv__MissionControl_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(pkg_srv__srv__MissionControl_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    pkg_srv__srv__MissionControl_Request * data =
      (pkg_srv__srv__MissionControl_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!pkg_srv__srv__MissionControl_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          pkg_srv__srv__MissionControl_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!pkg_srv__srv__MissionControl_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `mission_state`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

bool
pkg_srv__srv__MissionControl_Response__init(pkg_srv__srv__MissionControl_Response * msg)
{
  if (!msg) {
    return false;
  }
  // mission_state
  if (!rosidl_runtime_c__String__init(&msg->mission_state)) {
    pkg_srv__srv__MissionControl_Response__fini(msg);
    return false;
  }
  return true;
}

void
pkg_srv__srv__MissionControl_Response__fini(pkg_srv__srv__MissionControl_Response * msg)
{
  if (!msg) {
    return;
  }
  // mission_state
  rosidl_runtime_c__String__fini(&msg->mission_state);
}

bool
pkg_srv__srv__MissionControl_Response__are_equal(const pkg_srv__srv__MissionControl_Response * lhs, const pkg_srv__srv__MissionControl_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // mission_state
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->mission_state), &(rhs->mission_state)))
  {
    return false;
  }
  return true;
}

bool
pkg_srv__srv__MissionControl_Response__copy(
  const pkg_srv__srv__MissionControl_Response * input,
  pkg_srv__srv__MissionControl_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // mission_state
  if (!rosidl_runtime_c__String__copy(
      &(input->mission_state), &(output->mission_state)))
  {
    return false;
  }
  return true;
}

pkg_srv__srv__MissionControl_Response *
pkg_srv__srv__MissionControl_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  pkg_srv__srv__MissionControl_Response * msg = (pkg_srv__srv__MissionControl_Response *)allocator.allocate(sizeof(pkg_srv__srv__MissionControl_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(pkg_srv__srv__MissionControl_Response));
  bool success = pkg_srv__srv__MissionControl_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
pkg_srv__srv__MissionControl_Response__destroy(pkg_srv__srv__MissionControl_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    pkg_srv__srv__MissionControl_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
pkg_srv__srv__MissionControl_Response__Sequence__init(pkg_srv__srv__MissionControl_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  pkg_srv__srv__MissionControl_Response * data = NULL;

  if (size) {
    data = (pkg_srv__srv__MissionControl_Response *)allocator.zero_allocate(size, sizeof(pkg_srv__srv__MissionControl_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = pkg_srv__srv__MissionControl_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        pkg_srv__srv__MissionControl_Response__fini(&data[i - 1]);
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
pkg_srv__srv__MissionControl_Response__Sequence__fini(pkg_srv__srv__MissionControl_Response__Sequence * array)
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
      pkg_srv__srv__MissionControl_Response__fini(&array->data[i]);
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

pkg_srv__srv__MissionControl_Response__Sequence *
pkg_srv__srv__MissionControl_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  pkg_srv__srv__MissionControl_Response__Sequence * array = (pkg_srv__srv__MissionControl_Response__Sequence *)allocator.allocate(sizeof(pkg_srv__srv__MissionControl_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = pkg_srv__srv__MissionControl_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
pkg_srv__srv__MissionControl_Response__Sequence__destroy(pkg_srv__srv__MissionControl_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    pkg_srv__srv__MissionControl_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
pkg_srv__srv__MissionControl_Response__Sequence__are_equal(const pkg_srv__srv__MissionControl_Response__Sequence * lhs, const pkg_srv__srv__MissionControl_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!pkg_srv__srv__MissionControl_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
pkg_srv__srv__MissionControl_Response__Sequence__copy(
  const pkg_srv__srv__MissionControl_Response__Sequence * input,
  pkg_srv__srv__MissionControl_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(pkg_srv__srv__MissionControl_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    pkg_srv__srv__MissionControl_Response * data =
      (pkg_srv__srv__MissionControl_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!pkg_srv__srv__MissionControl_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          pkg_srv__srv__MissionControl_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!pkg_srv__srv__MissionControl_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
