#include <stdlib.h>
#include <stdio.h>
#include <regex.h>
#include <string.h>
#include "misc.h"

#define MAXBRANCH   7
#define MAXPLANTS   20
#define BUFLEN      50

typedef struct Plant Plant;

typedef struct {
    Plant *plantptr;
    int thickness;
} Branch;

struct Plant {
    int thickness, nbranches, energy;
    Branch branches[MAXBRANCH];
};



int main()
{
    Plant plants[MAXPLANTS];
    int nplants = 0;

    {
        regex_t pregex, fbregex, bregex;
        char ppattern[]  = "Plant ([0-9]+) with thickness ([0-9]+):";
        char fbpattern[] = "free branch with thickness ([0-9]+)";
        char bpattern[]  = "branch to Plant ([0-9]+) with thickness ([0-9]+)";

        int nmatch = 5;
        regmatch_t pmatch[nmatch];

        if (regcomp(&pregex,  ppattern,  REG_EXTENDED)) { perror("regcomp"); exit(1); }
        if (regcomp(&fbregex, fbpattern, REG_EXTENDED)) { perror("regcomp"); exit(1); }
        if (regcomp(&bregex,  bpattern,  REG_EXTENDED)) { perror("regcomp"); exit(1); }

        char buffer[BUFLEN];
        FILE *fp = fopen("inputs/everybody_codes_e2025_q18_p1.txt", "r");

        char *fgetsret = myfgets(buffer, BUFLEN, fp);
        while (fgetsret != NULL) {
            nplants++;
            regexec(&pregex, buffer, nmatch, pmatch, 0);
            Plant *plantptr = plants + atoi(buffer + pmatch[1].rm_so);
            plantptr->thickness = atoi(buffer + pmatch[2].rm_so);
            plantptr->energy = 0;
            int i = 0;
            fgetsret = myfgets(buffer, BUFLEN, fp);
            while ((fgetsret != NULL) && (strlen(buffer) != 0)) {
                if (regexec(&fbregex, buffer, nmatch, pmatch, 0) == 0) {
                    plantptr->branches[i].plantptr = NULL;
                    plantptr->branches[i].thickness = atoi(buffer + pmatch[1].rm_so);
                    plantptr->energy = 1;
                }
                else {
                    regexec(&bregex, buffer, nmatch, pmatch, 0);
                    plantptr->branches[i].plantptr = plants + atoi(buffer + pmatch[1].rm_so);
                    plantptr->branches[i].thickness = atoi(buffer + pmatch[2].rm_so);
                }
                fgetsret = myfgets(buffer, BUFLEN, fp);
                i++;
            }
            plantptr->nbranches = i;
            fgetsret = myfgets(buffer, BUFLEN, fp);
        }

        fclose(fp);
        regfree(&pregex);
        regfree(&fbregex);
        regfree(&bregex);
    }

    int energy = 0;
    for (int p = 1; p <= nplants; p++) {
        Plant *plantptr = plants + p;
        if (plantptr->energy == 0) {
            energy = 0;
            for (int b = 0; b < plantptr->nbranches; b++) {
                Branch *branchptr = plantptr->branches + b;
                energy += branchptr->plantptr->energy * branchptr->thickness;
            }
            if (energy >= plantptr->thickness)
                plantptr->energy = energy;
        }
    }

    printf("%i\n", energy);

    exit(0);
}

