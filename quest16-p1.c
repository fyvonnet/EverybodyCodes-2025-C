#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "misc.h"

#define NCOLUMNS    90
#define BUFLEN      70



int main()
{
    char buffer[BUFLEN];
    FILE *fp = fopen("inputs/everybody_codes_e2025_q16_p1.txt", "r");
    if (!fp) { perror("fopen"); exit(1); }
    myfgets(buffer, BUFLEN, fp);
    fclose(fp);

    char *token = strtok(buffer, ",");
    int sum = 0;
    while (token) {
            div_t result = div(NCOLUMNS, atoi(token));
            sum += result.quot;
            token = strtok(NULL, ",");
    }

    printf("%i\n", sum);

    exit(0);
}

