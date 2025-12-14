#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "misc.h"
#include "redblacktree.h"

#define BOARD_HEIGHT 6
#define BOARD_WIDTH  7

#define BUFLEN      10

typedef enum { DRAGON, SHEEP } Turn;
typedef struct {
    Turn turn;
    int sheepspos[BOARD_WIDTH], dragcol, dragrow;
    unsigned long value;
    int move;
} CacheElm;

int dragmoves[8][2] = {
    { 2, -1},
    { 2,  1},
    {-2, -1},
    {-2,  1},
    {-1,  2},
    { 1,  2},
    {-1, -2},
    { 1, -2}
};

bool refuges[BOARD_WIDTH][BOARD_HEIGHT];
redblacktree *cache;

unsigned long sheep_turn(int sheepscnt, int sheepspos[BOARD_WIDTH], int dragcol, int dragrow, int move);
unsigned long drag_turn(int sheepscnt, int sheepspos[BOARD_WIDTH], int dragcol, int dragrow, int move);
int compar_cacheelm(const void *a, const void *b);



int main()
{
    FILE *fp = fopen("inputs/everybody_codes_e2025_q10_p3.txt", "r");
    if (!fp) { perror("fopen"); exit(1); }

    cache = redblacktree_init(compar_cacheelm);

    int sheepscnt = 0;
    int sheepspos[BOARD_WIDTH];

    char buffer[BUFLEN];

    for (int col = 0; col < BOARD_WIDTH; col++) {
        sheepspos[col] = -1;
        for (int row = 0; row < BOARD_HEIGHT; row++) 
            refuges[col][row] = false;
    }

    int dragcol = -1;
    int dragrow = -1;
    for (int row = 0; row < BOARD_HEIGHT; row++) {
        myfgets(buffer, BUFLEN, fp);
        for (int col = 0; col < BOARD_WIDTH; col++) {
            char c = buffer[col];
            switch(c){
                case 'D':
                    dragcol = col;
                    dragrow = row;
                    break;
                case 'S':
                    sheepspos[col] = row;
                    sheepscnt++;
                    break;
                case '#':
                    refuges[col][row] = true;
                    break;
                case '.':
                    break;
                default:
                    fprintf(stderr, "Invalid character: %c\n", c);
                    exit(1);
            }
        }
    }
    fclose(fp);

    unsigned long sum = 0;
    for (int m = 0; m < BOARD_WIDTH; m++)
        sum += sheep_turn(sheepscnt, sheepspos, dragcol, dragrow, m);
    printf("%li\n", sum);
}



unsigned long sheep_turn(int sheepscnt, int sheepspos[BOARD_WIDTH], int dragcol, int dragrow, int move)
{
    int col = move;
    int row = sheepspos[col];
    CacheElm *elm = NULL;

    // no sheep in this column
    if (row == -1) return 0;

    // sheep at the edge of the board will escape
    if (row == BOARD_HEIGHT - 1) return 0;

    int newsheepspos[BOARD_WIDTH];
    for (int i = 0; i < BOARD_WIDTH; i++)
        newsheepspos[i] = sheepspos[i];

    // can't land on the dragon if there's no refuge
    if ((col == dragcol) && ((row + 1) == dragrow) && (!refuges[col][row + 1])) {
        if (sheepscnt == 1) goto skip_turn; // skip if the only remaining sheep can't move
        else return 0;
    }

    newsheepspos[col]++;

    elm = malloc(sizeof(CacheElm));
    elm->turn = SHEEP;
    elm->dragcol = dragcol;
    elm->dragrow = dragrow;
    for (int i = 0; i < BOARD_WIDTH; i++)
        elm->sheepspos[i] = newsheepspos[i];

    CacheElm *ret = redblacktree_insert(cache, (void *)elm);
    if (ret != NULL) {
        free(elm);
        return ret->value;
    }
    else {
skip_turn:
        unsigned long sum = 0;
        for (int m = 0; m < 8; m++)
            sum += drag_turn(sheepscnt, newsheepspos, dragcol, dragrow, m);
        if (elm != NULL) elm->value = sum;
        return sum;
    }
}



unsigned long drag_turn(int sheepscnt, int sheepspos[BOARD_WIDTH], int dragcol, int dragrow, int move)
{
    dragcol += dragmoves[move][0];
    dragrow += dragmoves[move][1];

    // dragon lands outside the board
    if (dragcol < 0) return 0;
    if (dragrow < 0) return 0;
    if (dragcol >= BOARD_WIDTH) return 0;
    if (dragrow >= BOARD_HEIGHT) return 0;

    int newsheepspos[BOARD_WIDTH];
    for (int i = 0; i < BOARD_WIDTH; i++)
        newsheepspos[i] = sheepspos[i];

    // lands on a sheep that's not in a refuge
    if ((newsheepspos[dragcol] == dragrow) && (!refuges[dragcol][dragrow])) {
        sheepscnt--;
        newsheepspos[dragcol] = -1;
        if (sheepscnt == 0) return 1; // game won! \o/
    }

    CacheElm *elm = malloc(sizeof(CacheElm));
    elm->turn = DRAGON;
    elm->dragcol = dragcol;
    elm->dragrow = dragrow;
    for (int i = 0; i < BOARD_WIDTH; i++)
        elm->sheepspos[i] = newsheepspos[i];

    CacheElm *ret = redblacktree_insert(cache, (void *)elm);
    if (ret != NULL) {
        free(elm);
        return ret->value;
    }
    else {
        unsigned long sum = 0;
        for (int m = 0; m < BOARD_WIDTH; m++)
            sum += sheep_turn(sheepscnt, newsheepspos, dragcol, dragrow, m);
        elm->value = sum;
        return sum;
    }
}



int compar_cacheelm(const void *a, const void *b)
{
    CacheElm *aa = (CacheElm *)a;
    CacheElm *bb = (CacheElm *)b;
    int ret;

    ret = aa->turn - bb->turn;
    if (ret != 0) return ret;

    ret = aa->dragcol - bb->dragcol;
    if (ret != 0) return ret;

    ret = aa->dragrow - bb->dragrow;
    if (ret != 0) return ret;

    for (int i = 0; i < BOARD_WIDTH; i++) {
        ret = aa->sheepspos[i] - bb->sheepspos[i];
        if (ret != 0) return ret;
    }

    return 0;
}

