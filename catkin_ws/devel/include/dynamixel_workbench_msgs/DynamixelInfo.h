// Generated by gencpp from file dynamixel_workbench_msgs/DynamixelInfo.msg
// DO NOT EDIT!


#ifndef DYNAMIXEL_WORKBENCH_MSGS_MESSAGE_DYNAMIXELINFO_H
#define DYNAMIXEL_WORKBENCH_MSGS_MESSAGE_DYNAMIXELINFO_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <dynamixel_workbench_msgs/DynamixelLoadInfo.h>

namespace dynamixel_workbench_msgs
{
template <class ContainerAllocator>
struct DynamixelInfo_
{
  typedef DynamixelInfo_<ContainerAllocator> Type;

  DynamixelInfo_()
    : load_info()
    , model_name()
    , model_number(0)
    , model_id(0)  {
    }
  DynamixelInfo_(const ContainerAllocator& _alloc)
    : load_info(_alloc)
    , model_name(_alloc)
    , model_number(0)
    , model_id(0)  {
  (void)_alloc;
    }



   typedef  ::dynamixel_workbench_msgs::DynamixelLoadInfo_<ContainerAllocator>  _load_info_type;
  _load_info_type load_info;

   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _model_name_type;
  _model_name_type model_name;

   typedef uint16_t _model_number_type;
  _model_number_type model_number;

   typedef uint8_t _model_id_type;
  _model_id_type model_id;





  typedef boost::shared_ptr< ::dynamixel_workbench_msgs::DynamixelInfo_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::dynamixel_workbench_msgs::DynamixelInfo_<ContainerAllocator> const> ConstPtr;

}; // struct DynamixelInfo_

typedef ::dynamixel_workbench_msgs::DynamixelInfo_<std::allocator<void> > DynamixelInfo;

typedef boost::shared_ptr< ::dynamixel_workbench_msgs::DynamixelInfo > DynamixelInfoPtr;
typedef boost::shared_ptr< ::dynamixel_workbench_msgs::DynamixelInfo const> DynamixelInfoConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::dynamixel_workbench_msgs::DynamixelInfo_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::dynamixel_workbench_msgs::DynamixelInfo_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace dynamixel_workbench_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/melodic/share/std_msgs/cmake/../msg'], 'dynamixel_workbench_msgs': ['/home/samuel/Desktop/MARV2/catkin_ws/src/dynamixel_workbench_msgs/dynamixel_workbench_msgs/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::dynamixel_workbench_msgs::DynamixelInfo_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::dynamixel_workbench_msgs::DynamixelInfo_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::dynamixel_workbench_msgs::DynamixelInfo_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::dynamixel_workbench_msgs::DynamixelInfo_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::dynamixel_workbench_msgs::DynamixelInfo_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::dynamixel_workbench_msgs::DynamixelInfo_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::dynamixel_workbench_msgs::DynamixelInfo_<ContainerAllocator> >
{
  static const char* value()
  {
    return "8c02a7626d88db402a8af7bc5e0880d4";
  }

  static const char* value(const ::dynamixel_workbench_msgs::DynamixelInfo_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x8c02a7626d88db40ULL;
  static const uint64_t static_value2 = 0x2a8af7bc5e0880d4ULL;
};

template<class ContainerAllocator>
struct DataType< ::dynamixel_workbench_msgs::DynamixelInfo_<ContainerAllocator> >
{
  static const char* value()
  {
    return "dynamixel_workbench_msgs/DynamixelInfo";
  }

  static const char* value(const ::dynamixel_workbench_msgs::DynamixelInfo_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::dynamixel_workbench_msgs::DynamixelInfo_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# This message includes information of dynamixel's basic parameter\n"
"\n"
"DynamixelLoadInfo load_info\n"
"\n"
"string model_name\n"
"uint16 model_number\n"
"uint8 model_id\n"
"\n"
"\n"
"================================================================================\n"
"MSG: dynamixel_workbench_msgs/DynamixelLoadInfo\n"
"# This message includes dynamixel's load information\n"
"\n"
"string device_name\n"
"uint64 baud_rate\n"
"float32 protocol_version\n"
;
  }

  static const char* value(const ::dynamixel_workbench_msgs::DynamixelInfo_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::dynamixel_workbench_msgs::DynamixelInfo_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.load_info);
      stream.next(m.model_name);
      stream.next(m.model_number);
      stream.next(m.model_id);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct DynamixelInfo_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::dynamixel_workbench_msgs::DynamixelInfo_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::dynamixel_workbench_msgs::DynamixelInfo_<ContainerAllocator>& v)
  {
    s << indent << "load_info: ";
    s << std::endl;
    Printer< ::dynamixel_workbench_msgs::DynamixelLoadInfo_<ContainerAllocator> >::stream(s, indent + "  ", v.load_info);
    s << indent << "model_name: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.model_name);
    s << indent << "model_number: ";
    Printer<uint16_t>::stream(s, indent + "  ", v.model_number);
    s << indent << "model_id: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.model_id);
  }
};

} // namespace message_operations
} // namespace ros

#endif // DYNAMIXEL_WORKBENCH_MSGS_MESSAGE_DYNAMIXELINFO_H
