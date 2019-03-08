#ifndef MPU9250_H_
#define MPU9250_H_

#include <stdbool.h>
#include <stdint.h>

bool mpu9250_init();
bool mpu9250_read_gyro(int16_t *x, int16_t *y, int16_t *z);
bool mpu9250_read_accel(int16_t *x, int16_t *y, int16_t *z);

bool mpu9250_read_accel_xy(int16_t *x, int16_t *y);
bool mpu9250_read_gyro_yaw_rate(int16_t *z);

#endif