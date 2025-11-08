#include <stdlib.h>
#include <stdio.h>
#include "misc.h"

#define BUFFER_SIZE 32
#define ARRAY_SIZE  50
#define NTURNS  2025


typedef struct { int n, d; } rational;

int gcd(int a, int b);
void rational_reduce(rational *r);
void rational_print(rational r);
rational rational_multiply(rational a, rational b);
rational rational_create(int n, int d);
double rational_to_double(rational r);



int main()
{
    char buffer[BUFFER_SIZE];
    int array[ARRAY_SIZE];

    FILE *fp = fopen("inputs/everybody_codes_e2025_q04_p1.txt", "r");
    if (!fp) exit(2);

    char *ret = myfgets(buffer, BUFFER_SIZE, fp);
    int i = 0;
    while (ret) {
        array[i++] = atoi(buffer);
        ret = myfgets(buffer, BUFFER_SIZE, fp);
    }
    int array_length = i;

    rational a = rational_create(NTURNS, 1);

    for (i = 0; i < array_length - 1; i++) {
        rational b = rational_create(array[i], array[i + 1]);
        a = rational_multiply(a, b);
    }

    printf("%d\n", (int)(rational_to_double(a)));


    exit(0);
}



int gcd(int a, int b)
{
    if (a)
        return gcd(b % a, a);
    return b;
}



void rational_reduce(rational *r)
{
    int d = gcd(r->n, r->d);
    r->n /= d;
    r->d /= d;
}




void rational_print(rational r)
{
    printf("%d/%d\n", r.n, r.d);
}



rational rational_multiply(rational a, rational b)
{
    rational r;
    r.n = a.n * b.n;
    r.d = a.d * b.d;
    rational_reduce(&r);
    return r;
}



rational rational_create(int n, int d)
{
    rational r;
    r.n = n; r.d = d;
    rational_reduce(&r);
    return r;
}



double rational_to_double(rational r)
{
    return (double)r.n / (double)r.d;
}
