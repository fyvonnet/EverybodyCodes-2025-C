#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "misc.h"
#include "coord.h"
#include "deque.h"

#define BUFLEN      200
#define GRIDSIDE    51
#define FREE        '.'
#define BLOCKED     '#'

typedef struct { coordinate coord; int nsteps; } queue_elm;



int main()
{
    FILE *fp = fopen("inputs/everybody_codes_e2025_q15_p1.txt", "r");
    if (!fp) { perror("fopen"); exit(1); }
    char buffer[BUFLEN];

    myfgets(buffer, BUFLEN, fp);

    fclose(fp);

    char grid[GRIDSIDE][GRIDSIDE];

    for (int i = 0; i < GRIDSIDE; i++)
        for (int j = 0; j < GRIDSIDE; j++)
            grid[i][j] = FREE;

    char *token = strtok(buffer, ",");
    direction_abs face = DIR_NORTH;
    coordinate start, coord;
    start = coord_create(GRIDSIDE >> 1, GRIDSIDE >> 1);
    coord = start;
    while (token) {
        switch (*token) {
            case 'L':
                face = coord_turn(face, DIR_LEFT);
                break;
            case 'R':
                face = coord_turn(face, DIR_RIGHT);
                break;
            default:
                fprintf(stderr, "Incorrection direction: %c\n", *token);
                exit(1);
        }

        int nsteps = atoi(token + 1);
        for (int s = 0; s < nsteps; s++) {
            grid[coord_x(coord)][coord_y(coord)] = BLOCKED;
            coord += coord_moves[face];
        }

        token = strtok(NULL, ",");
    }

    coordinate exitpt = coord;
    deque *queue = deque_create();
    queue_elm *qe = malloc(sizeof(queue_elm));
    qe->coord = start;
    qe->nsteps = 0;
    int nsteps = 0;
    while (qe != NULL) {
        coordinate coord = qe->coord;
        nsteps = qe->nsteps;
        free(qe);
        if (coord == exitpt) break;
        for (int m = 0; m < 4; m++) {
            coordinate new_coord = coord + coord_moves[m];
            int new_coord_x = coord_x(new_coord);
            int new_coord_y = coord_y(new_coord);
            if (new_coord_x < 0) continue;
            if (new_coord_y < 0) continue;
            if (new_coord_x >= GRIDSIDE) continue;
            if (new_coord_y >= GRIDSIDE) continue;
            if (grid[new_coord_x][new_coord_y] == BLOCKED) continue;
            grid[new_coord_x][new_coord_y] = BLOCKED;
            qe = malloc(sizeof(queue_elm));
            qe->coord = new_coord;
            qe->nsteps = nsteps + 1;
            deque_push_tail(queue, qe);
        }
        qe = deque_pop_head(queue);
    }

    printf("%i\n", nsteps);

    exit(0);
}
