
make: main

main: main.o
	g++ -g -Wall -O2 -std=c++11 main.o -o main

main.o: main.cpp
	g++ -g -Wall -O2 -std=c++11 main.cpp -c

clean:
	rm -f *.o main
