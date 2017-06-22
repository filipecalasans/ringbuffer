
#LIBS = -pthread -lcheck_pic -pthread -lrt -lm -lsubunit
#LIB_DIR=usr/lib
#LDFLAGS=-L$(LIB_DIR) $(LIBS)

OBJDIR=.

CSOURCES = $(wildcard ../src/*.c)
CSOURCES += $(wildcard *.cpp)

CCOMPILER=g++

all: wrapper

wrapper: $(CSOURCES:.c=.o)
	$(CCOMPILER) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CCOMPILER) -c $< $(CFLAGS) -o $(OBJDIR)/$@

clean:
	-rm -f *.o wrapper *~
	-rm -f ../src/*.o *~

remade:
	$(MAKE) clean
	$(MAKE)

-include $(CSOURCES:.c:.d) $(CSOURCES:.cpp:.d)

%.d: %.d
	gcc $< -MM -MT '$*.o $*.d' -MD $(CFLAGS)
