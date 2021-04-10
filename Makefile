CC=gcc

default: main.o kp_dynamic.o kp_naive.o
	$(CC) main.o kp_dynamic.o kp_naive.o -o knapsack.out

kp_naive.o: kp_naive.c kp_naive.h
	$(CC) -c kp_naive.c

kp_dynamic.o: kp_dynamic.c kp_dynamic.h
	$(CC) -c kp_dynamic.c

main.o: main.c main.h
	$(CC) -c main.c

clean:
	rm knapsack.out *.o *.gch