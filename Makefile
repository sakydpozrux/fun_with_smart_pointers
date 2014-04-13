CXX = g++
CXXFLAGS = -g -Wall -O2 -std=c++11

make: main

main: main.o
	$(CXX) $(CXXFLAGS) main.o -o main

main.o: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -c

clean:
	rm -f *.o main
