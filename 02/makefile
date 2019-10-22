CC = g++

GFLAGS = -c --std=c++14 -02

all: alloc

alloc: main.cpp LinearAllocator.h
	$(CC) $(CFLAGS) -o alloc main.cpp LinearAllocator.h

run: alloc
	./alloc $(args)

test: alloc
	python3 ./test.py

clean:
	rm -rf *.o alloc
