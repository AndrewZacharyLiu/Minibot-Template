#include "chassis_task.h"

#include "robot.h"
#include "remote.h"
#include "motor.h"
#include "dji_motor.h"


extern Robot_State_t g_robot_state;
extern Remote_t g_remote;
//Added global variable to store motors
DJI_Motor_Handle_t *omni_motors[MOTOR_COUNT];
//global array of wheel speeds (phi)
float wheel_speeds[MOTOR_COUNT];

void Chassis_Task_Init()
{
    //intialize motors
    // Added by Andrew Liu
    for (int i = 1; i <= MOTOR_COUNT; i++) {
        Motor_Config_t chassis_wi = {
            .can_bus = 1, // what can bus the motor is on
            .speed_controller_id = i, // identifier for each motor
            .offset = 0, // Initial offset of the motor (used for encoder)
            .control_mode = VELOCITY_CONTROL, // Control mode of the motor
            .motor_reversal = MOTOR_REVERSAL_NORMAL, // Direction of the motor
            .velocity_pid = // pid
                {
                    .kp = 500.0f,
                    .kd = 0.0f,
                    .kf = 0.0f,
                    .output_limit = M2006_MAX_CURRENT, // m2006 is the motor
                },
        };
        omni_motors[i-1] = DJI_Motor_Init(&chassis_wi, M2006); // Initializing motor
    }
}

void Chassis_Ctrl_Loop()
{
    //Added Andrew Liu
    // update_wheelmovements_from_input();
   
    // add MR
    float vx = g_robot_state.chassis.x_speed;
    float vy = g_robot_state.chassis.y_speed;
    float omega = g_robot_state.chassis.omega;

    update_wheelspeed(vx, vy, omega);

    for (int i = 0; i < MOTOR_COUNT; i++) {
        DJI_Motor_Set_Velocity(omni_motors[i], wheel_speeds[i]);
    }
}

//Andrew Liu: Added helper function convert input into omni chassis movements
// MR: added precomputed vals, changed function (suggestions from Ronak)
void update_wheelspeed(vx, vy, omega) {
    //currently assume omega to be from the right joystick
    wheel_speeds[0] = (SINT *  vx + COST *  vy + WHEEL_DISTANCE * omega) / WHEEL_RADIUS;
    wheel_speeds[1] = (-1 * COST *  vx - SINT *  vy + WHEEL_DISTANCE * omega) / WHEEL_RADIUS;
    wheel_speeds[2] = (SINT *  vx - COST *  vy + WHEEL_DISTANCE * omega) / WHEEL_RADIUS;
    wheel_speeds[3] = (COST *  vx + SINT *  vy + WHEEL_DISTANCE * omega) / WHEEL_RADIUS;
}