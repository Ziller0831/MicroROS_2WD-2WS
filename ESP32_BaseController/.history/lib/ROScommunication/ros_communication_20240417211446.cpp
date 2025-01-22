#include "ros_communication.h"

#define RCCHECK(fn)                  \
    {                                \
        rcl_ret_t temp_rc = fn;      \
        if ((temp_rc != RCL_RET_OK)) \
        {                            \
            rclErrorLoop();          \
        }                            \
    }
#define RCSOFTCHECK(fn)              \
    {                                \
        rcl_ret_t temp_rc = fn;      \
        if ((temp_rc != RCL_RET_OK)) \
        {                            \
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

    RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));
    RCCHECK(rclc_node_init_default(&node, "Base_controller", "", &support));

    RCCHECK(rclc_timer_init_default(
        &control_timer,
        &support,
        RCL_MS_TO_NS(control_timeout),
        controlCallback));

}

void ROS_communication::executors_start()
{
    RCCHECK(rclc_executor_init(&executor, &support.context, 1, &allocator));
    RCCHECK(rclc_executor_add_subscription(
        &executor,
        &motion_subscriber,
        &motion_command,
        &motion_callback,
        ON_NEW_DATA));

    RCCHECK(rclc_executor_add_timer(&executor, &control_timer));

    syncTime();
    digitalWrite(LED_PIN, HIGH);

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

void ROS_communication::start_receiving_msgs()
{
    rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100));
    delay(100);
}

void motion_callback(const void *msg_recv)
{
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    prev_cmd_time = millis();
}

void controlCallback(rcl_timer_t *timer, int64_t last_call_time)
{
    RCLC_UNUSED(last_call_time);
    if (timer != NULL)
        moveBase();
}

void moveBase()
{
    Kinematics::CP req_convertPara = kinematics.inverseKinematics(
        motion_command
    );
}

void syncTime()
{

    unsigned long now = millis();
    RCCHECK(rmw_uros_sync_session(10));
    unsigned long long ros_time_ms = rmw_uros_epoch_millis();
    // ROS_agent和MCU的时间差
    time_offset = ros_time_ms - now;
}

void rclErrorLoop()
{
    while (1)
    {
        digitalWrite(LED_PIN, !digitalRead(LED_PIN));
        delay(150);
    }
}