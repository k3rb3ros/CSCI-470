CC=g++
INCLUDES=
CFLAGS=-O0 $(INCLUDES) -Wall -Wextra
LPATHS=
LDFLAGS:=
SOURCES=threading.cpp
OBJECTS=$(SOURCES:.c=.o)
BINARY=threading

all: $(BINARY) $(OBJECTS)
.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(BINARY): $(OBJECTS)
	 $(CC) $(CFLAGS) $(LPATHS) $(OBJECTS) -o $@ $(LDFLAGS)

clean:
	 rm $(BINARY) $(OBJECTS) *.o
