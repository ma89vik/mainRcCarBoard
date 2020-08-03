#ifndef LINEAR_BUFFER_H_
#define LINEAR_BUFFER_H_

#include <stdbool.h>
#include <stdint.h>

typedef struct LinearBuffer
{
    uint8_t *buffer;
    uint16_t buf_len;
    uint16_t bytesWritten;
} LinearBuffer_t;

LinearBuffer_t linear_buf_init(uint8_t *buffer, uint16_t len);

bool linear_buf_push(LinearBuffer_t *buf, uint8_t value);

void linear_buf_clear(LinearBuffer_t *buf);

#endif
