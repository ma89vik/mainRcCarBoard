
#include <math.h>
#include <stdbool.h>
#include <stdint.h>

#include "ak8963.h"
#include "imu_handler.h"
#include "log.h"
#include "mpu9250.h"
#include "i2c_device.h"
#include "board.h"

void imu_init()
{
    i2c_init(&deviceI2c);
    
    // Initialize accel, gyro and magnetometer, MPU9250 needs to be init first
    if (!mpu9250_init())
    {
        LOG_ERROR("IMU init failed\n");
    }

    if (!ak8963_init())
    {
        LOG_ERROR("IMU init failed\n");
    }
}

/**
 * @brief  Reads compass heading, not tilt compensated
 * @note
 * @retval heading in radians [0-2pi] with 0 being north
 */
float read_compass_heading()
{
    uint16_t x, y, z;
    ak8963_read_mag(&x, &y, &z);

    float heading = atan2f(y, x);

    return heading;
}
