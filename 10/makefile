CC = g++

GFLAGS = -c --std=c++14 -02 

all: url

url: url.cpp
	$(CC) $(CFLAGS) -o url url.cpp 

run: url
	./url

clean:
	rm -rf *.o url
