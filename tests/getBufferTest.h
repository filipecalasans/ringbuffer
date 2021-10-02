#ifndef __GET_BUFFER_TEST_H__
#define __GET_BUFFER_TEST_H__

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdlib.h>
#include <setjmp.h>

#include <cmocka.h>

void Peek_One_After_Multiple_Insertions(void** state);
void Get_One_After_Multiple_Insertions(void** state);
void Get_Multiple_After_Multiple_Insertions_No_Round(void** state);
void Get_Multiple_After_Multiple_Insertions_Round(void** state);

#endif