# EC527 Project - Spring 2021

## Problem Overview

[Knapsack Problem](https://en.wikipedia.org/wiki/Knapsack_problem):

Given a set of items, each with a weight and a value, determine the number of each item to include in a collection so that the total weight is less than or equal to a given limit and the total value is as large as possible.

In other words, given two integer arrays `val[0..n-1]` and `wt[0..n-1]`, which represent values and weights associated with n items respectively, and given an integer W which represents knapsack capacity, find out the maximum value subset of `val[]` such that sum of the weights of this subset is smaller than or equal to W. You cannot break an item, either pick the complete item or don’t pick it (0-1 property).

## Objective and Analysis

Examine how to use parallel programming techniques with the dynamic programming approach for the 0-1 knapsack problem and examine how much, if any, speedup is achieved by using these techniques.

After implemeting the dynamic programming approach to this problem, OpenMP and POSIX threads (Pthreads) were used for parallelization.

## Setup

- Clone repository and `cd` into the directory.
- Run `make` to generate the `knapsack.out` binary.
- Run `./knapsack.out > results.txt &` to start a background job that will output the results to the text file.
- Run `make clean` to remove the binary or after any edits for testing.

## References

- [Knapsack Problem Wikipedia](https://en.wikipedia.org/wiki/Knapsack_problem)
- [GeeksforGeeks: 0-1 Knapsack Problem | DP-10](https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/)
