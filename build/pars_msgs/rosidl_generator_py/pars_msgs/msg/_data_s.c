// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from pars_msgs:msg/Data.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "pars_msgs/msg/detail/data__struct.h"
#include "pars_msgs/msg/detail/data__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool pars_msgs__msg__data__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[25];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("pars_msgs.msg._data.Data", full_classname_dest, 24) == 0);
  }
  pars_msgs__msg__Data * ros_message = _ros_message;
  {  // takim_numarasi
    PyObject * field = PyObject_GetAttrString(_pymsg, "takim_numarasi");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->takim_numarasi = (int32_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // iha_enlem
    PyObject * field = PyObject_GetAttrString(_pymsg, "iha_enlem");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->iha_enlem = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // iha_boylam
    PyObject * field = PyObject_GetAttrString(_pymsg, "iha_boylam");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->iha_boylam = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // iha_irtifa
    PyObject * field = PyObject_GetAttrString(_pymsg, "iha_irtifa");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->iha_irtifa = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // iha_yonelme
    PyObject * field = PyObject_GetAttrString(_pymsg, "iha_yonelme");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->iha_yonelme = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // iha_hizi
    PyObject * field = PyObject_GetAttrString(_pymsg, "iha_hizi");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->iha_hizi = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * pars_msgs__msg__data__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of Data */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("pars_msgs.msg._data");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "Data");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  pars_msgs__msg__Data * ros_message = (pars_msgs__msg__Data *)raw_ros_message;
  {  // takim_numarasi
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->takim_numarasi);
    {
      int rc = PyObject_SetAttrString(_pymessage, "takim_numarasi", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // iha_enlem
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->iha_enlem);
    {
      int rc = PyObject_SetAttrString(_pymessage, "iha_enlem", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // iha_boylam
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->iha_boylam);
    {
      int rc = PyObject_SetAttrString(_pymessage, "iha_boylam", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // iha_irtifa
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->iha_irtifa);
    {
      int rc = PyObject_SetAttrString(_pymessage, "iha_irtifa", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // iha_yonelme
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->iha_yonelme);
    {
      int rc = PyObject_SetAttrString(_pymessage, "iha_yonelme", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // iha_hizi
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->iha_hizi);
    {
      int rc = PyObject_SetAttrString(_pymessage, "iha_hizi", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
