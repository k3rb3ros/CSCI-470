CC=gcc
INCLUDES=
CFLAGS=-O0 -std=c99 $(INCLUDES) -Wall -Wextra
LPATHS=
LDFLAGS:=
SOURCES=forkbomb.c
OBJECTS=$(SOURCES:.c=.o)
BINARY="=^_^="
all: $(BINARY) $(OBJECTS)
.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(BINARY): $(OBJECTS)
	 $(CC) $(CFLAGS) $(LPATHS) $(OBJECTS) -o $@ $(LDFLAGS)

clean:
	 rm -rf $(BINARY) $(OBJECTS) *.o
