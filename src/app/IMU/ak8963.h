#ifndef AK8963_H_
#define AK8963_H_

#include <stdbool.h>
#include <stdint.h>

bool ak8963_init();
bool ak8963_read_mag(int16_t *x, int16_t *y, int16_t *z);

#endif