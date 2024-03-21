#include "ROS_communication.h"

void ROS_init()
{
    extern geometry_msgs__msg__Twist Twist;


    rcl_allocator_t allocator = rcl_get_default_allocator();

    extern rclc_support_t support;
    rclc_support_init(&support, 0, NULL, &allocator);

    extern rcl_node_t node;
    rclc_node_init_default(&node, "ros2esp_receive", "", &support);

    extern rcl_subscription_t sub;
    rclc_subscription_init_default(
        &sub,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Twist),
        "/cmd_vel");

    
    extern rcl_timer_t timer;
    rclc_timer_init_default(
        &timer,
        &support,
        RCL_MS_TO_NS(100),  
        timer_callback);
        
    extern rclc_executor_t executor;
    rclc_executor_init(&executor, &support.context, 2, &allocator);
    rclc_executor_add_subscription(&executor, &sub, &Twist, &cmd_vel_callback, ON_NEW_DATA);
    rclc_executor_add_timer(&executor, &timer);

    Twist.linear.x = 0;
    Twist.linear.y = 0;
    Twist.linear.z = 0;
    Twist.angular.x = 0;
    Twist.angular.y = 0;
    Twist.angular.z = 0;
}

void timer_callback(rcl_timer_t *timer, int64_t last_call_time)
{
    RCLC_UNUSED(last_call_time);
    // if (timer != NULL)
}

void cmd_vel_callback(const void *msgin)
{
    // const geometry_msgs__msg__Twist *msg = (const geometry_msgs__msg__Twist *) msgin;
    // printf("Message received: %f %f\n", msg->linear.x, msg->angular.z);
}
