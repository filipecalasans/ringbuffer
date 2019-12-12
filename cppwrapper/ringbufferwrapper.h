#ifndef __RING_BUFFER_WRAPPER_H__
#define __RING_BUFFER_WRAPPER_H__

#include <stdint.h>
#include "../src/ringbuffer.h"

class RingBufferWrapper {

public:

   /*
   * Warning: Size must be multiple of 2.
   */
  explicit RingBufferWrapper(uint8_t* data, uint32_t len, bool deallocate = false); 
  explicit RingBufferWrapper(uint32_t size);
   ~RingBufferWrapper();

   bool isValid();

   bool empty();
   uint32_t length();
   uint32_t lengthAvailable();
   uint32_t capacity();

   bool appendOne(uint8_t data);
   uint32_t appendMultiple(uint8_t *data, uint32_t len);

   uint8_t peekOne();
   uint8_t getOne();

   uint32_t getMultiple(uint8_t *dst, uint32_t len);
   uint32_t peekMultiple(uint8_t *dst, uint32_t len);

   uint32_t discardMultiple(uint32_t len);
   void clear();   

private:

   RingBuffer buffer;
   bool valid;
   bool deallocate;
};

#endif
