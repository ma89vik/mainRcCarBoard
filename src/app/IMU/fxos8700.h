#pragma once

#include <stdint.h>

#include "error_def.h"
#include "app_i2c.h"

typedef struct {
    int16_t x;    
    int16_t y;
    int16_t z;
} xyz_data_t;

err_def_t fxos8700_init(app_i2c_handle_t* i2c_handle);
void fxso8700_read_data(xyz_data_t *accel_data, xyz_data_t* mag_data);

// bool mpu9250_read_gyro(int16_t *x, int16_t *y, int16_t *z);
// bool mpu9250_read_accel(int16_t *x, int16_t *y, int16_t *z);

// bool mpu9250_read_accel_xy(int16_t *x, int16_t *y);
// bool mpu9250_read_gyro_yaw_rate(int16_t *z);
