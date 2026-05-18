.PHONY: run clean
CFLAGS = -fsanitize=address -g

all: run

main: main.o forwardlist.o
	g++ $(CFLAGS) main.o forwardlist.o -o main

main.o: main.cpp
	g++ $(CFLAGS) -c main.cpp

forwardlist.o: forwardlist.cpp
	g++ $(CFLAGS) -c forwardlist.cpp

run: main
	./main

clean:
	rm -f *.o main
