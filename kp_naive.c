#include <stdio.h>
#include <stdlib.h>
#include "kp_naive.h"

/************* Naive approach to the O-1 Knapsack problem *************/

/* Utility function to return the max of two integers */
int max(int a, int b)
{
    return (a > b) ? a : b;
}

int knapsack_naive(int W, int wt[], int val[], int n)
{
    // Base Case
    if (n == 0 || W == 0)
    {
        return 0;
    }

    if (wt[n - 1] > W)
    {
        return knapsack_naive(W, wt, val, n - 1);
    }
    else
    {
        return max(val[n - 1] + knapsack_naive(W - wt[n - 1], wt, val, n - 1), knapsack_naive(W, wt, val, n - 1));
    }
}