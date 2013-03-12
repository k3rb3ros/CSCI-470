CC=gcc
INCLUDES=
CFLAGS=-O2 -std=c99 $(INCLUDES) -Wall -Wextra
LPATHS=
LDFLAGS:=
SOURCES=exec_me.c
OBJECTS=$(SOURCES:.c=.o)
BINARY=exec_me

all: $(BINARY) $(OBJECTS)
.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(BINARY): $(OBJECTS)
	 $(CC) $(CFLAGS) $(LPATHS) $(OBJECTS) -o $@ $(LDFLAGS)

clean:
	 rm -rf $(BINARY) $(OBJECTS) *.o
