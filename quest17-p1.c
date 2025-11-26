#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "misc.h"

#define MAXGRIDSIDE 31
#define BUFLEN      50
#define RADIUS      10
#define RADIUSSQR   (RADIUS * RADIUS) 



int main()
{
    char buffer[BUFLEN];
    FILE *fp = fopen("inputs/everybody_codes_e2025_q17_p1.txt", "r");
    if (!fp) { perror("fopen"); exit(1); }

    myfgets(buffer, BUFLEN, fp);
    const int gridside = strlen(buffer);
    const int gridcenter = gridside >> 1;

    int sum = 0;
    for (int row = 0; row < gridside; row++) {
        for (int col = 0; col < gridside; col++) {
            char c = buffer[col];
            if ((c != '@') && (pow(col - gridcenter, 2) + pow(row - gridcenter, 2) <= RADIUSSQR))
                sum += c - '0';
        }
        myfgets(buffer, BUFLEN, fp);
    }

    printf("%i\n", sum);

    exit(0);
}

