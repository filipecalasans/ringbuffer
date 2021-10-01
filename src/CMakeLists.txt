set(SRC
  "ringbuffer.c"
 )

set(HEADERS
  "ringbuffer.h"
)

add_library(c_ringbuffer ${SRC})
target_include_directories(c_ringbuffer PUBLIC "../")

export(TARGETS c_ringbuffer FILE ${CMAKE_SOURCE_DIR}/exported/c_ringbuffer.cmake)