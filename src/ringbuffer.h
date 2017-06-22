#ifndef __RING_BUFFER_H_
#define __RING_BUFFER_H_

#include <stdint.h>
#include <stdio.h>

#ifdef  __cplusplus
extern  "C" {
#endif

typedef struct {
   uint32_t tail;
   uint32_t head;
   uint32_t sizeMask;
   uint8_t *data;
}RingBuffer;

int ringBufferInit(RingBuffer *buffer, uint8_t *data, uint32_t len);

uint32_t ringBufferLen(RingBuffer *buffer);
uint8_t ringBufferEmpty(RingBuffer *buffer);
uint32_t ringBufferLenAvailable(RingBuffer *buffer);
uint32_t ringBufferMaxSize(RingBuffer *buffer);

void ringBufferAppendOne(RingBuffer *buffer, uint8_t data);
void ringBufferAppendMultiple(RingBuffer *buffer, uint8_t *data, uint32_t len);

uint8_t ringBufferPeakOne(RingBuffer *buffer);
uint8_t ringBufferGetOne(RingBuffer *buffer);

void ringBufferGetMultiple(RingBuffer *buffer, uint8_t *dst, uint32_t len);
void ringBufferPeakMultiple(RingBuffer *buffer, uint8_t *dst, uint32_t len);

void ringBufferDiscardMultiple(RingBuffer *buffer, uint32_t len);
void ringBufferClear(RingBuffer *buffer);

#ifdef  __cplusplus
      }
#endif

#endif