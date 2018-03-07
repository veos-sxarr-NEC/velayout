CC = gcc
all:
	$(CC) -c -I ../src -o test.o test.c
	$(CC) -L ../src/.libs -lvelayout -llog4c -Wl,-rpath=../src/.libs test.o
clean:
	rm -f *.o a.out
