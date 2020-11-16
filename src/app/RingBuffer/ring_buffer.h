/*
 * ring_buffer.h
 *
 *  Created on: 25. jan. 2018
 *      Author: mv
 */

#ifndef RING_BUFFER_H_
#define RING_BUFFER_H_

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

typedef struct RingBuffer
{
    uint8_t *buffer;
    uint16_t n_elem;
    uint16_t head;
    uint16_t tail;
} RingBuffer_t;

int ring_buffer_init(RingBuffer_t *const ringBuffer, uint8_t *const buffer,
                     uint16_t n_elem);
int ring_buffer_get(RingBuffer_t *const buffer, uint8_t *dataOut);
int ring_buffer_set_head(RingBuffer_t *const ringBuffer, size_t index);

int ring_buffer_put(RingBuffer_t *const buffer, uint8_t dataIn);
bool ring_buffer_empty(RingBuffer_t *const ringBuffer);
bool ring_buffer_full(RingBuffer_t *const ringBuffer);
uint16_t ring_buffer_length(RingBuffer_t *const ringBuffer);

#endif /* RING_BUFFER_H_ */
