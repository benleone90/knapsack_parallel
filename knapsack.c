#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include "knapsack.h"

int main(int argc, char *argv[])
{
    int OPTION;
    struct timespec time_start, time_stop;
    float time_stamp[OPTIONS][NUM_TESTS];
    int i, n, x, alloc_size;

    x = NUM_TESTS - 1;
    alloc_size = A * x * x + B * x + C;

    list_ptr list0 = new_list(alloc_size);
    printf("Knapsack Problem");
    OPTION = 0;
    printf("\nNaive Approach\n");
    for (x = 0; x < NUM_TESTS && (n = A * x * x + B * x + C, n <= alloc_size); x++)
    {
        printf("iter %d length = %d\n", x, n);
        init_list(list0, n);
        clock_gettime(CLOCK_REALTIME, &time_start);
        printf("Highest Value: %d\n", knapsack_naive(WEIGHT, list0, n));
        clock_gettime(CLOCK_REALTIME, &time_stop);
        time_stamp[OPTION][x] = interval(time_start, time_stop);
    }

    OPTION++;
    printf("\nNaive Approach w/ Memorization\n");
    for (x = 0; x < NUM_TESTS && (n = A * x * x + B * x + C, n <= alloc_size); x++)
    {
        printf("iter %d length = %d\n", x, n);
        init_list(list0, n);
        clock_gettime(CLOCK_REALTIME, &time_start);
        printf("Highest Value: %d\n", knapsack_naive_mem(WEIGHT, list0, n));
        clock_gettime(CLOCK_REALTIME, &time_stop);
        time_stamp[OPTION][x] = interval(time_start, time_stop);
    }

    OPTION++;
    printf("\nDynamic Programming Approach\n");
    for (x = 0; x < NUM_TESTS && (n = A * x * x + B * x + C, n <= alloc_size); x++)
    {
        printf("iter %d length = %d\n", x, n);
        init_list(list0, n);
        clock_gettime(CLOCK_REALTIME, &time_start);
        printf("Highest Value: %d\n", knapsack_dynamic(WEIGHT, list0, n));
        clock_gettime(CLOCK_REALTIME, &time_stop);
        time_stamp[OPTION][x] = interval(time_start, time_stop);
    }

    OPTION++;
    printf("\nOpenMP Dynamic Programming Approach\n");
    detect_threads_setting();
    for (x = 0; x < NUM_TESTS && (n = A * x * x + B * x + C, n <= alloc_size); x++)
    {
        printf("iter %d length = %d\n", x, n);
        init_list(list0, n);
        clock_gettime(CLOCK_REALTIME, &time_start);
        printf("Highest Value: %d\n", knapsack_dynamic(WEIGHT, list0, n));
        clock_gettime(CLOCK_REALTIME, &time_stop);
        time_stamp[OPTION][x] = interval(time_start, time_stop);
    }
    printf("size, naive(ms), naive_mem(ms), dynamic(ms), dynamic_omp(ms)\n");
    {
        for (i = 0; i < NUM_TESTS; i++)
        {
            printf("%4d", A * i * i + B * i + C);
            for (OPTION = 0; OPTION < OPTIONS; OPTION++)
            {
                printf(", %10.4g", time_stamp[OPTION][i] * 1000);
            }
            printf("\n");
        }
    }
    return 0;
}

list_ptr new_list(int length)
{
    list_ptr result = (list_ptr)malloc(sizeof(list));
    if (!result)
    {
        printf("\nCouldn't allocate storage\n");
        exit(EXIT_FAILURE);
    }
    if (length > 0)
    {
        int *wgt = (int *)calloc(length, sizeof(int));
        int *val = (int *)calloc(length, sizeof(int));
        if (!wgt && !val)
        {
            free((void *)result);
            printf("\nCouldn't allocate storage\n");
            exit(EXIT_FAILURE);
        }
        result->weight = wgt;
        result->value = val;
    }
    else
    {
        result->weight = NULL;
        result->value = NULL;
    }
    return result;
}

int init_list(list_ptr lp, int length)
{
    int i, j;
    srand(123);
    if (length > 0)
    {
        for (i = 0; i < length; i++)
        {
            srand(i);
            lp->weight[i] = (rand() % (MAXW - MINW + 1)) + MINW;
            for (j = 0; j < length; j++)
            {
                srand(i + j);
                lp->value[j] = (rand() % (MAXV - MINV + 1)) + MINV;
            }
        }
        return 0;
    }
    else
    {
        return 1;
    }
}

/************* Naive approach to the O-1 Knapsack problem *************/

int knapsack_naive(int W, list_ptr lp, int n)
{
    // Base Case
    if (n == 0 || W == 0)
    {
        return 0;
    }

    if (lp->weight[n - 1] > W)
    {
        return knapsack_naive(W, lp, n - 1);
    }
    else
    {
        return max(lp->value[n - 1] + knapsack_naive(W - lp->weight[n - 1], lp, n - 1), knapsack_naive(W, lp, n - 1));
    }
}

/************* Naive approach w/ memorization to the O-1 Knapsack problem *************/
int knapsack_naive_mem(int W, list_ptr lp, int n)
{
    int i, j;
    int **dp;
    dp = malloc(n * sizeof(int *));

    for (i = 0; i < n; i++)
    {
        dp[i] = malloc((W + 1) * sizeof(int));
    }

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < W + 1; j++)
        {
            dp[i][j] = -1;
        }
    }
    return knapsack_rec(W, lp, n - 1, dp);
}

/************* Dynamic programming approach to the O-1 Knapsack problem *************/

int knapsack_dynamic(int W, list_ptr lp, int n)
{
    int i, w;
    int K[n + 1][W + 1];

    // Build table K[][] in bottom up manner
    for (i = 0; i <= n; i++)
    {
        for (w = 0; w <= W; w++)
        {
            if (i == 0 || w == 0)
            {
                K[i][w] = 0;
            }
            else if (lp->weight[i - 1] <= w)
            {
                K[i][w] = max(lp->value[i - 1] + K[i - 1][w - lp->weight[i - 1]], K[i - 1][w]);
            }
            else
            {
                K[i][w] = K[i - 1][w];
            }
        }
    }
    return K[n][W];
}

/************* Dynamic Programming with OpenMP approach to the O-1 Knapsack problem *************/

int knapsack_dynamic_omp(int W, list_ptr lp, int n)
{
    int i, w;
    int K[n + 1][W + 1];

    // Build table K[][] in bottom up manner
#pragma omp parallel shared(K) private(i, w)
    {
        for (i = 0; i <= n; i++)
        {
#pragma omp for
            for (w = 0; w <= W; w++)
            {
                if (i == 0 || w == 0)
                {
                    K[i][w] = 0;
                }
                else if (lp->weight[i - 1] <= w)
                {
                    K[i][w] = max(lp->value[i - 1] + K[i - 1][w - lp->weight[i - 1]], K[i - 1][w]);
                }
                else
                {
                    K[i][w] = K[i - 1][w];
                }
            }
        }
    }
    return K[n][W];
}