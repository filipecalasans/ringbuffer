#include "appendBufferTest.h"

#include "../src/ringbuffer.h"

#define BUFFER_SIZE 128

void Append_Element_No_Round(void** state)
{     
   RingBuffer buffer;
   uint8_t data[BUFFER_SIZE] = {0xFF};
   uint8_t elements[BUFFER_SIZE] = {0};

   assert_int_equal(ringBufferInit(&buffer, data, BUFFER_SIZE), 1);

   for(uint8_t i=0; i<BUFFER_SIZE; i++) {
        elements[i] = i;
        assert_int_equal(elements[i], i);
   }

   for(uint8_t i=0; i<BUFFER_SIZE-1; i++) {
        assert_int_equal(ringBufferLenAvailable(&buffer), BUFFER_SIZE-i-1);
        ringBufferAppendOne(&buffer, elements[i]);
        assert_int_equal(ringBufferLen(&buffer), i+1);
   }

   for(uint8_t i=0; i<BUFFER_SIZE-1; i++) {
       assert_int_equal(data[i], elements[i]);
   }
}

void Append_Element_Head_In_The_middle(void** state)
{     
   RingBuffer buffer;
   uint8_t data[BUFFER_SIZE] = {0xFF};
   uint8_t elements[BUFFER_SIZE] = {0};

   assert_int_equal(ringBufferInit(&buffer, data, BUFFER_SIZE), 1);

   /* Simulate Insertions and removals */
   buffer.tail = buffer.head = BUFFER_SIZE/2;

   for(uint8_t i=0; i<BUFFER_SIZE-1; i++) {
        elements[i] = i;
        assert_int_equal(elements[i], i);
   }

   for(uint8_t i=0; i<BUFFER_SIZE-1; i++) {
      assert_int_equal(ringBufferLenAvailable(&buffer), BUFFER_SIZE-i-1);        
      ringBufferAppendOne(&buffer, elements[i]);
      assert_int_equal(ringBufferLen(&buffer), i+1);
   }

   for(uint8_t i=0; i<(BUFFER_SIZE-1)/2; i++) {
       assert_int_equal(data[BUFFER_SIZE/2 + i], elements[i]);
   }
   
   for(uint8_t i=BUFFER_SIZE/2; i<BUFFER_SIZE-1; i++) {
       assert_int_equal(data[i-BUFFER_SIZE/2], elements[i]);
   }
}

void Append_Multiple_Elements_No_Round(void** state)
{     
   RingBuffer buffer;
   uint8_t data[BUFFER_SIZE] = {0xFF};
   uint8_t elements[BUFFER_SIZE] = {0};

   assert_int_equal(ringBufferInit(&buffer, data, BUFFER_SIZE), 1);

   for(uint8_t i=0; i<BUFFER_SIZE-1; i++) {
        elements[i] = i;
        assert_int_equal(elements[i], i);
   }

   assert_int_equal(ringBufferLenAvailable(&buffer), BUFFER_SIZE-1);
   ringBufferAppendMultiple(&buffer, elements, BUFFER_SIZE-1);
   assert_int_equal(ringBufferLen(&buffer), BUFFER_SIZE-1);

   for(uint8_t i=0; i<BUFFER_SIZE-1; i++) {
       assert_int_equal(data[i], elements[i]);
   }
   /* Simulate Insertions and removals */
   buffer.tail = buffer.head = BUFFER_SIZE/2;
   /* Simulate Insertions and removals */
   buffer.tail = buffer.head = BUFFER_SIZE/2;
}


void Append_Multiple_Elements_Head_In_The_middle(void** state)
{     
   RingBuffer buffer;
   uint8_t data[BUFFER_SIZE] = {0xFF};
   uint8_t elements[BUFFER_SIZE] = {0};

   assert_int_equal(ringBufferInit(&buffer, data, BUFFER_SIZE), 1);

   /* Simulate Insertions and removals */
   buffer.tail = buffer.head = BUFFER_SIZE/2;

   for(uint8_t i=0; i<BUFFER_SIZE-1; i++) {
        elements[i] = i;
        assert_int_equal(elements[i], i);
   }
   
   assert_int_equal(ringBufferLenAvailable(&buffer), BUFFER_SIZE-1);
   ringBufferAppendMultiple(&buffer, elements, BUFFER_SIZE-1);
   assert_int_equal(ringBufferLen(&buffer), BUFFER_SIZE-1);

   for(uint8_t i=0; i<(BUFFER_SIZE-1)/2; i++) {
       assert_int_equal(data[BUFFER_SIZE/2 + i], elements[i]);
   }

   for(uint8_t i=BUFFER_SIZE/2; i<BUFFER_SIZE-1; i++) {
       assert_int_equal(data[i-BUFFER_SIZE/2], elements[i]);
   }
}
