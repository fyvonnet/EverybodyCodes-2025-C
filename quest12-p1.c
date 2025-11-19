#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <complex.h>
#include "misc.h"
#include "deque.h"

#define make_coord CMPLX
#define coord_col(p) ((int)(creal(p)))
#define coord_row(p) ((int)(cimag(p)))
#define GRID_WIDTH  20
#define GRID_HEIGHT 20
#define BUFLEN      25
#define IGNITED     99

typedef complex int coordinate;

typedef struct {
    coordinate coord;
    int height;
} queue_elm;


void enqueue(deque *q, int grid[GRID_WIDTH][GRID_HEIGHT], coordinate coord);
bool coord_valid(coordinate coord);


int main()
{
    coordinate moves[4] = {
        make_coord( 0,  1),
        make_coord( 0, -1),
        make_coord( 1,  0),
        make_coord(-1,  0), 
    };

    int grid[GRID_WIDTH][GRID_HEIGHT];
    char buffer[BUFLEN];
    FILE *fp = fopen("inputs/everybody_codes_e2025_q12_p1.txt", "r");
    deque *queue = deque_create();

    for (int row = 0; row < GRID_HEIGHT; row++) {
        myfgets(buffer, BUFLEN, fp);
        for (int col = 0; col < GRID_WIDTH; col++)
            grid[col][row] = buffer[col] - '0';
    }

    enqueue(queue, grid, make_coord(0, 0));
    queue_elm *elm = deque_pop_head(queue);
    int counter = 0;
    while (elm != NULL) {
        counter++;
        coordinate coord = elm->coord;
        int height = elm->height;
        free(elm);
        for (int m = 0; m < 4; m++) {
            coordinate new_coord = coord + moves[m];
            if (coord_valid(new_coord)) {
                int col = coord_col(new_coord);
                int row = coord_row(new_coord);
                if (grid[col][row] <= height)
                    enqueue(queue, grid, new_coord);
            }
        }
        elm = deque_pop_head(queue);
    }

    printf("%i\n", counter);

    exit(0);
}



void enqueue(deque *q, int grid[GRID_WIDTH][GRID_HEIGHT], coordinate coord)
{
    queue_elm *e = malloc(sizeof(queue_elm));
    e->coord = coord;
    int col = coord_col(coord);
    int row = coord_row(coord);
    e->height = grid[col][row];
    grid[col][row] = IGNITED;
    deque_push_tail(q, e);
}



bool coord_valid(coordinate coord)
{
    int col = coord_col(coord);
    int row = coord_row(coord);

    if (col < 0) return false;
    if (row < 0) return false;
    if (col >= GRID_WIDTH) return false;
    if (row >= GRID_HEIGHT) return false;

    return true;
}

