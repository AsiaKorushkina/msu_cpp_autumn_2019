CC=g++ 

CFLAGS= -c --std=c++14 -O2

all: my_prog

my_prog: main.o sum_by_rows.o sum_by_col.o 
	$(CC) -o my_prog main.o sum_by_rows.o sum_by_col.o

main.o: main.cpp myfunction.h
	$(CC) $(CFLAGS) main.cpp
sum_by_rows.o: sum_by_rows.cpp myfunction.h
	$(CC) $(CFLAGS) sum_by_rows.cpp

sum_by_col.o: sum_by_col.cpp myfunction.h
	 $(CC) $(CFLAGS) sum_by_col.cpp

run: my_prog
	./my_prog
clean:
	rm -rf *.o my_prog
