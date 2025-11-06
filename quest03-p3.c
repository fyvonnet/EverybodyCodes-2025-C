#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "misc.h"

#define BUFSIZE 30000
#define NCOUNTERS 100

int compar(const void *a, const void *b);

int main()
{
    char buffer[BUFSIZE];
    //FILE *fp = fopen("inputs/everybody_codes_e2025_q03_p3-test.txt", "r");
    FILE *fp = fopen("inputs/everybody_codes_e2025_q03_p3.txt", "r");
    if (!fp) exit(2);
    int counters[NCOUNTERS];

    for (int i = 0; i < NCOUNTERS; i++)
        counters[i] = 0;

    myfgets(buffer, BUFSIZE, fp);

    char *str = strtok(buffer, ",");
    while (str) {
        int n = atoi(str);
        counters[n]++;
        str = strtok(NULL, ",");
    }

    int max = 0;
    for (int i = 0; i < NCOUNTERS; i++)
        if (counters[i] > max)
            max = counters[i];

    printf("%d\n", max);

    exit(0);
}

