#ifndef __APPEND_BUFFER_TEST_H__
#define __APPEND_BUFFER_TEST_H__

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdlib.h>
#include <setjmp.h>

#include <cmocka.h>

void Append_Element_No_Round(void** state);
void Append_Element_Head_In_The_middle(void** state);
void Append_Multiple_Elements_No_Round(void** state);
void Append_Multiple_Elements_Head_In_The_middle(void** state);

#endif