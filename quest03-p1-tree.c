#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "misc.h"
#include "redblacktree.h"

#define BUFSIZE 300

int compar(const void *a, const void *b);
void sum_values(void *value, void *sum_ptr);

int main()
{
    char buffer[BUFSIZE];
    //FILE *fp = fopen("inputs/everybody_codes_e2025_q03_p1-test.txt", "r");
    FILE *fp = fopen("inputs/everybody_codes_e2025_q03_p1.txt", "r");
    if (!fp) exit(2);
    redblacktree *tree = redblacktree_init(compar);


    myfgets(buffer, BUFSIZE, fp);

    char *str = strtok(buffer, ",");
    while (str) {
        redblacktree_insert(tree, (void *)atoll(str));
        str = strtok(NULL, ",");
    }

    long long sum = 0;
    redblacktree_inorder(tree, sum_values, &sum);

    printf("%lld\n", sum);

    exit(0);
}



void sum_values(void *value, void *sum_ptr)
{
    *((long long *)sum_ptr) += (long long) value;
}



int compar(const void *a, const void *b)
{
    return (int)((long long)a) - ((long long)b);
}

