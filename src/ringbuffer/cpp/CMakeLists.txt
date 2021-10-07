set(SRC
  "ringbufferwrapper.cpp"
 )

set(HEADERS
  "ringbufferwrapper.h"
)

add_library(cpp_ringbuffer ${SRC})
target_link_libraries(cpp_ringbuffer c_ringbuffer)
target_include_directories(cpp_ringbuffer PUBLIC "../../")

add_executable(example "main.cpp" ${SRC})
target_link_libraries(example cpp_ringbuffer)

export(TARGETS cpp_ringbuffer FILE ${CMAKE_SOURCE_DIR}/exported/cpp_ringbuffer.cmake)