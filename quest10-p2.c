#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <complex.h>
#include <string.h>
#include "misc.h"
#include "deque.h"

#define BUFLEN  150
#define NROUNDS 20
#define make_pos CMPLX
#define pos_col(p) ((int)(creal(p)))
#define pos_row(p) ((int)(cimag(p)))

typedef complex int position;
typedef struct { position pos; int turn; } move;
typedef struct { bool sheep, refuge, dragon; } square;

void printpos(position pos);
void move_enqueue(deque *q, position pos, int turn);



int main()
{
    position moves[8] = {
        make_pos( 2, -1),
        make_pos( 2,  1),
        make_pos(-2, -1),
        make_pos(-2,  1),
        make_pos(-1,  2),
        make_pos( 1,  2),
        make_pos(-1, -2),
        make_pos( 1, -2)
    };

    FILE *fp = fopen("inputs/everybody_codes_e2025_q10_p2.txt", "r");
    if (!fp) { perror("fopen"); exit(1); }

    char buffer[BUFLEN];

    square grid[125][125];

    myfgets(buffer, BUFLEN, fp);
    int gridside = strlen(buffer);

    position dragon = make_pos(-1, -1);
    for (int row = 0; row < gridside; row++) {
        for (int col = 0; col < gridside; col++) {
            char c = buffer[col];
            switch(c){
                case 'D':
                    grid[col][row] = (square){ false, false, true };
                    dragon = make_pos(col, row);
                    break;
                case 'S':
                    grid[col][row] = (square){ true, false, false };
                    break;
                case '#':
                    grid[col][row] = (square){ false, true, false };
                    break;
                case '.':
                    grid[col][row] = (square){ false, false, false };
                    break;
                default:
                    fprintf(stderr, "Unknown character: %c\n", c);
                    exit(1);
            }
        }
        myfgets(buffer, BUFLEN, fp);
    }
    fclose(fp);


    int sheepcnt = 0;

    // initialize dragon
    deque *q = deque_create();
    move_enqueue(q, dragon, 0);

    for (int turn = 0; turn < NROUNDS; turn++) {
        for (int row = 0; row < gridside; row++)
            for (int col = 0; col < gridside; col++)
                grid[col][row].dragon = false;

        // dragon's turn
        move *moveptr = deque_pop_head(q);
        while (moveptr->turn == turn) {
            position pos = moveptr->pos;
            free(moveptr);
            for (int m = 0; m < 8; m++) {
                position newpos = pos + moves[m];
                int newpos_col = pos_col(newpos);
                int newpos_row = pos_row(newpos);
                if ((newpos_col >= 0) && (newpos_row >= 0) && (newpos_col < gridside) && (newpos_row < gridside)) {
                    square *sq = &grid[newpos_col][newpos_row];
                    if (!sq->dragon) {
                        sq->dragon = true;
                        if (sq->sheep && !sq->refuge) {
                            sq->sheep = false;
                            sheepcnt++;
                        }
                        move_enqueue(q, newpos, turn + 1);
                    }
                }
            }
            moveptr = deque_pop_head(q);
        }
        // move is for the next round
        // put it back in front of the queue
        deque_push_head(q, moveptr);

        // sheep's turn
        {
            // remove sheeps form bottom row
            for (int col = 0; col < gridside; col++) 
                grid[col][gridside - 1].sheep = false;

            // move remaining sheeps one row down
            for (int row = gridside - 2; row >= 0; row--)
                for (int col = 0; col < gridside; col++) {
                    grid[col][row + 1].sheep = grid[col][row].sheep;
                    grid[col][row].sheep = false;
                    // lands on a dragon while moving
                    square *sq = &grid[col][row + 1];
                    if (sq->sheep && sq->dragon && !sq->refuge) {
                        sq->sheep = false;
                        sheepcnt++;
                    }
                }
        }
    }

    printf("%i\n", sheepcnt);
    exit(0);
}



void printpos(position pos)
{
    printf("(%i, %i)\n", pos_col(pos), pos_row(pos));
}



void move_enqueue(deque *q, position pos, int turn)
{
    move *moveptr = malloc(sizeof(move));
    moveptr->pos = pos;
    moveptr->turn = turn;
    deque_push_tail(q, moveptr);
}

