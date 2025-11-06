#include <stdlib.h>
#include <stdio.h>
#include "misc.h"

#define NAMESLEN    128
#define INSTRSLEN   64

int main()
{
    FILE *fp;
    char names[NAMESLEN];
    char instrs[INSTRSLEN];
    char *namesptr[16];
    char *ptr = names;

    fp = fopen("inputs/everybody_codes_e2025_q01_p1.txt", "r");
    //fp = fopen("inputs/everybody_codes_e2025_q01_p1-test.txt", "r");
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
    int move;
    while (1)
    {
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
        c = *(++ptr);
        c = c - '0';
        c *= move;
        i += c;

        if (i < 0)
            i = 0;
        else if (i >= namescnt)
            i = namescnt - 1;

        c = *(++ptr);

        if (c == '\0')
            break;

        c = *(++ptr);
    }
    printf("%s\n", namesptr[i]);

    exit(EXIT_SUCCESS);
}
