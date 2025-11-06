#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <regex.h>
#include "misc.h"

#define BUFF_SIZE 64
#define CYCLES_COUNT 100
#define GRID_SIDE   101
#define LIM_MIN -1000000 
#define LIM_MAX 1000000 

typedef struct { long x, y; } cmplx;

cmplx cmplx_add(cmplx a, cmplx b);
cmplx cmplx_mul(cmplx a, cmplx b);
cmplx cmplx_div(cmplx a, cmplx b);
bool cmplx_valid(cmplx c);
void cmplx_print(cmplx c);

int main()
{
    FILE *fp = fopen("inputs/everybody_codes_e2025_q02_p2.txt", "r");
    //FILE *fp = fopen("inputs/everybody_codes_e2025_q02_p2-test.txt", "r");
    char buffer[BUFF_SIZE];
    const char *pattern = "\\[(-?[0-9]+),(-?[0-9]+)\\]";
    regex_t regex;
    const size_t nmatch = 3;
    regmatch_t pmatch[nmatch];

    myfgets(buffer, BUFF_SIZE, fp);
    fclose(fp);

    if (regcomp(&regex, pattern, REG_EXTENDED))     exit(2);
    if (regexec(&regex, buffer, nmatch, pmatch, 0)) exit(3);
    regfree(&regex);

    int point_first = atoi(buffer + pmatch[1].rm_so);
    int row_first   = atoi(buffer + pmatch[2].rm_so);
    int point_last = point_first + 1000;
    int row_last   = row_first   + 1000;

    cmplx div, coord, result;
    div.x = 100000;
    div.y = 100000;

    int count = 0;

    for (int row = row_first; row <= row_last; row += 10) {
        for (int point = point_first; point <= point_last; point += 10) {
            coord.x = point;
            coord.y = row;
            result.x = 0;
            result.y = 0;
            bool valid;
            for (int i = 0; i < CYCLES_COUNT; i++) {
                result = cmplx_mul(result, result);
                result = cmplx_div(result, div);
                result = cmplx_add(result, coord);
                valid = cmplx_valid(result);
                if (!valid)
                    break;
            }
            if (valid)
                count++;
        }
    }

    printf("%d\n", count);

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

    r.x = (long)(a.x / b.x);
    r.y = (long)(a.y / b.y);

    return r;
}



bool cmplx_valid(cmplx c)
{
    if (c.x < LIM_MIN) return false;
    if (c.y < LIM_MIN) return false;
    if (c.x > LIM_MAX) return false;
    if (c.y > LIM_MAX) return false;

    return true;
}



void cmplx_print(cmplx c)
{
    printf("[%ld,%ld]\n", c.x, c.y);
}

