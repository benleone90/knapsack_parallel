#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Macro definitions */
#define CPNS 3.0
#define OPTIONS 2
#define A 1
#define B 1
#define C 10
#define NUM_TESTS 10
#define MINW 1
#define MAXW 100
#define MINV 2
#define MAXV 200
#define WEIGHT 50

typedef struct
{
    int *weight;
    int *value;
    int length;

} list, *list_ptr;

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

list_ptr new_list(int length);
int init_list(list_ptr lp, int length);
int max(int a, int b);
int knapsack_naive(int W, list_ptr lp, int n);
int knapsack_dynamic(int W, list_ptr lp, int n);
