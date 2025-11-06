#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <regex.h>
#include "misc.h"

#define BUFF_SIZE 64
#define CYCLES_COUNT 3

struct cmplx { int x, y; };
typedef struct cmplx cmplx;

cmplx cmplx_add(cmplx a, cmplx b);
cmplx cmplx_mul(cmplx a, cmplx b);
cmplx cmplx_div(cmplx a, cmplx b);
void cmplx_print(cmplx c);

int main()
{
    FILE *fp = fopen("inputs/everybody_codes_e2025_q02_p1.txt", "r");
    char buffer[BUFF_SIZE];
    const char *pattern = "\\[([0-9]+),([0-9]+)\\]";
    regex_t regex;
    int ret;
    size_t nmatch = 3;
    regmatch_t *pmatch = malloc (sizeof (*pmatch) * nmatch);

    myfgets(buffer, BUFF_SIZE, fp);
    fclose(fp);

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) exit(2);


    ret = regexec(&regex, buffer, nmatch, pmatch, 0);
    if (ret) exit(3);

    regfree(&regex);

    cmplx a, r, d;
    a.x = atoi(buffer + pmatch[1].rm_so);
    a.y = atoi(buffer + pmatch[2].rm_so);
    r.x = 0;
    r.y = 0;
    d.x = 10;
    d.y = 10;

    for (int i = 0; i < CYCLES_COUNT; i++) {
        r = cmplx_mul(r, r);
        r = cmplx_div(r, d);
        r = cmplx_add(r, a);
    }

    cmplx_print(r);

    exit(EXIT_SUCCESS);
}



cmplx cmplx_add(cmplx a, cmplx b)
{
    cmplx r;

    r.x = a.x + b.x;
    r.y = a.y + b.y;

    return r;
}



cmplx cmplx_mul(cmplx a, cmplx b)
{
    cmplx r;

    r.x = (a.x * b.x) - (a.y * b.y);
    r.y = (a.x * b.y) + (a.y * b.x);

    return r;
}



cmplx cmplx_div(cmplx a, cmplx b)
{
    cmplx r;

    r.x = trunc(a.x / b.x);
    r.y = trunc(a.y / b.y);

    return r;
}



void cmplx_print(cmplx c)
{
    printf("[%d,%d]\n", c.x, c.y);
}

