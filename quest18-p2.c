#include <stdlib.h>
#include <stdio.h>
#include <regex.h>
#include <string.h>
#include "misc.h"

#define MAXBRANCH   20
#define MAXPLANTS   40
#define BUFLEN      50

typedef struct Plant Plant;

typedef struct {
    Plant *plantptr;
    int thickness;
} Branch;

struct Plant {
    int thickness, nbranches;
    long long energy;
    Branch branches[MAXBRANCH];
};



int main()
{
    Plant plants[MAXPLANTS];
    int nplants = 0;

    char buffer[BUFLEN];
    FILE *fp = fopen("inputs/everybody_codes_e2025_q18_p2.txt", "r");
    char *fgetsret;

    {
        regex_t pregex, fbregex, bregex;
        char ppattern[]  = "Plant ([0-9]+) with thickness (-?[0-9]+):";
        char fbpattern[] = "free branch with thickness (-?[0-9]+)";
        char bpattern[]  = "branch to Plant ([0-9]+) with thickness (-?[0-9]+)";

        int nmatch = 5;
        regmatch_t pmatch[nmatch];

        regcomp(&pregex,  ppattern,  REG_EXTENDED);
        regcomp(&fbregex, fbpattern, REG_EXTENDED);
        regcomp(&bregex,  bpattern,  REG_EXTENDED);

        fgetsret = myfgets(buffer, BUFLEN, fp);
        while ((fgetsret != NULL) && (strlen(buffer) != 0)) {
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
        regfree(&pregex);
        regfree(&fbregex);
        regfree(&bregex);
    }

    long long sum = 0;
    fgetsret = myfgets(buffer, BUFLEN, fp);
    while (fgetsret != NULL) {
        char *token = strtok(buffer, " ");
        int p = 1;

        while (token) {
            plants[p].energy = *token - '0';
            p++;
            token = strtok(NULL, " ");
        }

        int energy = 0;
        for (; p <= nplants; p++) {
            Plant *plantptr = plants + p;
            plantptr->energy = 0;
            energy = 0;
            for (int b = 0; b < plantptr->nbranches; b++) {
                Branch *branchptr = plantptr->branches + b;
                energy += branchptr->plantptr->energy * branchptr->thickness;
            }
            if (energy >= plantptr->thickness)
                plantptr->energy = energy;
        }

        sum += plants[nplants].energy;
        fgetsret = myfgets(buffer, BUFLEN, fp);
    }

    fclose(fp);
    printf("%lli\n", sum);
    exit(0);
}

