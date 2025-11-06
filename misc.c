#include <stdio.h>
#include <string.h>

char *myfgets(char * restrict s, int size, FILE *stream)
{
    *s = '\0';
    char* r = fgets(s, size, stream);
    int l = strlen(s);

    if ((l > 0) && (s[l - 1] == '\n'))
        s[l - 1] = '\0';

    return r;
}

int modulo(int a, int b)
{
    return ((a % b) + b) % b;
}
