#ifndef __INIT_BUFFER_TEST_H__
#define __INIT_BUFFER_TEST_H__

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdlib.h>
#include <setjmp.h>

#include <cmocka.h>

void Init_Buffer_Size_multiple_of_2(void **state);
void Init_Buffer_Size_Not_multiple_of_2(void **state);

#endif