CC=g++
INCLUDES=
CFLAGS=-O0 $(INCLUDES) -Wall -Wextra
LPATHS=
LDFLAGS=-lSDL -lSDL_ttf -lpthread
SOURCES=mutex.cpp
OBJECTS=$(SOURCES:.cpp=.o)
BINARY=mutex_n_stuff

all: $(BINARY) $(OBJECTS)
.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(BINARY): $(OBJECTS)
	 $(CC) $(CFLAGS) $(LPATHS) $(OBJECTS) -o $@ $(LDFLAGS)

clean:
	 rm $(BINARY) *.o
