#include "linear_buffer.h"

#include "string.h"
/**
 * @brief Initialize a linear buffer
 *
 * @param buffer: pointer to buffer array
 * @param len: length of buffer
 * @return LinearBuffer_t
 */
LinearBuffer_t linear_buf_init(uint8_t *buffer, uint16_t len)
{
    LinearBuffer_t buf = {
        .buffer = buffer,
        .buf_len = len,
        .bytesWritten = 0,
    };
    linear_buf_clear(&buf);
    return buf;
}

/**
 * @brief add a byte to the linear buffer, returns false if buffer full
 *
 * @param buf: buffer to add byte to
 * @param value: value added
 * @return true
 * @return false
 */
bool linear_buf_push(LinearBuffer_t *buf, uint8_t value)
{
    if (buf->bytesWritten >= buf->buf_len)
    {
        return false;
    }
    else
    {
        buf->buffer[buf->bytesWritten] = value;
        buf->bytesWritten++;
        return true;
    }
}

void linear_buf_clear(LinearBuffer_t *buf)
{
    buf->bytesWritten = 0;
    memset(buf->buffer, 0, buf->buf_len);
}