CC=gcc
INCLUDES=
CFLAGS=-O0 -std=c99 $(INCLUDES) -Wall -Wextra
LPATHS=
LDFLAGS:=
SOURCES=fork_n_stuff.c
OBJECTS=$(SOURCES:.c=.o)
BINARY=fork_n_stuff

all: $(BINARY) $(OBJECTS)
.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(BINARY): $(OBJECTS)
	 $(CC) $(CFLAGS) $(LPATHS) $(OBJECTS) -o $@ $(LDFLAGS)

clean:
	 rm $(BINARY) $(OBJECTS) *.o
