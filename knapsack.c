#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "knapsack.h"

#define CPNS 3.0

/************* Time measurement by clock_gettime() *************/
/*
  As described in the clock_gettime manpage (type "man clock_gettime" at the
  shell prompt), a "timespec" is a structure that looks like this:
 
        struct timespec {
          time_t   tv_sec;   // seconds
          long     tv_nsec;  // and nanoseconds
        };
 */

double interval(struct timespec start, struct timespec end)
{
    struct timespec temp;
    temp.tv_sec = end.tv_sec - start.tv_sec;
    temp.tv_nsec = end.tv_nsec - start.tv_nsec;
    if (temp.tv_nsec < 0)
    {
        temp.tv_sec = temp.tv_sec - 1;
        temp.tv_nsec = temp.tv_nsec + 1000000000;
    }
    return (((double)temp.tv_sec) + ((double)temp.tv_nsec) * 1.0e-9);
}
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

/************* Dynamic programming approach to the O-1 Knapsack problem *************/

int knapsack_dynamic(int W, int wt[], int val[], int n)
{
    int i, w;
    int K[n + 1][W + 1];

    // Build table K[][] in bottom up manner
    for (i = 0; i <= n; i++)
    {
        for (w = 0; w <= W; w++)
        {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (wt[i - 1] <= w)
                K[i][w] = max(val[i - 1] + K[i - 1][w - wt[i - 1]],
                              K[i - 1][w]);
            else
                K[i][w] = K[i - 1][w];
        }
    }
    return K[n][W];
}

int main()
{
    struct timespec time_start, time_stop;
    double time_stamp[2];
    int val[] = {60, 100, 120};
    int wt[] = {10, 20, 30};
    int W = 50;
    int n = sizeof(val) / sizeof(val[0]);
    clock_gettime(CLOCK_REALTIME, &time_start);
    printf("%d\n", knapsack_naive(W, wt, val, n));
    clock_gettime(CLOCK_REALTIME, &time_stop);
    time_stamp[0] = interval(time_start, time_stop);
    clock_gettime(CLOCK_REALTIME, &time_start);
    printf("%d\n", knapsack_dynamic(W, wt, val, n));
    clock_gettime(CLOCK_REALTIME, &time_stop);
    time_stamp[1] = interval(time_start, time_stop);
    for (size_t i = 0; i < 2; i++)
    {
        printf("%.10f\n", time_stamp[i]);
    }

    return 0;
}