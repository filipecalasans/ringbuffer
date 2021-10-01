cmake_minimum_required(VERSION 3.1.0)
project(ringbuffer VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_subdirectory(src)
add_subdirectory(cppwrapper)
# add_subdirectory(tests)
