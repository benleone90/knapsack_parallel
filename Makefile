CC=gcc

default: knapsack.c knapsack.h
	$(CC) knapsack.c knapsack.h -o knapsack

clean:
	rm knapsack