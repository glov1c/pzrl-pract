.PHONY: run clean

all: run

main: main.o min_circle.o
	g++ main.o min_circle.o -o main

main.o: main.cpp
	g++ -c main.cpp

mincircle.o: min_circle.cpp
	g++ -c min_circle.cpp

run: main
	./main

clean:
	rm -f *.o main
