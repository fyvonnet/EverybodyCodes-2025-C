#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "misc.h"
#include "redblacktree.h"

#define BUFSIZE 1100

int compar(const void *a, const void *b);



int main()
{
    char buffer[BUFSIZE];
    FILE *fp = fopen("inputs/everybody_codes_e2025_q03_p2.txt", "r");
    if (!fp) exit(2);
    redblacktree *tree = redblacktree_init(compar);

    myfgets(buffer, BUFSIZE, fp);

    char *str = strtok(buffer, ",");
    while (str) {
        redblacktree_insert(tree, (void *)atoll(str));
        str = strtok(NULL, ",");
    }

    long long sum = 0;
    for (int i = 0; i < 20; i++)
        sum += (long long)redblacktree_pop_leftmost(tree);
    printf("%lld\n", sum);

    exit(0);
}



int compar(const void *a, const void *b)
{
    return (int)((long long)a) - ((long long)b);
}

