#include "initBufferTest.h"

#include "../src/ringbuffer.h"

#define BUFFER_SIZE 256

void Init_Buffer_Size_multiple_of_2(void **state)
{     
   RingBuffer buffer;
   uint8_t data[128];
   assert_int_equal(ringBufferInit(&buffer, data, BUFFER_SIZE), 1);
   assert_int_equal(0xFF, buffer.sizeMask);
   assert_int_equal(buffer.tail, 0);
   assert_int_equal(buffer.head, 0);
   assert_int_equal(buffer.data, data);
}

void Init_Buffer_Size_Not_multiple_of_2(void **state)
{     
   RingBuffer buffer;
   uint8_t data[128];
   assert_int_equal(ringBufferInit(&buffer, data, 126), 0);
}