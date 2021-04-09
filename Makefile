CC=gcc

default: main.o kp_dynamic.o kp_naive.o generator.o
	$(CC) main.o kp_dynamic.o kp_naive.o generator.o -o knapsack.out

generator.o: generator.c generator.h
	$(CC) -c generator.c

kp_naive.o: kp_naive.c kp_naive.h
	$(CC) -c kp_naive.c

kp_dynamic.o: kp_dynamic.c kp_dynamic.h
	$(CC) -c kp_dynamic.c

main.o: main.c main.h
	$(CC) -c main.c

clean:
	rm knapsack.out *.o *.gch