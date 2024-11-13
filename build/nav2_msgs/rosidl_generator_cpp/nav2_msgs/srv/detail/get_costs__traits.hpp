// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from nav2_msgs:srv/GetCosts.idl
// generated code does not contain a copyright notice

#ifndef NAV2_MSGS__SRV__DETAIL__GET_COSTS__TRAITS_HPP_
#define NAV2_MSGS__SRV__DETAIL__GET_COSTS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "nav2_msgs/srv/detail/get_costs__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'poses'
#include "geometry_msgs/msg/detail/pose_stamped__traits.hpp"

namespace nav2_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetCosts_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: use_footprint
  {
    out << "use_footprint: ";
    rosidl_generator_traits::value_to_yaml(msg.use_footprint, out);
    out << ", ";
  }

  // member: poses
  {
    if (msg.poses.size() == 0) {
      out << "poses: []";
    } else {
      out << "poses: [";
      size_t pending_items = msg.poses.size();
      for (auto item : msg.poses) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetCosts_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: use_footprint
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "use_footprint: ";
    rosidl_generator_traits::value_to_yaml(msg.use_footprint, out);
    out << "\n";
  }

  // member: poses
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.poses.size() == 0) {
      out << "poses: []\n";
    } else {
      out << "poses:\n";
      for (auto item : msg.poses) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetCosts_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace nav2_msgs

namespace rosidl_generator_traits
{

[[deprecated("use nav2_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const nav2_msgs::srv::GetCosts_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  nav2_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use nav2_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const nav2_msgs::srv::GetCosts_Request & msg)
{
  return nav2_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<nav2_msgs::srv::GetCosts_Request>()
{
  return "nav2_msgs::srv::GetCosts_Request";
}

template<>
inline const char * name<nav2_msgs::srv::GetCosts_Request>()
{
  return "nav2_msgs/srv/GetCosts_Request";
}

template<>
struct has_fixed_size<nav2_msgs::srv::GetCosts_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<nav2_msgs::srv::GetCosts_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<nav2_msgs::srv::GetCosts_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace nav2_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetCosts_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: costs
  {
    if (msg.costs.size() == 0) {
      out << "costs: []";
    } else {
      out << "costs: [";
      size_t pending_items = msg.costs.size();
      for (auto item : msg.costs) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetCosts_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: costs
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.costs.size() == 0) {
      out << "costs: []\n";
    } else {
      out << "costs:\n";
      for (auto item : msg.costs) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetCosts_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace nav2_msgs

namespace rosidl_generator_traits
{

[[deprecated("use nav2_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const nav2_msgs::srv::GetCosts_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  nav2_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use nav2_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const nav2_msgs::srv::GetCosts_Response & msg)
{
  return nav2_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<nav2_msgs::srv::GetCosts_Response>()
{
  return "nav2_msgs::srv::GetCosts_Response";
}

template<>
inline const char * name<nav2_msgs::srv::GetCosts_Response>()
{
  return "nav2_msgs/srv/GetCosts_Response";
}

template<>
struct has_fixed_size<nav2_msgs::srv::GetCosts_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<nav2_msgs::srv::GetCosts_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<nav2_msgs::srv::GetCosts_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<nav2_msgs::srv::GetCosts>()
{
  return "nav2_msgs::srv::GetCosts";
}

template<>
inline const char * name<nav2_msgs::srv::GetCosts>()
{
  return "nav2_msgs/srv/GetCosts";
}

template<>
struct has_fixed_size<nav2_msgs::srv::GetCosts>
  : std::integral_constant<
    bool,
    has_fixed_size<nav2_msgs::srv::GetCosts_Request>::value &&
    has_fixed_size<nav2_msgs::srv::GetCosts_Response>::value
  >
{
};

template<>
struct has_bounded_size<nav2_msgs::srv::GetCosts>
  : std::integral_constant<
    bool,
    has_bounded_size<nav2_msgs::srv::GetCosts_Request>::value &&
    has_bounded_size<nav2_msgs::srv::GetCosts_Response>::value
  >
{
};

template<>
struct is_service<nav2_msgs::srv::GetCosts>
  : std::true_type
{
};

template<>
struct is_service_request<nav2_msgs::srv::GetCosts_Request>
  : std::true_type
{
};

template<>
struct is_service_response<nav2_msgs::srv::GetCosts_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // NAV2_MSGS__SRV__DETAIL__GET_COSTS__TRAITS_HPP_
