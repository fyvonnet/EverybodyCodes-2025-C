CC=/usr/bin/gcc
CFLAGS = -O1 -Wall -g
LDFLAGS = -lm -g



all: \
	quest01-p1 quest01-p2 quest01-p3 \
	quest02-p1 quest02-p2 quest02-p3 quest02-p3-visu \
	quest03-p1 quest03-p2 quest03-p3 quest03-p1-tree quest03-p2-tree \
	quest04-p1 quest04-p2 quest04-p3 \
	quest05-p1 quest05-p2 quest05-p3



quest01-p1.o: quest01-p1.c misc.h

quest01-p2.o: quest01-p2.c misc.h

quest01-p3.o: quest01-p3.c misc.h

quest02-p1.o: quest02-p1.c misc.h

quest02-p2.o: quest02-p2.c misc.h

quest02-p3.o: quest02-p3.c misc.h

quest02-p3-visu.o: quest02-p3-visu.c misc.h

quest03-p1.o: quest03-p1.c misc.h

quest03-p1-tree.o: quest03-p1-tree.c misc.h redblacktree.h

quest03-p2.o: quest03-p2.c misc.h

quest03-p2-tree.o: quest03-p2-tree.c misc.h redblacktree.h

quest03-p3.o: quest03-p3.c misc.h

quest04-p1.o: quest04-p1.c misc.h

quest04-p2.o: quest04-p2.c misc.h

quest04-p3.o: quest04-p3.c misc.h

quest05-p1.o: quest05-p1.c misc.h

quest05-p2.o: quest05-p2.c misc.h

quest05-p3.o: quest05-p3.c misc.h



quest01-p1: quest01-p1.o misc.o

quest01-p2: quest01-p2.o misc.o

quest01-p3: quest01-p3.o misc.o

quest02-p1: quest02-p1.o misc.o

quest02-p2: quest02-p2.o misc.o

quest02-p3: quest02-p3.o misc.o

quest02-p3-visu: quest02-p3-visu.o misc.o

quest03-p1: quest03-p1.o misc.o

quest03-p1-tree: quest03-p1-tree.o misc.o redblacktree.o

quest03-p2: quest03-p2.o misc.o

quest03-p2-tree: quest03-p2-tree.o misc.o redblacktree.o

quest03-p3: quest03-p3.o misc.o

quest04-p1: quest04-p1.o misc.o

quest04-p2: quest04-p2.o misc.o

quest04-p3: quest04-p3.o misc.o

quest05-p1: quest05-p1.o misc.o

quest05-p2: quest05-p2.o misc.o

quest05-p3: quest05-p3.o misc.o

