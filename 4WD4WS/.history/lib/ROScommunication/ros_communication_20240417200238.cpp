#include "ros_communication.h"

#define RCCHECK(fn)                  \
    {                                \
        rcl_ret_t temp_rc = fn;      \
        if ((temp_rc != RCL_RET_OK)) \
        {                            \
            error_loop();            \
        }                            \
    }
#define RCSOFTCHECK(fn)              \
    {                                \
        rcl_ret_t temp_rc = fn;      \
        if ((temp_rc != RCL_RET_OK)) \
        {                            \
        }                            \
    }

rcl_subscription_t motion_subscriber;
customize_interface__msg__MotionCommand motion_command;

rclc_support_t support;
rclc_executor_t executor;

rcl_node_t node;
rcl_allocator_t allocator;
rcl_timer_t control_timer;

ROS_communication::ROS_communication() {}

void ROS_communication::initialize()
{
    Serial.begin(115200);
    Serial.println("ROS Communication node started");
    set_microros_serial_transports(Serial);

    allocator = rcl_get_default_allocator();

    RC  rclc_support_init(&support, 0, NULL, &allocator));
    RCCHECK(rclc_node_init_default(&node, "Base_controller", "", &support));

    RCCHECK(rclc_timer_init_default)
}

void ROS_communication::executors_start()
{
    RCCHECK(rclc_executor_init(&executor, &support.context, 1, &allocator));
    RCCHECK(rclc_executor_add_subscription(
        &executor,
        &motion_subscriber,
        &motion_command,
        &ROS_communication::vel_callback,
        ON_NEW_DATA));

    Serial.println("Executors Started");
}



void ROS_communication::subscriber_define()
{
    RCCHECK(rclc_subscription_init_default(
        &motion_subscriber,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(customize_interface, msg, MotionCommand),
        "/Motion_command"));
}

void ROS_communication::vel_callback(const void *msg_recv)
{
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    prev_cmd_time = millis();
}

void ROS_communication::start_receiving_msgs()
{
    rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100));
    delay(100);
}

void error_loop()
{
    while (1)
    {
        digitalWrite(LED_PIN, !digitalRead(LED_PIN));
        delay(100);
    }
}