#include <stdlib.h>
#include <stdio.h>
#include <complex.h>
#include <string.h>
#include "misc.h"
#include "deque.h"

#define BUFLEN  30
#define NMOVES 4

complex int moves[8] = {
    CMPLX( 2, -1),
    CMPLX( 2,  1),
    CMPLX(-2, -1),
    CMPLX(-2,  1),
    CMPLX(-1,  2),
    CMPLX( 1,  2),
    CMPLX(-1, -2),
    CMPLX( 1, -2)
};

typedef struct { complex int pos; int cd; } move;

void printpos(complex int pos);



int main()
{
    FILE *fp = fopen("inputs/everybody_codes_e2025_q10_p1.txt", "r");
    if (!fp) { perror("fopen"); exit(1); }

    char buffer[BUFLEN];

    char grid[25][25];

    myfgets(buffer, BUFLEN, fp);
    int gridside = strlen(buffer);
    complex int dragon = CMPLX(-1, -1);
    for (int row = 0; row < gridside; row++) {
        for (int col = 0; col < gridside; col++) {
            char c = buffer[col];
            if (c == 'D')
                dragon = CMPLX(col, row);
            grid[col][row] = c;
        }
        myfgets(buffer, BUFLEN, fp);
    }

    deque *q = deque_create();
    move *moveptr = malloc(sizeof(move));
    moveptr->pos = dragon;
    moveptr->cd  = NMOVES;

    int sheepcnt = 0;
    while (moveptr != NULL) {
        complex int pos = moveptr->pos;
        int cd = moveptr->cd;
        free(moveptr);
        if (cd != 0) {
            cd--;
            for (int m = 0; m < 8; m++) {
                complex int newpos = pos + moves[m];
                int newpos_col = (int)creal(newpos);
                int newpos_row = (int)cimag(newpos);
                if ((newpos_col >= 0) && (newpos_row >= 0) && (newpos_col < gridside) && (newpos_row < gridside) && (grid[newpos_row][newpos_col] != 'D')) {
                    if (grid[newpos_row][newpos_col] == 'S')
                        sheepcnt++;
                    grid[newpos_row][newpos_col] = 'D';
                    moveptr = malloc(sizeof(complex int));
                    moveptr->pos = newpos;
                    moveptr->cd = cd;
                    deque_push_tail(q, moveptr);
                }
            }
        }
        moveptr = deque_pop_head(q);
    }

    printf("%i\n", sheepcnt);

    exit(0);
}



void printpos(complex int pos)
{
    printf("(%i, %i)\n", (int)creal(pos), (int)(cimag(pos)));
}
