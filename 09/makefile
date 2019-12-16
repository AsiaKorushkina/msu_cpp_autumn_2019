CC = g++

GFLAGS = -c --std=c++14 -02 

all: sort ttest

sort: sort.cpp
	$(CC) $(CFLAGS) -o sort sort.cpp -lpthread

run: sort
	./sort

gen_data: gen_data.cpp
	$(CC) $(CFLAGS) -o gen_data gen_data.cpp

gen_data_run: gen_data
	./gen_data

ttest: check_sort.cpp
	$(CC) $(CFLAGS) -o test check_sort.cpp

test: ttest
	./test

clean:
	rm -rf *.o sort gen_data test
