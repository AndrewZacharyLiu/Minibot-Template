#include "chassis_task.h"

#include "robot.h"
#include "remote.h"

extern Robot_State_t g_robot_state;
extern Remote_t g_remote;

float chassis_rad;

void Chassis_Task_Init()
{
    // Init chassis hardware
}

void Chassis_Ctrl_Loop()
{
    //Added Andrew Liu
    update_wheelmovements_from_input();

}

//Added helper function convert input into omni chassis movements
void update_wheelmovements_from_input() {
        float wheel_radius = 1; // TODO: This is hardcoded constant. replace with actual
        float d = 1; // TODO: This is hardcoded constant. replace with actual. d is distance between wheel
        float vx = g_robot_state.chassis.x_speed;
        float vy = g_robot_state.chassis.y_speed;

        float theta = 0;
        float sintheta = sin(theta);
        float costheta = cos(theta);

        //TODO: call set velocty functions to set each wheel movements
        wheelmovements[0] = (sintheta *  vx + costheta *  vy + d * theta) / wheel_radius;
        wheelmovements[1] = (-1 * costheta *  vx - sintheta *  vy + d * theta) / wheel_radius;
        wheelmovements[2] = (sintheta *  vx - costheta *  vy + d * theta) / wheel_radius;
        wheelmovements[3] = (costheta *  vx + sintheta *  vy+ d * theta) / wheel_radius;
}