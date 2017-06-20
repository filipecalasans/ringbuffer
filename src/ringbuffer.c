#include "ringbuffer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ringBufferInit(RingBuffer *buffer, uint8_t *data, uint32_t len) {
   if(!(len && !(len & (len - 1)))) {
      return 0;
   }

   buffer->tail = 0;
   buffer->head = 0;
   buffer->sizeMask = len-1;
   return 1;
}

uint32_t ringBufferLen(RingBuffer *buffer) {
   return (buffer->tail - buffer->head) & buffer->sizeMask;
}

uint8_t ringBufferEmpty(RingBuffer *buffer) {
   return (buffer->tail == buffer->head);
}

uint32_t ringBufferLenAvailable(RingBuffer *buffer){
   return buffer->sizeMask - ringBufferLen(buffer) + 1;
}

uint32_t ringBufferAppendOne(RingBuffer *buffer, uint8_t data){
   buffer->data[buffer->head] = data;
   buffer->head = (buffer->head + 1) & buffer->sizeMask;
}

uint32_t ringBufferAppendMultiple(RingBuffer *buffer, uint8_t *data, uint32_t len){
   if(buffer->tail + len > buffer->sizeMask) {
      uint32_t lenToTheEnd = buffer->sizeMask - buffer->tail;
      uint32_t lenFromBegin = len - lenToTheEnd;
      memcpy(buffer->data + ringBufferLen(buffer), data, lenToTheEnd);
      memcpy(buffer->data, data + lenToTheEnd, lenFromBegin);
   }
   else {
      memcpy(buffer->data, data, len);
   }
   buffer->tail = (buffer->tail + len) & buffer->sizeMask;
}

uint8_t ringBufferPeakOne(RingBuffer *buffer){
   return buffer->data[buffer->head];
}

uint8_t ringBufferGetOne(RingBuffer *buffer){
   uint8_t data =  buffer->data[buffer->head];
   buffer->head = (buffer->head + 1) & buffer->sizeMask;
   return data;
}

uint32_t ringBufferGetMultiple(RingBuffer *buffer, uint8_t *dst, uint32_t len) {

}

uint32_t ringBufferPeakMultiple(RingBuffer *buffer, uint8_t *dst, uint32_t len){

}

uint32_t ringBufferDiscardMultiple(RingBuffer *buffer, uint32_t len){

}

uint32_t ringBufferClear(RingBuffer *buffer){
   buffer->head = buffer->tail = 0;
}