CC = g++

GFLAGS = -c --std=c++14 -02

all: matrix ttest

matrix: main.cpp Matrix.h
	$(CC) $(CFLAGS) -o matrix main.cpp Matrix.h

run: matrix
	./matrix

ttest: test.cpp Matrix.h
	$(CC) $(CFLAGS) -o test test.cpp Matrix.h

test: ttest
	./test

clean:
	rm -rf *.o matrix test
