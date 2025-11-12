#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "misc.h"

#define BUFLEN  100

typedef struct {
    char letter;
    char nextletters[5];
} rule;

int compar(const void *a, const void *b);
bool check_name(char *name, rule *rules, int rulescnt);



int main()
{
    char buffer[BUFLEN];
    char namesstr[BUFLEN];
    //FILE *fp = fopen("inputs/everybody_codes_e2025_q07_p1-test.txt", "r");
    FILE *fp = fopen("inputs/everybody_codes_e2025_q07_p1.txt", "r");
    if (!fp) { perror("fopen"); exit(1); }

    myfgets(namesstr, BUFLEN, fp);

    char c;
    int i = 1;
    char *names[20];
    names[0] = namesstr;
    for (char *ptr = namesstr; (c = *ptr) != '\0'; ptr++)
        if (c == ',') {
            names[i++] = (ptr + 1);
            *ptr = '\0';
        }
    int namescnt = i;

    myfgets(buffer, BUFLEN, fp); // skip empty line

    rule rules[20];
    char *ret = myfgets(buffer, BUFLEN, fp);
    i = 0;
    while (ret != NULL) {
        rules[i].letter = *buffer;
        int j = 0;
        char *ptr;
        for (ptr = buffer + 4; *(ptr + 1) == ','; ptr += 2)
            rules[i].nextletters[j++] = *ptr;
        rules[i].nextletters[j++] = *ptr;
        rules[i].nextletters[j] = '\0';
        i++;
        ret = myfgets(buffer, BUFLEN, fp);

    }
    int rulescnt = i;

    qsort(rules, rulescnt, sizeof(rule), compar);

    for (int i = 0; i < namescnt; i++)
        if (check_name(names[i], rules, rulescnt)) {
            printf("%s\n", names[i]);
            exit(0);
        }

    exit(0);
}



int compar(const void *a, const void *b)
{
    rule *aa = (rule *)a;
    rule *bb = (rule *)b;

    return aa->letter - bb->letter;
}



bool check_name(char *name, rule *rules, int rulescnt)
{
    for (char *ptr = name; *(ptr + 1) != '\0'; ptr++) {
        rule t;
        t.letter = ptr[0];
        rule *r = binsearch(rules, rulescnt, sizeof(rule), compar, &t);
        if (strchr(r->nextletters, ptr[1]) == NULL)
            return false;
    }
    return true;
}

