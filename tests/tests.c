#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>

#include <cmocka.h>

#include "../src/ringbuffer.h"

#include "initBufferTest.h"
#include "appendBufferTest.h"
#include "getBufferTest.h"

int main(void)
{
    const struct CMUnitTest tests[] = {

        // Init Buffer Test Cases.
        cmocka_unit_test(Init_Buffer_Size_multiple_of_2),
        cmocka_unit_test(Init_Buffer_Size_Not_multiple_of_2),

        // Get Test cases.
        cmocka_unit_test(Peek_One_After_Multiple_Insertions),
        cmocka_unit_test(Get_One_After_Multiple_Insertions),
        cmocka_unit_test(Get_Multiple_After_Multiple_Insertions_No_Round),
        cmocka_unit_test(Get_Multiple_After_Multiple_Insertions_Round),

        // Append test cases.
        cmocka_unit_test(Append_Element_No_Round),
        cmocka_unit_test(Append_Element_Head_In_The_middle),
        cmocka_unit_test(Append_Multiple_Elements_No_Round),
        cmocka_unit_test(Append_Multiple_Elements_Head_In_The_middle),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);;
}
