C=g++
CFLAGS=-Wall -c -g -fms-extensions $(shell sdl2-config --cflags)
LDFLAGS=$(shell sdl2-config --libs) -lm
SOURCES=$(shell find . -name "*.cpp")
OBJECTS=$(SOURCES:.cpp=.o)
	EXECUTABLE=sgl

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
		$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
		$(CC) $(CFLAGS) $< -o $@
