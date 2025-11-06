#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "misc.h"

#define BUFSIZE 300

int compar(const void *a, const void *b);

int main()
{
    char buffer[BUFSIZE];
    int numbers[100];
    //FILE *fp = fopen("inputs/everybody_codes_e2025_q03_p1-test.txt", "r");
    FILE *fp = fopen("inputs/everybody_codes_e2025_q03_p1.txt", "r");
    if (!fp) exit(2);


    myfgets(buffer, BUFSIZE, fp);

    char *str = strtok(buffer, ",");
    int count = 0;
    while (str) {
        numbers[count++] = atoi(str);
        str = strtok(NULL, ",");
    }

    qsort(numbers, count, sizeof(int), compar);

    int prev, sum;
    prev = sum = numbers[0];
    for (int i = 1; i < count; i++) {
        int n = numbers[i];
        if (n != prev) {
            prev = n;
            sum += n;
        }
    }

    printf("%d\n", sum);

    exit(0);
}



int compar(const void *a, const void *b)
{
    return *((int *)a) - *((int *)b);
}

