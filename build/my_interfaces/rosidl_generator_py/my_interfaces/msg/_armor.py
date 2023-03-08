# generated from rosidl_generator_py/resource/_idl.py.em
# with input from my_interfaces:msg/Armor.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_Armor(type):
    """Metaclass of message 'Armor'."""

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
            module = import_type_support('my_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'my_interfaces.msg.Armor')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__armor
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__armor
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__armor
            cls._TYPE_SUPPORT = module.type_support_msg__msg__armor
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__armor

            from geometry_msgs.msg import Point
            if Point.__class__._TYPE_SUPPORT is None:
                Point.__class__.__import_type_support__()

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Armor(metaclass=Metaclass_Armor):
    """Message class 'Armor'."""

    __slots__ = [
        '_header',
        '_time_stamp',
        '_id',
        '_cam_point',
        '_robot_pitch',
        '_robot_yaw',
        '_bullet_speed',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'time_stamp': 'double',
        'id': 'int8',
        'cam_point': 'geometry_msgs/Point',
        'robot_pitch': 'float',
        'robot_yaw': 'float',
        'bullet_speed': 'float',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('int8'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Point'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.time_stamp = kwargs.get('time_stamp', float())
        self.id = kwargs.get('id', int())
        from geometry_msgs.msg import Point
        self.cam_point = kwargs.get('cam_point', Point())
        self.robot_pitch = kwargs.get('robot_pitch', float())
        self.robot_yaw = kwargs.get('robot_yaw', float())
        self.bullet_speed = kwargs.get('bullet_speed', float())

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
        if self.header != other.header:
            return False
        if self.time_stamp != other.time_stamp:
            return False
        if self.id != other.id:
            return False
        if self.cam_point != other.cam_point:
            return False
        if self.robot_pitch != other.robot_pitch:
            return False
        if self.robot_yaw != other.robot_yaw:
            return False
        if self.bullet_speed != other.bullet_speed:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def header(self):
        """Message field 'header'."""
        return self._header

    @header.setter
    def header(self, value):
        if __debug__:
            from std_msgs.msg import Header
            assert \
                isinstance(value, Header), \
                "The 'header' field must be a sub message of type 'Header'"
        self._header = value

    @builtins.property
    def time_stamp(self):
        """Message field 'time_stamp'."""
        return self._time_stamp

    @time_stamp.setter
    def time_stamp(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'time_stamp' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'time_stamp' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._time_stamp = value

    @builtins.property  # noqa: A003
    def id(self):  # noqa: A003
        """Message field 'id'."""
        return self._id

    @id.setter  # noqa: A003
    def id(self, value):  # noqa: A003
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'id' field must be of type 'int'"
            assert value >= -128 and value < 128, \
                "The 'id' field must be an integer in [-128, 127]"
        self._id = value

    @builtins.property
    def cam_point(self):
        """Message field 'cam_point'."""
        return self._cam_point

    @cam_point.setter
    def cam_point(self, value):
        if __debug__:
            from geometry_msgs.msg import Point
            assert \
                isinstance(value, Point), \
                "The 'cam_point' field must be a sub message of type 'Point'"
        self._cam_point = value

    @builtins.property
    def robot_pitch(self):
        """Message field 'robot_pitch'."""
        return self._robot_pitch

    @robot_pitch.setter
    def robot_pitch(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'robot_pitch' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'robot_pitch' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._robot_pitch = value

    @builtins.property
    def robot_yaw(self):
        """Message field 'robot_yaw'."""
        return self._robot_yaw

    @robot_yaw.setter
    def robot_yaw(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'robot_yaw' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'robot_yaw' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._robot_yaw = value

    @builtins.property
    def bullet_speed(self):
        """Message field 'bullet_speed'."""
        return self._bullet_speed

    @bullet_speed.setter
    def bullet_speed(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'bullet_speed' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'bullet_speed' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._bullet_speed = value
