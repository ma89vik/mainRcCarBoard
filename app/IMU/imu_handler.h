#ifndef IMU_HANDLER_H_
#define IMU_HANDLER_H_

#include <stdint.h>

typedef struct ImuData
{
    float accel_x;         // Unfiltered acceleration in x-direction [m/s²]
    float accel_y;         // Unfiltered acceleration in y-direction [m/s²]
    float ang_vel_yaw;     // Unfiltered angular velocity for yaw [rad/s]
    float compass_heading; // Unfiltered heading [rad]

} ImuData_t;

void imu_init();
float read_compass_heading();

#endif