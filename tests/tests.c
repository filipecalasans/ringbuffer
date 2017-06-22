#include <check.h>
#include <stdlib.h>

#include "../src/ringbuffer.h"

#include "initBufferTest.h"
#include "appendBufferTest.h"
#include "getBufferTest.h"

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = init_buffer_suite();
    sr = srunner_create(s);
    
    srunner_add_suite(sr, append_buffer_suite());
    srunner_add_suite(sr, get_buffer_suite());

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);


    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
