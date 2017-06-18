#include "ringbuffer.h"

void initRingBuffer(RingBuffer *buffer, uint8_t *data, uint32_t len) {
   buffer->tail = 0;
   
}

uint32_t ringBufferLen(RingBuffer *buffer) {

}

uint8_t ringBufferEmpty(RingBuffer *buffer) {

}

uint32_t ringBufferLenAvailable(RingBuffer *buffer){

}

uint32_t ringBufferAppendOne(RingBuffer *buffer, uint8_t data){

}

uint32_t ringBufferAppendMultiple(RingBuffer *buffer, uint8_t *data, uint32_t len){

}

uint8_t ringBufferPeakOne(RingBuffer *buffer){

}

uint8_t ringBufferGetOne(RingBuffer *buffer){

}

uint32_t ringBufferGetMultiple(RingBuffer *buffer, uint8_t *dst, uint32_t len) {

}

uint32_t ringBufferPeakMultiple(RingBuffer *buffer, uint8_t *dst, uint32_t len){

}

uint32_t ringBufferDiscardMultiple(RingBuffer *buffer, uint32_t len){

}

uint32_t ringBufferClear(RingBuffer *buffer){

}