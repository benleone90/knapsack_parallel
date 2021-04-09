#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "kp_naive.h"
#include "kp_dynamic.h"
#include "generator.h"

int main(int argc, char *argv[])
{
    int OPTION;
    struct timespec time_start, time_stop;
    float time_stamp[2];
    int wt[ITEMS];
    int val[ITEMS];
    generator(wt, val);
    int n = sizeof(val) / sizeof(val[0]);
    printf("Knapsack Problem\nNumber of Items: %d\n", n);

    OPTION = 0;
    printf("\nNaive Approach\n");
    clock_gettime(CLOCK_REALTIME, &time_start);
    printf("%d\n", knapsack_naive(WEIGHT, wt, val, ITEMS));
    clock_gettime(CLOCK_REALTIME, &time_stop);
    time_stamp[OPTION] = interval(time_start, time_stop);

    OPTION++;
    printf("\nDynamic Programming Approach\n");
    clock_gettime(CLOCK_REALTIME, &time_start);
    printf("%d\n", knapsack_dynamic(WEIGHT, wt, val, ITEMS));
    clock_gettime(CLOCK_REALTIME, &time_stop);
    time_stamp[OPTION] = interval(time_start, time_stop);
    for (size_t i = 0; i < 2; i++)
    {
        printf("%.9f\n", time_stamp[i]);
    }
    return 0;
}