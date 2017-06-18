all: ringbuffer

ringbuffer: main.o ringbuffer.o
	gcc -o ringbuffer main.o ringbuffer.o

ringbuffer.o: main.c ringbuffer.c ringbuffer.h
	gcc -c ringbuffer.c

clean:
	-rm -f *.o ringbuffer *~