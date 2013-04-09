CC=gcc
INCLUDES=
CFLAGS=-std="c99" -O0 $(INCLUDES) -Wall -Wextra
LPATHS=
LDFLAGS=-lpthread
SOURCES=pthread.c
OBJECTS=$(SOURCES:.c=.o)
BINARY=threading_yeah

all: $(BINARY) $(OBJECTS)
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(BINARY): $(OBJECTS)
	 $(CC) $(CFLAGS) $(LPATHS) $(OBJECTS) -o $@ $(LDFLAGS)

clean:
	 rm $(BINARY) *.o
