#include "getBufferTest.h"

#include "../src/ringbuffer.h"

#define BUFFER_SIZE 128

START_TEST (Peak_One_After_Multiple_Insertions)
{     
   RingBuffer buffer;
   uint8_t data[BUFFER_SIZE] = {0xFF};
   uint8_t elements[BUFFER_SIZE] = {0};

   ck_assert_int_eq(ringBufferInit(&buffer, data, BUFFER_SIZE), 1);

   for(uint8_t i=0; i<BUFFER_SIZE; i++) {
        elements[i] = i;
        ck_assert_int_eq(elements[i], i);
   }

   ck_assert_int_eq(ringBufferEmpty(&buffer), 1);

   for(uint8_t i=0; i<BUFFER_SIZE-1; i++) {
        ck_assert_int_eq(ringBufferLenAvailable(&buffer), BUFFER_SIZE-i-1);
        ringBufferAppendOne(&buffer, elements[i]);
        ck_assert_int_eq(ringBufferLen(&buffer), i+1);
        ck_assert_int_eq(ringBufferEmpty(&buffer), 0);
        ck_assert_int_eq(ringBufferPeakOne(&buffer), elements[0]);
   }
}
END_TEST

START_TEST (Get_One_After_Multiple_Insertions)
{     
   RingBuffer buffer;
   uint8_t data[BUFFER_SIZE] = {0xFF};
   uint8_t elements[BUFFER_SIZE] = {0};

   ck_assert_int_eq(ringBufferInit(&buffer, data, BUFFER_SIZE), 1);

   for(uint8_t i=0; i<BUFFER_SIZE; i++) {
        elements[i] = i;
        ck_assert_int_eq(elements[i], i);
   }

   ck_assert_int_eq(ringBufferEmpty(&buffer), 1);

   for(uint8_t i=0; i<BUFFER_SIZE-1; i++) {
        ck_assert_int_eq(ringBufferLenAvailable(&buffer), BUFFER_SIZE-i-1);
        ringBufferAppendOne(&buffer, elements[i]);
        ck_assert_int_eq(ringBufferLen(&buffer), i+1);
        ck_assert_int_eq(ringBufferEmpty(&buffer), 0);
   }

   for(uint8_t i=0; i<BUFFER_SIZE-1; i++) {
        ck_assert_int_eq(ringBufferLen(&buffer), BUFFER_SIZE-i-1);
        ck_assert_int_eq(ringBufferGetOne(&buffer), elements[i]);
   }

   ck_assert_int_eq(ringBufferEmpty(&buffer), 1);
}
END_TEST

START_TEST (Get_Multiple_After_Multiple_Insertions_No_Round)
{     
   RingBuffer buffer;
   uint8_t data[BUFFER_SIZE] = {0xFF};
   uint8_t elements[BUFFER_SIZE] = {0};

   ck_assert_int_eq(ringBufferInit(&buffer, data, BUFFER_SIZE), 1);

   for(uint8_t i=0; i<BUFFER_SIZE; i++) {
        elements[i] = i;
        ck_assert_int_eq(elements[i], i);
   }

   ck_assert_int_eq(ringBufferEmpty(&buffer), 1);

   for(uint8_t i=0; i<BUFFER_SIZE-1; i++) {
        ck_assert_int_eq(ringBufferLenAvailable(&buffer), BUFFER_SIZE-i-1);
        ringBufferAppendOne(&buffer, elements[i]);
        ck_assert_int_eq(ringBufferLen(&buffer), i+1);
        ck_assert_int_eq(ringBufferEmpty(&buffer), 0);
   }

   uint8_t out[BUFFER_SIZE];

   ringBufferGetMultiple(&buffer, out, ringBufferLen(&buffer));
   ck_assert_int_eq(ringBufferLen(&buffer), 0);

   for(uint8_t i=0; i<BUFFER_SIZE-1; i++) {
        ck_assert_int_eq(out[i], elements[i]);
   }

   ck_assert_int_eq(ringBufferEmpty(&buffer), 1);
}
END_TEST

START_TEST (Get_Multiple_After_Multiple_Insertions_Round)
{     
   RingBuffer buffer;
   uint8_t data[BUFFER_SIZE] = {0xFF};
   uint8_t elements[BUFFER_SIZE] = {0};

   ck_assert_int_eq(ringBufferInit(&buffer, data, BUFFER_SIZE), 1);

   for(uint8_t i=0; i<BUFFER_SIZE; i++) {
        elements[i] = i;
        ck_assert_int_eq(elements[i], i);
   }

   /* Simulate Insertions and removals */
   buffer.tail = buffer.head = BUFFER_SIZE/2;

   ck_assert_int_eq(ringBufferEmpty(&buffer), 1);

   ck_assert_int_eq(ringBufferLenAvailable(&buffer), BUFFER_SIZE-1);
   ringBufferAppendMultiple(&buffer, elements, BUFFER_SIZE-1);
   ck_assert_int_eq(ringBufferLen(&buffer), BUFFER_SIZE-1);

   uint8_t out[BUFFER_SIZE];
   ringBufferGetMultiple(&buffer, out, ringBufferLen(&buffer));
   ck_assert_int_eq(ringBufferLen(&buffer), 0);

   for(uint8_t i=0; i<BUFFER_SIZE-1; i++) {
        ck_assert_int_eq(out[i], elements[i]);
   }

   ck_assert_int_eq(ringBufferEmpty(&buffer), 1);
}
END_TEST

Suite * get_buffer_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Get Data from Buffer");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, Peak_One_After_Multiple_Insertions);
    tcase_add_test(tc_core, Get_One_After_Multiple_Insertions);
    tcase_add_test(tc_core, Get_Multiple_After_Multiple_Insertions_No_Round);
    tcase_add_test(tc_core, Get_Multiple_After_Multiple_Insertions_Round);

    suite_add_tcase(s, tc_core);

    return s;
}