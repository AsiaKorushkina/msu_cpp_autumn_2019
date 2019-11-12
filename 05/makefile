CC = g++

GFLAGS = -c --std=c++14 -02

all: serializer ttest

serializer: main.cpp Serializer.h
	$(CC) $(CFLAGS) -o serializer main.cpp Serializer.h

run: serializer
	./serializer

ttest: test.cpp Serializer.h
	$(CC) $(CFLAGS) -o test test.cpp Serializer.h

test: ttest
	./test

clean:
	rm -rf *.o serializer test
