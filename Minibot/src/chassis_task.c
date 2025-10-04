#include "chassis_task.h"

#include "robot.h"
#include "remote.h"
#include "motor.h"
#include "dji_motor.h"


extern Robot_State_t g_robot_state;
extern Remote_t g_remote;
//Added global variable to store motors
DJI_Motor_Handle_t *omni_motors[MOTOR_COUNT];

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
    update_wheelmovements_from_input();

}

//Andrew Liu: Added helper function convert input into omni chassis movements
void update_wheelmovements_from_input() {
    float vx = g_robot_state.chassis.x_speed;
    float vy = g_robot_state.chassis.y_speed;
    float omega = g_robot_state.chassis.omega;
    // you can precompute this as an optimization if you wish.
    float sintheta = sin(MINIBOT_THETA);
    float costheta = cos(MINIBOT_THETA);
    //currently assume theta to be from the right joystick
    float wheel_speeds[4] = {0.0f};
    wheel_speeds[0] = (sintheta *  vx + costheta *  vy + WHEEL_DISTANCE * omega) / WHEEL_RADIUS;
    wheel_speeds[1] = (-1 * costheta *  vx - sintheta *  vy + WHEEL_DISTANCE * omega) / WHEEL_RADIUS;
    wheel_speeds[2] = (sintheta *  vx - costheta *  vy + WHEEL_DISTANCE * omega) / WHEEL_RADIUS;
    wheel_speeds[3] = (costheta *  vx + sintheta *  vy + WHEEL_DISTANCE * omega) / WHEEL_RADIUS;
    for (int i = 0; i < MOTOR_COUNT; i++) {
        DJI_Motor_Set_Velocity(omni_motors[i], wheel_speeds[i]);
    }
        
}