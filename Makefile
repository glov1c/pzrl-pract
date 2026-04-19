.PHONY: run clean

all: run

main: main.o mincircle.o
	g++ main.o mincircle.o -o main

main.o: main.cpp
	g++ -c main.cpp

mincircle.o: mincircle.cpp
	g++ -c mincircle.cpp

run: main
	./main

clean:
	rm -f *.o main
