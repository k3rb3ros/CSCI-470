CC=g++
INCLUDES=
CFLAGS=-O0 $(INCLUDES) -Wall -Wextra
LPATHS=
LDFLAGS:=
SOURCES=proc_share.cpp
OBJECTS=$(SOURCES:.c=.o)
BINARY=proc_share

all: $(BINARY) $(OBJECTS)
.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(BINARY): $(OBJECTS)
	 $(CC) $(CFLAGS) $(LPATHS) $(OBJECTS) -o $@ $(LDFLAGS)

clean:
	 rm -rf $(BINARY) $(OBJECTS) *.o
