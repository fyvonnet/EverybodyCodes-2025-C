#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "misc.h"

#define BUFLEN   10

int main()
{
    char buffer[BUFLEN];
    int inputlen = 1;

    FILE *fp = fopen("inputs/everybody_codes_e2025_q13_p1.txt", "r");

    char *ret = myfgets(buffer, BUFLEN, fp);
    while (ret) {
        ret = myfgets(buffer, BUFLEN, fp);
        inputlen++;
    }

    int input[inputlen];
    input[0] = 1;

    rewind(fp);

    bool cwise = true;
    int cwise_index = 1;
    int ccwise_index = inputlen - 1;
    for (int i = 1; i < inputlen; i++) {
        myfgets(buffer, BUFLEN, fp);
        if (cwise)
            input[cwise_index++] = atoi(buffer);
        else
            input[ccwise_index--] = atoi(buffer);
        cwise = !cwise;
    }

    printf("%i\n", input[2025 % inputlen]);

    exit(0);
}

