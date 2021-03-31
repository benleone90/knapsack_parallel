CC=gcc

default: knapsack.c knapsack.h
	$(CC) knapsack.c knapsack.h -o knapsack.out

clean:
	rm knapsack