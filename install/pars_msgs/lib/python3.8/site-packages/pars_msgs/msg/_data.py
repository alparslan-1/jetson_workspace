# generated from rosidl_generator_py/resource/_idl.py.em
# with input from pars_msgs:msg/Data.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_Data(type):
    """Metaclass of message 'Data'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('pars_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'pars_msgs.msg.Data')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__data
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__data
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__data
            cls._TYPE_SUPPORT = module.type_support_msg__msg__data
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__data

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Data(metaclass=Metaclass_Data):
    """Message class 'Data'."""

    __slots__ = [
        '_takim_numarasi',
        '_iha_enlem',
        '_iha_boylam',
        '_iha_irtifa',
        '_iha_yonelme',
        '_iha_hizi',
    ]

    _fields_and_field_types = {
        'takim_numarasi': 'int32',
        'iha_enlem': 'double',
        'iha_boylam': 'double',
        'iha_irtifa': 'double',
        'iha_yonelme': 'double',
        'iha_hizi': 'double',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.takim_numarasi = kwargs.get('takim_numarasi', int())
        self.iha_enlem = kwargs.get('iha_enlem', float())
        self.iha_boylam = kwargs.get('iha_boylam', float())
        self.iha_irtifa = kwargs.get('iha_irtifa', float())
        self.iha_yonelme = kwargs.get('iha_yonelme', float())
        self.iha_hizi = kwargs.get('iha_hizi', float())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.takim_numarasi != other.takim_numarasi:
            return False
        if self.iha_enlem != other.iha_enlem:
            return False
        if self.iha_boylam != other.iha_boylam:
            return False
        if self.iha_irtifa != other.iha_irtifa:
            return False
        if self.iha_yonelme != other.iha_yonelme:
            return False
        if self.iha_hizi != other.iha_hizi:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def takim_numarasi(self):
        """Message field 'takim_numarasi'."""
        return self._takim_numarasi

    @takim_numarasi.setter
    def takim_numarasi(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'takim_numarasi' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'takim_numarasi' field must be an integer in [-2147483648, 2147483647]"
        self._takim_numarasi = value

    @builtins.property
    def iha_enlem(self):
        """Message field 'iha_enlem'."""
        return self._iha_enlem

    @iha_enlem.setter
    def iha_enlem(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'iha_enlem' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'iha_enlem' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._iha_enlem = value

    @builtins.property
    def iha_boylam(self):
        """Message field 'iha_boylam'."""
        return self._iha_boylam

    @iha_boylam.setter
    def iha_boylam(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'iha_boylam' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'iha_boylam' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._iha_boylam = value

    @builtins.property
    def iha_irtifa(self):
        """Message field 'iha_irtifa'."""
        return self._iha_irtifa

    @iha_irtifa.setter
    def iha_irtifa(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'iha_irtifa' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'iha_irtifa' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._iha_irtifa = value

    @builtins.property
    def iha_yonelme(self):
        """Message field 'iha_yonelme'."""
        return self._iha_yonelme

    @iha_yonelme.setter
    def iha_yonelme(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'iha_yonelme' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'iha_yonelme' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._iha_yonelme = value

    @builtins.property
    def iha_hizi(self):
        """Message field 'iha_hizi'."""
        return self._iha_hizi

    @iha_hizi.setter
    def iha_hizi(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'iha_hizi' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'iha_hizi' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._iha_hizi = value
