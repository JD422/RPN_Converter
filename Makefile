CC=gcc
CFLAGS=-std=c99 -Wall -I.
LDFLAGS=-std=c99 -Wall
SOURCES=src/rpnconverter.c test/check_rpnconverter.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=rpnconverter
LIBS=-pthread -pthread -lcheck_pic -lrt -lm -lcheck

all: $(SOURCES) $(EXECUTABLE)

test: $(EXECUTABLE)
	./$(EXECUTABLE)
 
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
    
clean:
	$(RM) src/*.o src/*~ test/*.o test/*~ $(EXECUTABLE)
