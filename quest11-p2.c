#include <stdlib.h>
#include <stdio.h>
#include "misc.h"

#define NCOLS 60
#define BUFSIZE 16



int checksum(int columns[NCOLS]);

int main()
{
    int columns[NCOLS];
    char buffer[BUFSIZE];

    FILE *fp = fopen("inputs/everybody_codes_e2025_q11_p2.txt", "r");
    for (int i = 0; i < NCOLS; i++) {
        myfgets(buffer, BUFSIZE, fp);
        columns[i] = atoi(buffer);
    }

    int movescnt;
    int round = 0;

    // first phase
    do {
        movescnt = 0;
        for (int i = 0; i < NCOLS - 1; i++) {
            if (columns[i + 1] < columns[i]) {
                columns[i + 1]++;
                columns[i]--;
                movescnt++;
            }
        }

        if (movescnt)
            round++;

    } while (movescnt != 0);

    // second phase
    do {
        movescnt = 0;
        for (int i = 0; i < NCOLS - 1; i++) {
            if (columns[i + 1] > columns[i]) {
                columns[i + 1]--;
                columns[i]++;
                movescnt++;
            }
        }

        if (movescnt)
            round++;

    } while (movescnt != 0);

    printf("%i\n", round);

    exit(0);
}




int checksum(int columns[NCOLS])
{
    int sum = 0;
    for (int i = 0; i < NCOLS; i++)
        sum += (i + 1) * columns[i];
    return sum;
}

