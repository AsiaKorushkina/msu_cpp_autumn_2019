CC = g++

GFLAGS = -c --std=c++14 -02

all: vector ttest 

vector: main.cpp vector.h
	$(CC) $(CFLAGS) -o vector main.cpp vector.h

run: vector
	./vector

ttest: test.cpp vector.h
	$(CC) $(CFLAGS) -o test test.cpp vector.h

test: ttest
	./test

clean:
	rm -rf *.o vector test
