#ifndef __RING_BUFFER_H_
#define __RING_BUFFER_H_

#include <stdint.h>
#include <stdio.h>

typedef struct {
   uint32_t tail;
   uint32_t head;
   uint32_t sizeMask;
   uint32_t size;
   uint8_t *data;
}RingBuffer;

void initRingBuffer(RingBuffer *buffer, uint8_t *data, uint32_t len);

uint32_t ringBufferLen(RingBuffer *buffer);
uint8_t ringBufferEmpty(RingBuffer *buffer);
uint32_t ringBufferLenAvailable(RingBuffer *buffer);

uint32_t ringBufferAppendOne(RingBuffer *buffer, uint8_t data);
uint32_t ringBufferAppendMultiple(RingBuffer *buffer, uint8_t *data, uint32_t len);

uint8_t ringBufferPeakOne(RingBuffer *buffer);
uint8_t ringBufferGetOne(RingBuffer *buffer);

uint32_t ringBufferGetMultiple(RingBuffer *buffer, uint8_t *dst, uint32_t len);
uint32_t ringBufferPeakMultiple(RingBuffer *buffer, uint8_t *dst, uint32_t len);

uint32_t ringBufferDiscardMultiple(RingBuffer *buffer, uint32_t len);
uint32_t ringBufferClear(RingBuffer *buffer);

#endif