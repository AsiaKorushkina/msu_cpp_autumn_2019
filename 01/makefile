CC = g++

GFLAGS = -c --std=c++14 -02

all: calc

calc: calc.cpp
	$(CC) $(CFLAGS) -o calc calc.cpp

run: calc
	./calc $(args)

test: calc
	python3 ./test.py

clean:
	rm -rf *.o calc
