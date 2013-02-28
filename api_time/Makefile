###################################
# Makefile for sytem time printer #
###################################
CC=g++
CFLAGS= -O0 -g -Wall -Wextra
LDFLAGS=
SOURCES=get_date.cpp
OBJECTS=$(SOURCES:.cpp=.o)
BINARY=get_date

all: $(BINARY) $(OBJECTS)
.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(BINARY): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

clean: 
	rm -rfv $(BINARY) $(OBJECTS)
