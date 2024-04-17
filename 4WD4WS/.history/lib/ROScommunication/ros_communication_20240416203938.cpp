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

rcl_subscription_t sub;
customize_interface__msg__MotionCommand motion_command;

rcl_allocator_t allocator;
rclc_support_t support;
rcl_node_t node;
rclc_executor_t executor;

ROS_communication::ROS_communication() {}

void ROS_communication::initialize()
{
    Serial.begin(115200);
    Serial.println("ROS Communication node started");
    set_microros_serial_transports(Serial);

    allocator = rcl_get_default_allocator();

    rclc_support_init(&support, 0, NULL, &allocator);
    rclc_node_init_default(&node, "Base_controller", "", &support);
}

void ROS_communication::executors_start()
{
    RCCHECK(rclc_executor_init(&executor, &support.context, 1, &allocator));
    RCCHECK(rclc_executor_add_subscription(
        &executor,
        &sub,
        &motion_command,
        &ROS_communication::vel_callback,
        ON_NEW_DATA));

    Serial.println("Executors Started");
}

void ROS_communication::subscriber_define()
{
    RCCHECK(rclc_subscription_init_default(
        &sub,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(customize_interface, msg, MotionCommand),
        "/Motion_command"));
}

void ROS_communication::vel_callback(const void *msg_recv)
{
    const customize_interface__msg__MotionCommand *received_data = (const customize_interface__msg__MotionCommand *)msg_recv;
    kinematics.MCommand mCommand;

    float linear_vel = received_data->linear_x;
    float center_rotation_rad = received_data-> center_rotation_rad;
    float turning_distance = received_data-> turning_distance;

    kinematics.inverseKinematics(received_data);
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