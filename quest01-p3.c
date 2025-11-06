#include <stdlib.h>
#include <stdio.h>
#include "misc.h"

#define NAMESLEN    270
#define INSTRSLEN   250

int main()
{
    FILE *fp;
    char names[NAMESLEN];
    char instrs[INSTRSLEN];
    char *namesptr[32];
    char *ptr = names;

    fp = fopen("inputs/everybody_codes_e2025_q01_p3.txt", "r");
    //fp = fopen("inputs/everybody_codes_e2025_q01_p3-test.txt", "r");
    myfgets(names,  NAMESLEN,  fp);
    myfgets(instrs, INSTRSLEN, fp); // skip empty line
    myfgets(instrs, INSTRSLEN, fp);
    fclose(fp);

    namesptr[0] = ptr;
    int c = *ptr;
    int i = 1;
    int namescnt = 1;
    while (c != '\0') {
        if (c == ',') {
            *ptr = '\0';
            namesptr[i++] = ptr + 1;
            namescnt++;
        }
        c = *(++ptr);
    }

    ptr = instrs;
    c = *ptr;
    i = 0;

    while (1)
    {
        int move;
        switch(c) {
            case 'L':
                move = -1;
                break;
            case 'R':
                move = 1;
                break;
            default:
                fprintf(stderr, "Unknown move: %c\n", c);
                exit(EXIT_FAILURE);
        }

        i = atoi(++ptr);
        i *= move;
        i = modulo(i, namescnt);

        char *tmp = namesptr[0];
        namesptr[0] = namesptr[i];
        namesptr[i] = tmp;

        c = *(++ptr);
        while (c && c != ',')
            c = *(++ptr);

        if (!c) break;

        c = *(++ptr);
    }

    printf("%s\n", namesptr[0]);

    exit(EXIT_SUCCESS);
}
