CC = g++

GFLAGS = -c --std=c++14 -02

all: bigint ttest

bigint: main.cpp BigInt.h
	$(CC) $(CFLAGS) -o bigint main.cpp BigInt.h

run: bigint
	./bigint

ttest: test.cpp BigInt.h
	$(CC) $(CFLAGS) -o test test.cpp BigInt.h

test: ttest
	./test

clean:
	rm -rf *.o bigint test
