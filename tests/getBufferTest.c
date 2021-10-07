#include "getBufferTest.h"

#include <ringbuffer/c/ringbuffer.h>

#define BUFFER_SIZE 128

void Peek_One_After_Multiple_Insertions(void** state)
{     
   RingBuffer buffer;
   uint8_t data[BUFFER_SIZE] = {0xFF};
   uint8_t elements[BUFFER_SIZE] = {0};

   assert_int_equal(ringBufferInit(&buffer, data, BUFFER_SIZE), 1);

   for(uint8_t i=0; i<BUFFER_SIZE; i++) {
        elements[i] = i;
        assert_int_equal(elements[i], i);
   }

   assert_int_equal(ringBufferEmpty(&buffer), 1);

   for(uint8_t i=0; i<BUFFER_SIZE-1; i++) {
        assert_int_equal(ringBufferFreeSpace(&buffer), BUFFER_SIZE-i-1);
        ringBufferAppendOne(&buffer, elements[i]);
        assert_int_equal(ringBufferLen(&buffer), i+1);
        assert_int_equal(ringBufferEmpty(&buffer), 0);
        assert_int_equal(ringBufferPeekOne(&buffer), elements[0]);
   }
}

void Get_One_After_Multiple_Insertions(void** state)
{     
   RingBuffer buffer;
   uint8_t data[BUFFER_SIZE] = {0xFF};
   uint8_t elements[BUFFER_SIZE] = {0};

   assert_int_equal(ringBufferInit(&buffer, data, BUFFER_SIZE), 1);

   for(uint8_t i=0; i<BUFFER_SIZE; i++) {
        elements[i] = i;
        assert_int_equal(elements[i], i);
   }

   assert_int_equal(ringBufferEmpty(&buffer), 1);

   for(uint8_t i=0; i<BUFFER_SIZE-1; i++) {
        assert_int_equal(ringBufferFreeSpace(&buffer), BUFFER_SIZE-i-1);
        ringBufferAppendOne(&buffer, elements[i]);
        assert_int_equal(ringBufferLen(&buffer), i+1);
        assert_int_equal(ringBufferEmpty(&buffer), 0);
   }

   for(uint8_t i=0; i<BUFFER_SIZE-1; i++) {
        assert_int_equal(ringBufferLen(&buffer), BUFFER_SIZE-i-1);
        assert_int_equal(ringBufferGetOne(&buffer), elements[i]);
   }

   assert_int_equal(ringBufferEmpty(&buffer), 1);
}

void Get_Multiple_After_Multiple_Insertions_No_Round(void** state)
{     
   RingBuffer buffer;
   uint8_t data[BUFFER_SIZE] = {0xFF};
   uint8_t elements[BUFFER_SIZE] = {0};

   assert_int_equal(ringBufferInit(&buffer, data, BUFFER_SIZE), 1);

   for(uint8_t i=0; i<BUFFER_SIZE; i++) {
        elements[i] = i;
        assert_int_equal(elements[i], i);
   }

   assert_int_equal(ringBufferEmpty(&buffer), 1);

   for(uint8_t i=0; i<BUFFER_SIZE-1; i++) {
        assert_int_equal(ringBufferFreeSpace(&buffer), BUFFER_SIZE-i-1);
        ringBufferAppendOne(&buffer, elements[i]);
        assert_int_equal(ringBufferLen(&buffer), i+1);
        assert_int_equal(ringBufferEmpty(&buffer), 0);
   }

   uint8_t out[BUFFER_SIZE];

   ringBufferGetMultiple(&buffer, out, ringBufferLen(&buffer));
   assert_int_equal(ringBufferLen(&buffer), 0);

   for(uint8_t i=0; i<BUFFER_SIZE-1; i++) {
        assert_int_equal(out[i], elements[i]);
   }

   assert_int_equal(ringBufferEmpty(&buffer), 1);
}

void Get_Multiple_After_Multiple_Insertions_Round(void** state)
{     
   RingBuffer buffer;
   uint8_t data[BUFFER_SIZE] = {0xFF};
   uint8_t elements[BUFFER_SIZE] = {0};

   assert_int_equal(ringBufferInit(&buffer, data, BUFFER_SIZE), 1);

   for(uint8_t i=0; i<BUFFER_SIZE; i++) {
        elements[i] = i;
        assert_int_equal(elements[i], i);
   }

   /* Simulate Insertions and removals */
   buffer.tail = buffer.head = BUFFER_SIZE/2;

   assert_int_equal(ringBufferEmpty(&buffer), 1);

   assert_int_equal(ringBufferFreeSpace(&buffer), BUFFER_SIZE-1);
   ringBufferAppendMultiple(&buffer, elements, BUFFER_SIZE-1);
   assert_int_equal(ringBufferLen(&buffer), BUFFER_SIZE-1);

   uint8_t out[BUFFER_SIZE];
   ringBufferGetMultiple(&buffer, out, ringBufferLen(&buffer));
   assert_int_equal(ringBufferLen(&buffer), 0);

   for(uint8_t i=0; i<BUFFER_SIZE-1; i++) {
        assert_int_equal(out[i], elements[i]);
   }

   assert_int_equal(ringBufferEmpty(&buffer), 1);
}
