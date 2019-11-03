
LIBS = -pthread -lcheck_pic -pthread -lrt -lm -lsubunit
LIB_DIR=usr/lib
LDFLAGS=-L$(LIB_DIR) $(LIBS)

OBJDIR=.
CSOURCES = $(wildcard *.c)
CSOURCES += $(wildcard ../src/*.c)

CCOMPILER=gcc

BIN=test

all: test run-test

$(BIN): $(CSOURCES:.c=.o)
	$(CCOMPILER) -o $@ $^ $(LDFLAGS)
	
%.o: %.c
	$(CCOMPILER) -c $< $(CFLAGS) -o $(OBJDIR)/$@

clean:
	-rm -f *.o $(BIN) *~

remade:
	$(MAKE) clean
	$(MAKE)

run-test:
	./$(BIN)

-include $(CSOURCES:.c:.d)

%.d: %.d
	$(CCOMPILER) $< -MM -MT '$*.o $*.d' -MD $(CFLAGS)
