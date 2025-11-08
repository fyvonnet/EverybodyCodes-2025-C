#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "misc.h"

#define BUFFSIZE 100
#define ARRSIZE 500

struct spine {
    int left, right, value, number;
    struct spine *down;
};
typedef struct spine spine;

struct sword {
    int id;
    long quality;
    spine *s;
};
typedef struct sword sword;

spine *spine_create();
void spine_insert(spine *root, int n);
void spine_delete(spine *root);
long spine_quality(spine *root);
int compar_swords(const void *a, const void *b);



int main()
{
    char buffer[BUFFSIZE];
    sword array[ARRSIZE] = {};

    FILE *fp = fopen("inputs/everybody_codes_e2025_q05_p3.txt", "r");
    if (!fp) { perror("fopen"); exit(1); }

    char *ret = myfgets(buffer, BUFFSIZE, fp);
    int i = 0;
    while(ret) {
        spine *root = spine_create();
        char *bufstr = buffer;

        array[i].id = atoi(buffer);
        array[i].s = root;

        while (*bufstr != ':')
            bufstr++;
        bufstr++;

        char *token = strtok(bufstr, ",");
        while (token != NULL) {
            spine_insert(root, atoi(token));
            token = strtok(NULL, ",");
        }

        array[i].quality = spine_quality(root);

        i++;
        ret = myfgets(buffer, BUFFSIZE, fp);
    }
    fclose(fp);

    int array_len = i;
    qsort(array, array_len, sizeof(sword), compar_swords);

    long checksum = 0;
    for (i = 0; i < array_len; i++)
        checksum += array[i].id * (i + 1);
    printf("%ld\n", checksum);

    exit(0);
}



spine *spine_create()
{
    spine *s = (spine *)malloc(sizeof(spine));

    s->left   = -1;
    s->right  = -1;
    s->value  = -1;
    s->number =  0;
    s->down   =  NULL;

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



long spine_quality(spine *root)
{
    long quality = 0;
    for (spine *s = root; s != NULL; s = s->down) {
        int n = 0;
        if (s->left != -1) n = s->left;
        n *= 10; n += s->value;
        if (s->right != -1) { n *= 10; n += s->right; }
        s->number = n;
        quality *= 10;
        quality += s->value;
    }
    return quality;
}



int compar_swords(const void *a, const void *b) 
{
    sword *aa = (sword *)a;
    sword *bb = (sword *)b;
    int ret;

    if (bb->quality > aa->quality) return  1;
    if (bb->quality < aa->quality) return -1;

    spine *sa = aa->s; spine *sb = bb->s;
    while ((sa != NULL) && (sb != NULL)) {
        ret = sb->number - sa->number;
        if (ret != 0) return ret;
        sa = sa->down; sb = sb->down;
    }

    return bb->id - aa->id;
}

