/*
 * ring_buffer.c
 *
 *  Created on: 25. jan. 2018
 *      Author: mv
 */

#include "ring_buffer.h"
#include <stddef.h>

int ring_buffer_init(RingBuffer_t *const ringBuffer, uint8_t *const buffer,
                     uint16_t n_elem)
{
    int err = -1;

    if ((ringBuffer == NULL) || (buffer == NULL))
    {
        return err;
    }

    /* Check that the desired size of the ring buffer is a power of 2 */
    if (((n_elem - 1) & n_elem) == 0)
    {
        /* Initialize the ring buffer internal variables */
        ringBuffer->buffer = buffer;
        ringBuffer->head = 0;
        ringBuffer->tail = 0;
        ringBuffer->n_elem = n_elem;

        err = 0;
    }

    return err;
}

bool ring_buffer_full(RingBuffer_t *const ringBuffer)
{
    if ((ringBuffer->head - ringBuffer->tail) == ringBuffer->n_elem)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool ring_buffer_empty(RingBuffer_t *const ringBuffer)
{
    if ((ringBuffer->head - ringBuffer->tail) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

uint16_t ring_buffer_length(RingBuffer_t *const ringBuffer)
{
    //Works even when head > tail
    return (ringBuffer->head - ringBuffer->tail);
}

int ring_buffer_put(RingBuffer_t *const ringBuffer, uint8_t dataIn)
{
    int err = -1;

    if (!ring_buffer_full(ringBuffer))
    {
        // Calculates the offset by using the fact that n_elem is a power of 2
        uint16_t index = (ringBuffer->head & (ringBuffer->n_elem - 1));
        ringBuffer->buffer[index] = dataIn;
        ringBuffer->head++;

        err = 0;
    }

    return err;
}

int ring_buffer_get(RingBuffer_t *const ringBuffer, uint8_t *dataOut)
{
    int err = -1;

    if (!ring_buffer_empty(ringBuffer))
    {
        // Calculates the offset by using the fact that n_elem is a power of 2
        uint16_t index = (ringBuffer->tail & (ringBuffer->n_elem - 1));
        *dataOut = ringBuffer->buffer[index];
        ringBuffer->tail++;

        err = 0;
    }
    return err;
}

int ring_buffer_length(RingBuffer_t *const buffer);

/*






int ring_buffer_search(rbd_t rbd, char cmpData)
{
    int err = 0;
    size_t search_idx;

    for(int i = 0; i<_rb[rbd].n_elem;i++)
    {
      search_idx = ((_rb[rbd].tail+i) & (_rb[rbd].n_elem - 1)) *
_rb[rbd].s_elem;
    //  printf("Search index: %d\n",search_idx);
      if(_rb[rbd].buf[search_idx] == cmpData)
      {
        return i+1;
      }
      if(_rb[rbd].tail+i == _rb[rbd].head)
      {
        //Reached end of buffer, did not find
          return 0;
      }
    }


}


int ring_buffer_length(rbd_t rbd)
{
        return(_rb[rbd].head - _rb[rbd].tail);
}
*/