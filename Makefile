
#LIB_DIR=
#CFLAGS=-I$(INCLUDE_DIR)
#LDFLAGS=-L$(LIB_DIR) $(LIBS)

CSOURCES = $(wildcard *.c)
CCOMPILER=gcc

all: ringbuffer

test: $(CSOURCES:.c=.o)
	+$(MAKE) -C tests
	
ringbuffer: $(CSOURCES:.c=.o)
	$(CCOMPILER) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CCOMPILER) -c $< $(CFLAGS) -o $@

clean:
	-rm -f *.o ringbuffer *~
	-rm -f tests/*.o tests *~

remade:
	$(MAKE) clean
	$(MAKE)

-include $(CSOURCES:.c:.d)

%.d: %.d
	gcc $< -MM -MT '$*.o $*.d' -MD $(CFLAGS)
