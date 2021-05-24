#C=g++
C=g++-8
#C=clang-9
CFLAGS=-Wall -c -g $(shell sdl2-config --cflags) -std=c++11
LDFLAGS=$(shell sdl2-config --libs) -lm -std=c++11 -lstdc++
RELFLAGS=-s -Ofast -flto -funroll-loops
SOURCES=$(shell find . -name "*.cpp")
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=sgl

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

release: $(SOURCES)
	$(CC) -Wall -c $(RELFLAGS) `sdl2-config --cflags` -std=c++11 $(SOURCES)
	$(CC) $(LDFLAGS) $(RELFLAGS) $(OBJECTS) -o $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)
