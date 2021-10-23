# Ring Buffer

Static size Ring Buffer implementation in C with minimal dependencies and tailored to be fast and have small footprint.

This library privileges performance over safety, therefore we do not make safety checks before manipulating the buffer in the C implementation, and very minimal on C++ wrapper. Also, the implemenation is meant to be used on embedded devices, bare-metal if required and therefore it won't raise exceptions. This library is useful for applications such as packet queue, I/O queue, embedded applications that needs to stream real time acquired data.

# How to Use:

You can import this repo as a submodule in your project, add the project subdirectory to your CMake defintiion and link to the following libraries:

```
add_subdirectory(your/project/third-party/ringbuffer)

# C library
target_link_libraries(your_target_name c_ringbuffer)

# C++ library
target_link_libraries(your_cpp_target_name cpp_ringbuffer)
```

Or you can copy only the directory `ringbuffer`, and add the source and headers to
your build definition.

## Using the RingBuffer C library

```C
   #include <ringbuffer/c/ringbuffer.h>

   #define STATIC_BUFFER_SIZE 512

   static uint8_t data[STATIC_BUFFER_SIZE];

   int main(){

      RingBuffer buffer;
      ringBufferInit(&buffer, data, BUFFER_SIZE);

      // Append multiples bytes at one time
      uint8_t new_elem[3] = {1, 10, 20};
      ringBufferAppendMultiple(&buffer, new_elem, 3);

      // You can inspect multiples bytes without removing 
      uint8_t inspect[2];
      ringBufferPeekMultiple(&buffer, inspect, 2);

      // You can discard multiples
      ringBufferDiscardMultiple(&buffer, 2);
      
      uint32_t freeSpace = ringBufferFreeSpace(&buffer)l
      uint32_t size = ringBufferLen(&buffer);
      uint32_t capacity = ringBufferLen(&buffer); 

      return 0;
   }

```

If you are working in a memory constrained environment, you may want to 
use statically allocated memory as internal data buffer, as we show in the example above.

However, you are not doomed to this approach. The library is flexible to allow
you to use dynamically allocated memory if you want.

## Using the C++ RingBuffer library

You can find the **RingBufferWrapper** implementation in the folder **src/ringbuffer/cpp/**. It provides a C++ class wrapper for the C implementation.

```C++
#include <ringbuffer/cpp/ringbufferwrapper.h>

#include <iostream>

#define ADD_SIZE 10

int main(int argc, char *argv[]) {

   std::cout << "Runnign Ring-Buffer wrapper main()\n";

   RingBufferWrapper ringBuffer(2048);

   if(!ringBuffer.isValid()) {
      std::cout << "Couldn`t allocate the Ring Buffer\n";
      return -1; 
   }

   uint8_t values[ADD_SIZE];

   for(int i=0; i<ADD_SIZE; i++) { 
      values[i] = i*10;
   }

   uint32_t len = ringBuffer.appendMultiple(values, ADD_SIZE);
   std::cout << "Inserted: " << len << ", Tryied: " 
             << ADD_SIZE << ", Len Read: " << ringBuffer.length() 
             << " Len Available: " << ringBuffer.freeSpace() << "\n";

   std::cout << "Array Values: ";

   while(!ringBuffer.empty()) { 
      std::cout << (int)ringBuffer.getOne() << " ";
   }
   std::cout << "\n";

   std::cout << "Len Read: " << ringBuffer.length() 
             << " Len Available: " << ringBuffer.freeSpace() << "\n";

   return 0;
}

```

The example above creates a RingBuffer of size 2048, inserts 10 elements into the ring buffer, and
consume them until the buffer is empty.

# Tests

The C library was unit tested using [CMocka](https://github.com/clibs/cmocka), which is provided as a submodule. Tests are automatically compiled and you can run them from the build output directory as follow:

```
# Compile
$ ./build.sh

# Run
$ cd out/
$ tests/c_ringbuffer_test
```
