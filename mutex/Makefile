CC=g++
INCLUDES=
CFLAGS=-O0 $(INCLUDES) -Wall -Wextra
LPATHS=
LDFLAGS= -lpthread
SOURCES=threading.cpp
OBJECTS=$(SOURCES:.cpp=.o)
BINARY=threading_n_stuff

all: $(BINARY) $(OBJECTS)
.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(BINARY): $(OBJECTS)
	 $(CC) $(CFLAGS) $(LPATHS) $(OBJECTS) -o $@ $(LDFLAGS)

clean:
	 rm $(BINARY) *.o
