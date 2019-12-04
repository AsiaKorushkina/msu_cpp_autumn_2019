CC = g++

GFLAGS = -c --std=c++14 -02 

all: threadpool ttest

threadpool: main.cpp ThreadPool.h
	$(CC) $(CFLAGS) -o threadpool main.cpp ThreadPool.h -lpthread

run: threadpool
	./threadpool

ttest: test.cpp ThreadPool.h
	$(CC) $(CFLAGS) -o test test.cpp ThreadPool.h -lpthread

test: ttest
	./test

clean:
	rm -rf *.o threadpool test
