#include "ringbufferwrapper.h"

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
   std::cout << "Inserted: " << len << ", Tried: " 
             << ADD_SIZE << ", Len Read: " << ringBuffer.length() 
             << " Len Available: " << ringBuffer.lengthAvailable() << "\n";

   std::cout << "Array Values: ";

   while(!ringBuffer.empty()) { 
      std::cout << (int)ringBuffer.getOne() << " ";
   }
   std::cout << "\n";

   std::cout << "Len Read: " << ringBuffer.length() 
             << " Len Available: " << ringBuffer.lengthAvailable() << "\n";

   return 0;
}
