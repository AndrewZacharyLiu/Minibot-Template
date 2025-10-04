#ifndef CHASSIS_TASK_H
#define CHASSIS_TASK_H

// Function prototypes
void Chassis_Task_Init(void);
void Chassis_Ctrl_Loop(void);

//Added by Andrew Liu
//Constants for wheel dimension
#define WHEEL_RADIUS 0.05
#define WHEEL_DISTANCE 1
#define MOTOR_COUNT 4

#endif // CHASSIS_TASK_H
