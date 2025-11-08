#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "misc.h"

#define BUFFSIZE 100
#define ARRSIZE 100

struct spine {
    int left, right, value;
    struct spine *down;
};

typedef struct spine spine;

spine *spine_create();
void spine_insert(spine *root, int n);
void spine_delete(spine *root);



int main()
{
    char buffer[BUFFSIZE];
    long array[ARRSIZE] = {};

    FILE *fp = fopen("inputs/everybody_codes_e2025_q05_p2.txt", "r");
    //FILE *fp = fopen("inputs/everybody_codes_e2025_q05_p2-test.txt", "r");
    if (!fp) { perror("fopen"); exit(1); }

    char *ret = myfgets(buffer, BUFFSIZE, fp);
    int i = 0;
    while(ret) {
        spine *root = spine_create();
        char *bufstr = buffer;
        while (*bufstr != ':')
            bufstr++;
        bufstr++;

        char *token = strtok(bufstr, ",");
        while (token != NULL) {
            spine_insert(root, atoi(token));
            token = strtok(NULL, ",");
        }

        long  n = 0;
        for (spine *s = root; s != NULL; s = s->down) {
            n *= 10;
            n += s->value;
        }
        array[i++] = n;

        spine_delete(root);
        ret = myfgets(buffer, BUFFSIZE, fp);
    }
    fclose(fp);

    int array_len = i;
    long min, max;

    min = max = array[0];

    for (i = 1; i < array_len; i++) {
        long n = array[i];
        if (n < min) min = n;
        if (n > max) max = n;
    }

    printf("%ld\n", max - min);


    exit(0);
}



spine *spine_create()
{
    spine *s = (spine *)malloc(sizeof(spine));

    s->left  = -1;
    s->right = -1;
    s->value = -1;
    s->down = NULL;

    return s;
}



void spine_insert(spine *root, int n)
{
    if (root->value == -1)
        root->value = n;
    else if ((root->left == -1) && (n < root->value))
        root->left = n;
    else if ((root->right == -1) && (n > root->value))
        root->right = n;
    else {
        if (root->down == NULL)
            root->down = spine_create();
        spine_insert(root->down, n);
    }
}



void spine_delete(spine *root)
{
    if (root != NULL) {
        spine_delete(root->down);
        free(root);
    }
}

