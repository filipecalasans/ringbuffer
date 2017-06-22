#include "appendBufferTest.h"

#include "../src/ringbuffer.h"

#define BUFFER_SIZE 128

START_TEST (Append_Element_No_Round)
{     
   RingBuffer buffer;
   uint8_t data[BUFFER_SIZE] = {0xFF};
   uint8_t elements[BUFFER_SIZE] = {0};

   ck_assert_int_eq(ringBufferInit(&buffer, data, BUFFER_SIZE), 1);

   for(uint8_t i=0; i<BUFFER_SIZE; i++) {
        elements[i] = i;
        ck_assert_int_eq(elements[i], i);
   }

   for(uint8_t i=0; i<BUFFER_SIZE-1; i++) {
        ck_assert_int_eq(ringBufferLenAvailable(&buffer), BUFFER_SIZE-i-1);
        ringBufferAppendOne(&buffer, elements[i]);
        ck_assert_int_eq(ringBufferLen(&buffer), i+1);
   }

   for(uint8_t i=0; i<BUFFER_SIZE-1; i++) {
       ck_assert_int_eq(data[i], elements[i]);
   }

}
END_TEST

START_TEST (Append_Element_Head_In_The_middle)
{     
    
   RingBuffer buffer;
   uint8_t data[BUFFER_SIZE] = {0xFF};
   uint8_t elements[BUFFER_SIZE] = {0};

   ck_assert_int_eq(ringBufferInit(&buffer, data, BUFFER_SIZE), 1);

   /* Simulate Insertions and removals */
   buffer.tail = buffer.head = BUFFER_SIZE/2;

   for(uint8_t i=0; i<BUFFER_SIZE-1; i++) {
        elements[i] = i;
        ck_assert_int_eq(elements[i], i);
   }

   for(uint8_t i=0; i<BUFFER_SIZE-1; i++) {
      ck_assert_int_eq(ringBufferLenAvailable(&buffer), BUFFER_SIZE-i-1);        
      ringBufferAppendOne(&buffer, elements[i]);
      ck_assert_int_eq(ringBufferLen(&buffer), i+1);
   }

   for(uint8_t i=0; i<(BUFFER_SIZE-1)/2; i++) {
       ck_assert_int_eq(data[BUFFER_SIZE/2 + i], elements[i]);
   }
   
   for(uint8_t i=BUFFER_SIZE/2; i<BUFFER_SIZE-1; i++) {
       ck_assert_int_eq(data[i-BUFFER_SIZE/2], elements[i]);
   }

}
END_TEST


START_TEST (Append_Multiple_Elements_No_Round)
{     
   RingBuffer buffer;
   uint8_t data[BUFFER_SIZE] = {0xFF};
   uint8_t elements[BUFFER_SIZE] = {0};

   ck_assert_int_eq(ringBufferInit(&buffer, data, BUFFER_SIZE), 1);

   for(uint8_t i=0; i<BUFFER_SIZE-1; i++) {
        elements[i] = i;
        ck_assert_int_eq(elements[i], i);
   }

   ck_assert_int_eq(ringBufferLenAvailable(&buffer), BUFFER_SIZE-1);
   ringBufferAppendMultiple(&buffer, elements, BUFFER_SIZE-1);
   ck_assert_int_eq(ringBufferLen(&buffer), BUFFER_SIZE-1);

   for(uint8_t i=0; i<BUFFER_SIZE-1; i++) {
       ck_assert_int_eq(data[i], elements[i]);
   }

}
END_TEST


START_TEST (Append_Multiple_Elements_Head_In_The_middle)
{     
    
   RingBuffer buffer;
   uint8_t data[BUFFER_SIZE] = {0xFF};
   uint8_t elements[BUFFER_SIZE] = {0};

   ck_assert_int_eq(ringBufferInit(&buffer, data, BUFFER_SIZE), 1);

   /* Simulate Insertions and removals */
   buffer.tail = buffer.head = BUFFER_SIZE/2;

   for(uint8_t i=0; i<BUFFER_SIZE-1; i++) {
        elements[i] = i;
        ck_assert_int_eq(elements[i], i);
   }
   
   ck_assert_int_eq(ringBufferLenAvailable(&buffer), BUFFER_SIZE-1);
   ringBufferAppendMultiple(&buffer, elements, BUFFER_SIZE-1);
   ck_assert_int_eq(ringBufferLen(&buffer), BUFFER_SIZE-1);

   for(uint8_t i=0; i<(BUFFER_SIZE-1)/2; i++) {
       ck_assert_int_eq(data[BUFFER_SIZE/2 + i], elements[i]);
   }

   for(uint8_t i=BUFFER_SIZE/2; i<BUFFER_SIZE-1; i++) {
       ck_assert_int_eq(data[i-BUFFER_SIZE/2], elements[i]);
   }

}
END_TEST

Suite * append_buffer_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Append Data to Buffer");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, Append_Element_No_Round);
    tcase_add_test(tc_core, Append_Element_Head_In_The_middle);
    tcase_add_test(tc_core, Append_Multiple_Elements_No_Round);
    tcase_add_test(tc_core, Append_Multiple_Elements_Head_In_The_middle);

    suite_add_tcase(s, tc_core);

    return s;
}