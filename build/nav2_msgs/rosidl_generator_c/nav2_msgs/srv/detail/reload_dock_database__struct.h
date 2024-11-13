// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from nav2_msgs:srv/ReloadDockDatabase.idl
// generated code does not contain a copyright notice

#ifndef NAV2_MSGS__SRV__DETAIL__RELOAD_DOCK_DATABASE__STRUCT_H_
#define NAV2_MSGS__SRV__DETAIL__RELOAD_DOCK_DATABASE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'filepath'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/ReloadDockDatabase in the package nav2_msgs.
typedef struct nav2_msgs__srv__ReloadDockDatabase_Request
{
  rosidl_runtime_c__String filepath;
} nav2_msgs__srv__ReloadDockDatabase_Request;

// Struct for a sequence of nav2_msgs__srv__ReloadDockDatabase_Request.
typedef struct nav2_msgs__srv__ReloadDockDatabase_Request__Sequence
{
  nav2_msgs__srv__ReloadDockDatabase_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} nav2_msgs__srv__ReloadDockDatabase_Request__Sequence;


// Constants defined in the message

/// Struct defined in srv/ReloadDockDatabase in the package nav2_msgs.
typedef struct nav2_msgs__srv__ReloadDockDatabase_Response
{
  bool success;
} nav2_msgs__srv__ReloadDockDatabase_Response;

// Struct for a sequence of nav2_msgs__srv__ReloadDockDatabase_Response.
typedef struct nav2_msgs__srv__ReloadDockDatabase_Response__Sequence
{
  nav2_msgs__srv__ReloadDockDatabase_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} nav2_msgs__srv__ReloadDockDatabase_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // NAV2_MSGS__SRV__DETAIL__RELOAD_DOCK_DATABASE__STRUCT_H_
