#include "ringbufferwrapper.h"

#ifndef NULL
#define NULL 0;
#endif

RingBufferWrapper::RingBufferWrapper(uint8_t* data, uint32_t len, bool deallocate) noexcept
  : deallocate(deallocate)
  , valid(false)
{
  valid = ringBufferInit(&buffer, data, len);
  if(!valid && deallocate) {
    delete[] data;
    buffer.data = NULL;
  }
}


RingBufferWrapper::RingBufferWrapper(uint32_t size) noexcept
   : valid(false)
   , deallocate(true)
{ 
   uint8_t *data = new uint8_t[size];
   valid = ringBufferInit(&buffer, data, size);

   if(!valid) { 
      delete[] data;
      buffer.data = NULL;
   }
}

RingBufferWrapper::~RingBufferWrapper() noexcept
{  
   if(buffer.data && deallocate) {
      delete[] buffer.data;
   }
}

bool RingBufferWrapper::isValid() noexcept
{
   return valid;
}

bool RingBufferWrapper::empty() noexcept
{
   return ringBufferEmpty(&buffer);
}

uint32_t RingBufferWrapper::length() noexcept
{
   return ringBufferLen(&buffer);
}

uint32_t RingBufferWrapper::lengthAvailable() noexcept
{
   return ringBufferLenAvailable(&buffer);
}

uint32_t RingBufferWrapper::capacity() noexcept
{
   return ringBufferMaxSize(&buffer);
}

bool RingBufferWrapper::appendOne(uint8_t data) noexcept
{
   if(length() < capacity()) {
      ringBufferAppendOne(&buffer, data);
      return true;
   }
   return false;
}

uint32_t RingBufferWrapper::appendMultiple(uint8_t *data, uint32_t len) noexcept
{
   uint32_t freeSpace = lengthAvailable();
   if(freeSpace == 0) { return 0; }

   if(len > freeSpace) {
      len = freeSpace;
   }

   ringBufferAppendMultiple(&buffer, data, len);
   return len;
}

uint8_t RingBufferWrapper::peekOne() noexcept
{
   if(!length()) { return 0; }
   return ringBufferPeekOne(&buffer);
}

uint8_t RingBufferWrapper::getOne() noexcept
{
   if(!length()) { return 0; }
   return ringBufferGetOne(&buffer);
}

uint32_t RingBufferWrapper::getMultiple(uint8_t *dst, uint32_t len) noexcept
{
   uint32_t currentLen = length();
   if(currentLen == 0) { return 0; }

   if(len > currentLen) {
      len = currentLen;
   }

   ringBufferGetMultiple(&buffer, dst, len);
   return len; 
}

uint32_t RingBufferWrapper::peekMultiple(uint8_t *dst, uint32_t len) noexcept
{
   uint32_t currentLen = length();
   if(currentLen == 0) { return 0; }

   if(len > currentLen) {
      len = currentLen;
   }

   ringBufferPeekMultiple(&buffer, dst, len);
   return len; 
}

uint32_t RingBufferWrapper::discardMultiple(uint32_t len) noexcept
{  
   uint32_t currentLen = length();
   if(currentLen == 0) { return 0; }

   if(len > currentLen) {
      len = currentLen;
   }

   ringBufferDiscardMultiple(&buffer, len);
   return len;
}

void RingBufferWrapper::clear() noexcept
{
   ringBufferClear(&buffer);
}
