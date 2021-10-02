set(SRC
  "appendBufferTest.c"
  "getBufferTest.c"
  "initBufferTest.c"
 )

set(HEADERS
  "appendBufferTest.h"
  "getBufferTest.h"
  "initBufferTest.h"
)

add_executable(c_ringbuffer_test "tests.c" ${SRC})
target_link_libraries(c_ringbuffer_test c_ringbuffer cmocka::cmocka)

add_test(test c_ringbuffer_test)
