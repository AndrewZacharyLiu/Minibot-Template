#include "chassis_task.h"

#include "robot.h"
#include "remote.h"

extern Robot_State_t g_robot_state;
extern Remote_t g_remote;

float chassis_rad;

// M2006 motors
// Omnidrive 

void Chassis_Task_Init()
{
    // Init chassis hardware
        
    Motor_Config_t chassis_w1 = {   // added(mr)
        .can_bus = 1, // what can bus the motor is on
        .speed_controller_id = 1, // identifier for each motor
        .offset = 0, // Initial offset of the motor (used for encoder)
        .control_mode = VELOCITY_CONTROL, // Control mode of the motor (setting velocity or setting position/angle)
        .motor_reversal = MOTOR_REVERSAL_NORMAL, // Direction of the motor
        .velocity_pid = // pid
            {
                .kp = 500.0f,
                .kd = 0.0f,
                .kf = 0.0f,
                .output_limit = M2006_MAX_CURRENT, // m2006 is the motor
            },
    };
    motor_w1 = DJI_Motor_Init(&chassis_w1, M2006); // Initializing motor
}

void Chassis_Ctrl_Loop()
{
    // Control loop for the chassis
}