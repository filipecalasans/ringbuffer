#ifndef __RING_BUFFER_WRAPPER_H__
#define __RING_BUFFER_WRAPPER_H__

#include <stdint.h>
#include "../src/ringbuffer.h"

class RingBufferWrapper {

public:

   /*
   * Warning: Size must be multiple of 2.
   */
   explicit RingBufferWrapper(uint8_t* data, uint32_t len, bool deallocate = false) noexcept; 
   explicit RingBufferWrapper(uint32_t size) noexcept;
   virtual ~RingBufferWrapper() noexcept;

   bool isValid() noexcept;

   bool empty() noexcept;
   uint32_t length() noexcept;
   uint32_t lengthAvailable() noexcept;
   uint32_t capacity() noexcept;

   bool appendOne(uint8_t data) noexcept;
   uint32_t appendMultiple(uint8_t *data, uint32_t len) noexcept;

   uint8_t peekOne() noexcept;
   uint8_t getOne() noexcept;

   uint32_t getMultiple(uint8_t *dst, uint32_t len) noexcept;
   uint32_t peekMultiple(uint8_t *dst, uint32_t len) noexcept;

   uint32_t discardMultiple(uint32_t len) noexcept;
   void clear() noexcept;

private:

   RingBuffer buffer;
   bool valid;
   bool deallocate;
};

#endif
