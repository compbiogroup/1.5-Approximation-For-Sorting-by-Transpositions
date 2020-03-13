CXX = g++
CXXFLAGS = -g -Wall -pedantic -O3
SRCS=include/*.cc main.cc

all: main

main: $(SRCS)
	$(CXX) $(CPPFLAGS) $(SRCS) -o main

.PHONY: clean
clean:
	rm -rf main *.o
