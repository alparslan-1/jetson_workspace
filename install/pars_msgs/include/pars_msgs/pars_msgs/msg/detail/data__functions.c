// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from pars_msgs:msg/Data.idl
// generated code does not contain a copyright notice
#include "pars_msgs/msg/detail/data__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
pars_msgs__msg__Data__init(pars_msgs__msg__Data * msg)
{
  if (!msg) {
    return false;
  }
  // takim_numarasi
  // iha_enlem
  // iha_boylam
  // iha_irtifa
  // iha_yonelme
  // iha_hizi
  return true;
}

void
pars_msgs__msg__Data__fini(pars_msgs__msg__Data * msg)
{
  if (!msg) {
    return;
  }
  // takim_numarasi
  // iha_enlem
  // iha_boylam
  // iha_irtifa
  // iha_yonelme
  // iha_hizi
}

bool
pars_msgs__msg__Data__are_equal(const pars_msgs__msg__Data * lhs, const pars_msgs__msg__Data * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // takim_numarasi
  if (lhs->takim_numarasi != rhs->takim_numarasi) {
    return false;
  }
  // iha_enlem
  if (lhs->iha_enlem != rhs->iha_enlem) {
    return false;
  }
  // iha_boylam
  if (lhs->iha_boylam != rhs->iha_boylam) {
    return false;
  }
  // iha_irtifa
  if (lhs->iha_irtifa != rhs->iha_irtifa) {
    return false;
  }
  // iha_yonelme
  if (lhs->iha_yonelme != rhs->iha_yonelme) {
    return false;
  }
  // iha_hizi
  if (lhs->iha_hizi != rhs->iha_hizi) {
    return false;
  }
  return true;
}

bool
pars_msgs__msg__Data__copy(
  const pars_msgs__msg__Data * input,
  pars_msgs__msg__Data * output)
{
  if (!input || !output) {
    return false;
  }
  // takim_numarasi
  output->takim_numarasi = input->takim_numarasi;
  // iha_enlem
  output->iha_enlem = input->iha_enlem;
  // iha_boylam
  output->iha_boylam = input->iha_boylam;
  // iha_irtifa
  output->iha_irtifa = input->iha_irtifa;
  // iha_yonelme
  output->iha_yonelme = input->iha_yonelme;
  // iha_hizi
  output->iha_hizi = input->iha_hizi;
  return true;
}

pars_msgs__msg__Data *
pars_msgs__msg__Data__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  pars_msgs__msg__Data * msg = (pars_msgs__msg__Data *)allocator.allocate(sizeof(pars_msgs__msg__Data), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(pars_msgs__msg__Data));
  bool success = pars_msgs__msg__Data__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
pars_msgs__msg__Data__destroy(pars_msgs__msg__Data * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    pars_msgs__msg__Data__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
pars_msgs__msg__Data__Sequence__init(pars_msgs__msg__Data__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  pars_msgs__msg__Data * data = NULL;

  if (size) {
    data = (pars_msgs__msg__Data *)allocator.zero_allocate(size, sizeof(pars_msgs__msg__Data), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = pars_msgs__msg__Data__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        pars_msgs__msg__Data__fini(&data[i - 1]);
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
pars_msgs__msg__Data__Sequence__fini(pars_msgs__msg__Data__Sequence * array)
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
      pars_msgs__msg__Data__fini(&array->data[i]);
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

pars_msgs__msg__Data__Sequence *
pars_msgs__msg__Data__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  pars_msgs__msg__Data__Sequence * array = (pars_msgs__msg__Data__Sequence *)allocator.allocate(sizeof(pars_msgs__msg__Data__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = pars_msgs__msg__Data__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
pars_msgs__msg__Data__Sequence__destroy(pars_msgs__msg__Data__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    pars_msgs__msg__Data__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
pars_msgs__msg__Data__Sequence__are_equal(const pars_msgs__msg__Data__Sequence * lhs, const pars_msgs__msg__Data__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!pars_msgs__msg__Data__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
pars_msgs__msg__Data__Sequence__copy(
  const pars_msgs__msg__Data__Sequence * input,
  pars_msgs__msg__Data__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(pars_msgs__msg__Data);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    pars_msgs__msg__Data * data =
      (pars_msgs__msg__Data *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!pars_msgs__msg__Data__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          pars_msgs__msg__Data__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!pars_msgs__msg__Data__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
