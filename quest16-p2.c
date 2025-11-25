#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "misc.h"

#define MAXCOLUMNS  260
#define BUFLEN      520

long long build(int start);

int target[MAXCOLUMNS];
int wall[MAXCOLUMNS];
int ncolumns;



int main()
{
    char buffer[BUFLEN];
    FILE *fp = fopen("inputs/everybody_codes_e2025_q16_p2.txt", "r");
    if (!fp) { perror("fopen"); exit(1); }
    myfgets(buffer, BUFLEN, fp);
    fclose(fp);

    char *token = strtok(buffer, ",");
    int i = 0;
    while (token) {
        wall[i] = 0;
        target[i++] = atoi(token);
        token = strtok(NULL, ",");
    }
    ncolumns = i;

    printf("%lli\n", build(1));

    exit(0);
}



long long build(int start)
{
    for (int number = start; true; number++) {
        for (int c = number; c <= ncolumns; c += number)
            wall[c - 1]++;

        int nequals = 0;
        bool failed = false;

        for (int c = 0; c < ncolumns; c++)
            if (wall[c] == target[c])
                nequals++;
            else if (wall[c] > target[c]) {
                failed = true;
                break;
            }

        if (!failed) {
            if (nequals == ncolumns)
                return number;
            else
                return number * build(number + 1);
        }

        for (int c = number; c <= ncolumns; c += number)
            wall[c - 1]--;
    }
}

