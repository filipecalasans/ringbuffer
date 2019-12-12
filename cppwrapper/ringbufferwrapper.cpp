#include "ringbufferwrapper.h"

#ifndef NULL
#define NULL 0;
#endif

RingBufferWrapper::RingBufferWrapper(uint8_t* data, uint32_t len, bool deallocate)
  : deallocate(deallocate)
  , valid(false)
{
  valid = ringBufferInit(&buffer, data, len);
  if(!valid && deallocate) {
    delete[] data;
    buffer.data = NULL;
  }
}


RingBufferWrapper::RingBufferWrapper(uint32_t size)
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

RingBufferWrapper::~RingBufferWrapper()
{  
   if(buffer.data && deallocate) {
      delete[] buffer.data;
   }
}

bool RingBufferWrapper::isValid() 
{
   return valid;
}

bool RingBufferWrapper::empty() 
{
   return ringBufferEmpty(&buffer);
}

uint32_t RingBufferWrapper::length() 
{
   return ringBufferLen(&buffer);
}

uint32_t RingBufferWrapper::lengthAvailable() 
{
   return ringBufferLenAvailable(&buffer);
}

uint32_t RingBufferWrapper::capacity() 
{
   return ringBufferMaxSize(&buffer);
}

bool RingBufferWrapper::appendOne(uint8_t data) 
{
   if(length() < capacity()) {
      ringBufferAppendOne(&buffer, data);
      return true;
   }
   return false;
}

uint32_t RingBufferWrapper::appendMultiple(uint8_t *data, uint32_t len) 
{
   uint32_t freeSpace = lengthAvailable();
   if(freeSpace == 0) { return 0; }

   if(len > freeSpace) {
      len = freeSpace;
   }

   ringBufferAppendMultiple(&buffer, data, len);
   return len;
}

uint8_t RingBufferWrapper::peekOne() 
{
   if(!length()) { return 0; }
   return ringBufferPeekOne(&buffer);
}

uint8_t RingBufferWrapper::getOne() 
{
   if(!length()) { return 0; }
   return ringBufferGetOne(&buffer);
}

uint32_t RingBufferWrapper::getMultiple(uint8_t *dst, uint32_t len)
{
   uint32_t currentLen = length();
   if(currentLen == 0) { return 0; }

   if(len > currentLen) {
      len = currentLen;
   }

   ringBufferGetMultiple(&buffer, dst, len);
   return len; 
}

uint32_t RingBufferWrapper::peekMultiple(uint8_t *dst, uint32_t len) 
{
   uint32_t currentLen = length();
   if(currentLen == 0) { return 0; }

   if(len > currentLen) {
      len = currentLen;
   }

   ringBufferPeekMultiple(&buffer, dst, len);
   return len; 
}

uint32_t RingBufferWrapper::discardMultiple(uint32_t len)
{  
   uint32_t currentLen = length();
   if(currentLen == 0) { return 0; }

   if(len > currentLen) {
      len = currentLen;
   }

   ringBufferDiscardMultiple(&buffer, len);
   return len;
}

void RingBufferWrapper::clear() 
{
   ringBufferClear(&buffer);
}
