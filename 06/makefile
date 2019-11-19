CC = g++

GFLAGS = -c --std=c++14 -02

all: format ttest 

format: main.cpp format.h
	$(CC) $(CFLAGS) -o format main.cpp format.h

run: format
	./format

ttest: test.cpp format.h
	$(CC) $(CFLAGS) -o test test.cpp format.h

test: ttest
	./test

clean:
	rm -rf *.o format test
