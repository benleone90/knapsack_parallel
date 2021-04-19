#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

/* Macro definitions */
#define CPNS 3.0
#define OPTIONS 4
#define A 1
#define B 5
#define C 10
#define NUM_TESTS 15
#define MINW 1
#define MAXW 100
#define MINV 2
#define MAXV 200
#define WEIGHT 50
#define THREADS 4

typedef struct
{
    int *weight;
    int *value;
} list, *list_ptr;

/************* Time measurement by clock_gettime() *************/
/*
  As described in the clock_gettime manpage (type "man clock_gettime" at
  the shell prompt), a "timespec" is a structure that looks like this:
 
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

/* Utility function to return the max of two integers */
int max(int a, int b)
{
    return (a > b) ? a : b;
}

int knapsack_rec(int W, list_ptr lp, int n, int **dp)
{
    if (n < 0)
    {
        return 0;
    }

    if (dp[n][W] != -1)
    {
        return dp[n][W];
    }

    if (lp->weight[n] > W)
    {
        dp[n][W] = knapsack_rec(W, lp, n - 1, dp);
        return dp[n][W];
    }
    else
    {
        dp[n][W] = max(lp->value[n] + knapsack_rec(W - lp->weight[n], lp, n - 1, dp), knapsack_rec(W, lp, n - 1, dp));
        return dp[n][W];
    }
}

void detect_threads_setting()
{
    int i, ognt;

    /* Find out how many threads OpenMP thinks it is wants to use */
#pragma omp parallel for
    for (i = 0; i < 1; i++)
    {
        ognt = omp_get_num_threads();
    }

    printf("omp's default number of threads is %d\n", ognt);

    /* If this is illegal (0 or less), default to the "#define THREADS"
     value that is defined above */
    if (ognt <= 0)
    {
        if (THREADS != ognt)
        {
            printf("Overriding with #define THREADS value %d\n", THREADS);
            ognt = THREADS;
        }
    }

    omp_set_num_threads(ognt);

    /* Once again ask OpenMP how many threads it is going to use */
#pragma omp parallel for
    for (i = 0; i < 1; i++)
    {
        ognt = omp_get_num_threads();
    }
    printf("Using %d threads for OpenMP\n", ognt);
}

list_ptr new_list(int length);
int init_list(list_ptr lp, int length);
int knapsack_naive(int W, list_ptr lp, int n);
int knapsack_naive_mem(int W, list_ptr lp, int n);
int knapsack_dynamic(int W, list_ptr lp, int n);
int knapsack_dynamic_omp(int W, list_ptr lp, int n);

#endif