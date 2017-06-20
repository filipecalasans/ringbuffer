#include "initBufferTest.h"

#include "../src/ringbuffer.h"

#define BUFFER_SIZE 256

START_TEST (Init_Buffer_Size_multiple_of_2)
{     
   RingBuffer buffer;
   uint8_t data[128];
   ck_assert_int_eq(ringBufferInit(&buffer, data, BUFFER_SIZE), 1);
   ck_assert_int_eq(0xFF, buffer.sizeMask);
   ck_assert_int_eq(buffer.tail, 0);
   ck_assert_int_eq(buffer.head, 0);
   ck_assert_ptr_eq(buffer.data, data);
}
END_TEST

START_TEST (Init_Buffer_Size_Not_multiple_of_2)
{     
   RingBuffer buffer;
   uint8_t data[128];
   ck_assert_int_eq(ringBufferInit(&buffer, data, 126), 0);
}
END_TEST

Suite * init_buffer_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Ring Buffer Initialization");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, Init_Buffer_Size_multiple_of_2);
    tcase_add_test(tc_core, Init_Buffer_Size_Not_multiple_of_2);

    suite_add_tcase(s, tc_core);

    return s;
}