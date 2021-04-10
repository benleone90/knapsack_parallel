CC=gcc
FLAGS=-Wall

default: knapsack.c knapsack.h
	$(CC) $(FLAGS) knapsack.c knapsack.h -o knapsack.out

clean:
	rm knapsack.out