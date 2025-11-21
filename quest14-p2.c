#include <stdlib.h>
#include <stdio.h>
#include <complex.h>
#include <string.h>
#include "misc.h"

#define BUFLEN  40
#define GRID_SIDE  34
#define NROUNDS     2025


char get_grid(char grid[NROUNDS + 1][GRID_SIDE][GRID_SIDE], int round, int col, int row);

int main()
{
    int moves_col[4] = { -1, -1,  1,  1 };
    int moves_row[4] = { -1,  1, -1,  1 };

    FILE *fp = fopen("inputs/everybody_codes_e2025_q14_p2.txt", "r");
    char buffer[BUFLEN];
    char grid[NROUNDS + 1][GRID_SIDE][GRID_SIDE];

    for (int row = 0; row < GRID_SIDE; row++) {
        myfgets(buffer, BUFLEN, fp);
        for (int col = 0; col < GRID_SIDE; col++)
            switch(buffer[col]) {
                case '.':
                    grid[0][col][row] = 0;
                    break;
                case '#':
                    grid[0][col][row] = 1;
                    break;
                default:
                    fprintf(stderr, "incorrect character: %c\n", buffer[col]);
                    exit(1);
            }
    }

    for (int round = 0; round < NROUNDS; round++)
        for (int row = 0; row < GRID_SIDE; row++)
            for (int col = 0; col < GRID_SIDE; col++) {
                if (grid[round][col][row]) {
                    // tile is active
                    int cnt = 0;
                    for (int m = 0; m < 4; m++)
                        cnt += get_grid(grid, round, col + moves_col[m], row + moves_row[m]);
                    if (cnt % 2 == 1)
                        grid[round + 1][col][row] = 1;
                    else
                        grid[round + 1][col][row] = 0;
                }
                else {
                    // tile is inactive
                    int cnt = 0;
                    for (int m = 0; m < 4; m++)
                        cnt += get_grid(grid, round, col + moves_col[m], row + moves_row[m]);
                    if (cnt % 2 == 0)
                        grid[round + 1][col][row] = 1;
                    else
                        grid[round + 1][col][row] = 0;
                }
            }

    int cnt = 0;
    for (int round = 1; round <= NROUNDS; round++)
        for (int row = 0; row < GRID_SIDE; row++)
            for (int col = 0; col < GRID_SIDE; col++)
                cnt += grid[round][col][row];
    
    printf("%i\n", cnt);
    exit(0);
}



char get_grid(char grid[NROUNDS + 1][GRID_SIDE][GRID_SIDE], int round, int col, int row)
{
    if (col < 0)
        return 0;

    if (row < 0)
        return 0;

    if (col >= GRID_SIDE)
        return 0;

    if (row >= GRID_SIDE)
        return 0;

    return grid[round][col][row];
}
