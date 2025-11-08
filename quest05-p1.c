#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "misc.h"

#define BUFFSIZE 200

struct spine {
    int left, right, value;
    struct spine *down;
};

typedef struct spine spine;

spine *spine_create();
void spine_insert(spine *root, int n);



int main()
{
    char buffer[BUFFSIZE];
    spine *root = spine_create();
    FILE *fp = fopen("inputs/everybody_codes_e2025_q05_p1.txt", "r");
    //FILE *fp = fopen("inputs/everybody_codes_e2025_q05_p1-test.txt", "r");
    if (!fp) { perror("fopen"); exit(1); }
    myfgets(buffer, BUFFSIZE, fp);

    char *bufstr = buffer;
    while (*bufstr != ':')
        bufstr++;
    bufstr++;

    char *token = strtok(bufstr, ",");
    while (token != NULL) {
        spine_insert(root, atoi(token));
        token = strtok(NULL, ",");
    }

    fclose(fp);

    for (spine *s = root; s != NULL; s = s->down)
        printf("%d", s->value);
    putchar('\n');

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

