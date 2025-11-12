#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "misc.h"
#include "deque.h"

#define BUFLEN  900

typedef struct {
    char letter;
    char nextletters[20];
    int letterscnt;
} rule;

typedef struct {
    char letter;
    int len;
} name_node;

int compar_rules(const void *a, const void *b);
int compar_strings(const void *a, const void *b);
bool check_name(char *name, rule *rules, int rulescnt);
int find_names(char *name, rule *rules, int rulescnt);



int main()
{
    char buffer[BUFLEN];
    char namesstr[BUFLEN];
    //FILE *fp = fopen("inputs/everybody_codes_e2025_q07_p3-test2.txt", "r");
    FILE *fp = fopen("inputs/everybody_codes_e2025_q07_p3.txt", "r");
    if (!fp) { perror("fopen"); exit(1); }

    myfgets(namesstr, BUFLEN, fp);
    myfgets(buffer, BUFLEN, fp); // skip empty line

    rule rules[50];
    char *ret = myfgets(buffer, BUFLEN, fp);
    int i = 0;
    while (ret != NULL) {
        rules[i].letter = *buffer;
        int j = 0;
        char *ptr;
        for (ptr = buffer + 4; *(ptr + 1) == ','; ptr += 2)
            rules[i].nextletters[j++] = *ptr;
        rules[i].nextletters[j++] = *ptr;
        rules[i].nextletters[j] = '\0';
        rules[i].letterscnt = j;
        i++;
        ret = myfgets(buffer, BUFLEN, fp);

    }
    int rulescnt = i;

    qsort(rules, rulescnt, sizeof(rule), compar_rules);

    i = 0;
    char *names[20];
    char *token = strtok(namesstr, ",");
    while (token != NULL) {
        if (check_name(token, rules, rulescnt))
            names[i++] = token;
        token = strtok(NULL, ",");
    }
    int namescnt = i;

    qsort(names, namescnt, sizeof(char *), compar_strings);
    int sum = 0;
    for (int i = 0; i < namescnt; i++) {
        bool b = true;
        for (int j = i + 1; j < namescnt; j++)
            if (!strncmp(names[i], names[j], strlen(names[j]))) {
                b = false;
                break;
            }
        if (b) sum += find_names(names[i], rules, rulescnt);
    }

    printf("%i\n", sum);
    exit(0);
}



int compar_strings(const void *a, const void *b)
{
    return strlen(*((char **)b)) - strlen(*((char **)a));
    //return strcmp(*((char **)a), *((char **)b));
}



int compar_rules(const void *a, const void *b)
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
        rule *r = binsearch(rules, rulescnt, sizeof(rule), compar_rules, &t);
        if (strchr(r->nextletters, ptr[1]) == NULL)
            return false;
    }
    return true;
}



int find_names(char *name, rule *rules, int rulescnt)
{
    int cnt = 0;

    if (!check_name(name, rules, rulescnt))
        return 0;

    deque *q = deque_create();
    name_node *n = malloc(sizeof(name_node));
    n->len = strlen(name);
    n->letter = name[n->len - 1];
    //deque_push_tail(q, (void *)n);

    while (n != NULL) {
        int len = n->len;
        int letter = n->letter;
        free(n);

        if (len >= 7)
            cnt++;

        if (len != 11) {
            len++;
            rule t; t.letter = letter;
            rule *r = binsearch(rules, rulescnt, sizeof(rule), compar_rules, &t);
            if (r != NULL) {
                for (int i = 0; i < r->letterscnt; i++) {
                    n = malloc(sizeof(name_node));
                    n->len = len;
                    n->letter = r->nextletters[i];
                    deque_push_tail(q, n);
                }
            }
        }

        n = deque_pop_head(q);
    }

    return cnt;
}

