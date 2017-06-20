#include "ringbuffer.h"

char data[1024];

int main(int argc, char *argv[]) {

   RingBuffer buffer;
   ringBufferInit(&buffer, data, 1023);

   return 0;
}