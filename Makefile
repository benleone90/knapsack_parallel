CC=gcc
FLAGS=-Wall -O1 -fopenmp -lpthread -lm -lrt

default: knapsack.c knapsack.h
	$(CC) $(FLAGS) knapsack.c knapsack.h -o knapsack.out

clean:
	rm knapsack.out