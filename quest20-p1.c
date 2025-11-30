#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "misc.h"

#define BUFLEN  32
#define MAXROWS 15
#define MAXCOLS 30



int main()
{
    char buffer[BUFLEN];
    FILE *fp = fopen("inputs/everybody_codes_e2025_q20_p1.txt", "r");
    if (!fp) { perror("fopen"); exit(1); }
    char grid[MAXCOLS][MAXROWS];

    int movecol[3] = { -1,  1,  0 };
    int moverow[3] = {  0,  0,  1 };

    myfgets(buffer, BUFLEN, fp);

    const int ncols = strlen(buffer);
    const int nrows = (ncols >> 1) + 1;

    for (int row = 0; row < nrows; row++) {
        for (int col = 0; col < ncols; col++)
            grid[col][row] = buffer[col];
        myfgets(buffer, BUFLEN, fp);
    }

    int colstart = 1;
    int colend = ncols;
    int npairs = 0;
    for (int row = 0; row < nrows; row++) {
        for (int col = colstart; col < colend; col += 2)
            if (grid[col][row] == 'T')
                for (int m = 0; m < 3; m++)
                    if (grid[col + movecol[m]][row + moverow[m]] == 'T')
                        npairs++;
        colstart++;
        colend--;
    }
    printf("%i\n", npairs);

    exit(0);
}

