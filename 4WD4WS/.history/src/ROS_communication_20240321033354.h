#include <Arduino.h>
#include <micro_ros_platformio.h>

#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <std_msgs/msg/int32.h>
#include <geometry_msgs/msg/twist.h>

geometry_msgs__msg__Twist Twist;

extern rcl_allocator_t allocator;
extern rclc_support_t support;
extern rcl_node_t node;
extern rcl_subscription_t sub;
extern rclc_executor_t executor;
extern rcl_timer_t timer;

// #define RCCHECK(fn)
// {
//     rcl_ret_t temp_rc = fn;                                                          \
//     if ((temp_rc != RCL_RET_OK))                                                     \
//     {                                                                                \
//         printf("Failed status on line %d: %d. Aborting.\n", __LINE__, (int)temp_rc); \
//         vTaskDelete(NULL);                                                           \
//     }                                                                                \
// }

// #define RCSOFTCHEC(fn)
// {                                                                                     
//     rcl_ret_t temp_rc =fn;                                                            
//     if ((temp_rc != RCL_RET_OK))
//     {
//         printf("Failed status on line %d: %d. Continuing.\n", __LINE__, (int)temp_rc);
//     } 
// }

void ROS_init();

void cmd_vel_callback(const void *msgin);

void timer_callback(rcl_timer_t *timer, int64_t last_call_time);
