#include <stdlib.h>
#include <stdio.h>
#include "misc.h"

#define BUFFER_SIZE 32
#define ARRAY_SIZE  50
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

    FILE *fp = fopen("inputs/everybody_codes_e2025_q04_p2.txt", "r");
    //FILE *fp = fopen("inputs/everybody_codes_e2025_q04_p2-test.txt", "r");
    if (!fp) exit(2);

    char *ret = myfgets(buffer, BUFFER_SIZE, fp);
    int i = 0;
    while (ret) {
        array[i++] = atoi(buffer);
        ret = myfgets(buffer, BUFFER_SIZE, fp);
    }
    int array_length = i;

    int x = 0, y = array_length - 1;
    while (x < y) {
        int tmp = array[x];
        array[x] = array[y];
        array[y] = tmp;
        x++; y--;
    }

    rational a = rational_create(NTURNS, 1);

    for (i = 0; i < array_length - 1; i++) {
        rational b = rational_create(array[i], array[i + 1]);
        a = rational_multiply(a, b);
    }

    lldiv_t result = lldiv(a.n, a.d);
    printf("%lld\n", result.quot + (result.rem == 0 ? 0 : 1));


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


