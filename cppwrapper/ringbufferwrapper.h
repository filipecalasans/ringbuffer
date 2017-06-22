#ifndef __RING_BUFFER_WRAPPER_H__
#define __RING_BUFFER_WRAPPER_H__


// int ringBufferInit(RingBuffer *buffer, uint8_t *data, uint32_t len);

// uint32_t ringBufferLen(RingBuffer *buffer);
// uint8_t ringBufferEmpty(RingBuffer *buffer);
// uint32_t ringBufferLenAvailable(RingBuffer *buffer);
// uint32_t ringBufferMaxSize(RingBuffer *buffer);

// uint32_t ringBufferAppendOne(RingBuffer *buffer, uint8_t data);
// uint32_t ringBufferAppendMultiple(RingBuffer *buffer, uint8_t *data, uint32_t len);

// uint8_t ringBufferPeakOne(RingBuffer *buffer);
// uint8_t ringBufferGetOne(RingBuffer *buffer);

// void ringBufferGetMultiple(RingBuffer *buffer, uint8_t *dst, uint32_t len);
// void ringBufferPeakMultiple(RingBuffer *buffer, uint8_t *dst, uint32_t len);

// void ringBufferDiscardMultiple(RingBuffer *buffer, uint32_t len);
// void ringBufferClear(RingBuffer *buffer);

#include <stdint.h>

#include "../src/ringbuffer.h"

class RingBufferWrapper {

public:

   /*
   * Warning: Size must be multiple of 2.
   */
   explicit RingBufferWrapper(uint32_t size);
   ~RingBufferWrapper();

   bool isValid();

   bool empty();
   uint32_t length();
   uint32_t lengthAvailable();
   uint32_t capacity();

   bool appendOne(uint8_t data);
   uint32_t appendMultiple(uint8_t *data, uint32_t len);

   uint8_t peakOne();
   uint8_t getOne();

   uint32_t getMultiple(uint8_t *dst, uint32_t len);
   uint32_t peakMultiple(uint8_t *dst, uint32_t len);

   uint32_t discardMultiple(uint32_t len);
   void clear();   

private:

   RingBuffer buffer;
   bool valid;

};

#endif