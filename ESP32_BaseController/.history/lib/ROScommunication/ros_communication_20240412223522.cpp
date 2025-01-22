#include "ros_communication.h"
#include "Base_controller.h"

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
motion__msg__Twist Twist;

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
    // RCCHECK(rclc_executor_add_subscription(
    //     &executor,
    //     &sub,
    //     &Twist,
    //     &ROS_communication::vel_callback,
    //     ON_NEW_DATA));

    Serial.println("Executors Started");
}

void ROS_communication::subscriber_define()
{
    // RCCHECK(rclc_subscription_init_default(
    //     &sub,
    //     &node,
    //     ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Twist),
    //     "/cmd_vel"));
}

void ROS_communication::vel_callback(const void *msg_recv)
{
    // const geometry_msgs__msg__Twist *received_data = (const geometry_msgs__msg__Twist *)msg_recv;
    // float linear_vel = received_data->linear.x;
    // float steer_angle = received_data->angular.z;

    /* 馬達控制函式*/
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