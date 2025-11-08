#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "misc.h"

#define BUFFER_SIZE 32
#define ARRAY_SIZE  200
#define NTURNS  10000000000000


typedef struct { unsigned long long n, d; } rational;

unsigned long long gcd(unsigned long long a, unsigned long long b);
void rational_reduce(rational *r);
void rational_print(rational r);
rational rational_multiply(rational a, rational b);
rational rational_create(unsigned long long n, unsigned long long d);



int main()
{
    char buffer[BUFFER_SIZE];
    int array[ARRAY_SIZE];

    FILE *fp = fopen("inputs/everybody_codes_e2025_q04_p3.txt", "r");
    if (!fp) exit(2);

    char *ret = myfgets(buffer, BUFFER_SIZE, fp);
    int i = 0;
    while (ret) {
        char *token = strtok(buffer, "|");
        while (token) {
            array[i++] = atoi(token);
            token = strtok(NULL, "|");
        }
        ret = myfgets(buffer, BUFFER_SIZE, fp);
    }
    int array_length = i;

    rational r = rational_create(100, 1);

    for (i = 0; i < array_length - 2; i+=2) {
        printf("%d:%d => ", array[i], array[i + 1]);
        rational_print(r);
        r = rational_multiply(r, rational_create(array[i], array[i + 1]));
    }

    r = rational_multiply(r, rational_create(array[array_length - 2], array[array_length - 1]));

    lldiv_t result = lldiv(r.n, r.d);
    printf("%lld\n", result.quot);

    exit(0);
}



unsigned long long gcd(unsigned long long a, unsigned long long b)
{
    if (a)
        return gcd(b % a, a);
    return b;
}



void rational_reduce(rational *r)
{
    unsigned long long d = gcd(r->n, r->d);
    r->n /= d;
    r->d /= d;
}




void rational_print(rational r)
{
    printf("%lld/%lld\n", r.n, r.d);
}



rational rational_multiply(rational a, rational b)
{
    rational r;
    r.n = a.n * b.n;
    r.d = a.d * b.d;
    rational_reduce(&r);
    return r;
}



rational rational_create(unsigned long long n, unsigned long long d)
{
    rational r;
    r.n = n; r.d = d;
    rational_reduce(&r);
    return r;
}


