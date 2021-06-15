#include <stdio.h>
#include <time.h>
#include "defs.h"
#include "stdlib.h"

#define WAC1 "r1b1k2r/ppppnppp/2n2q2/2b5/3NP3/2P1B3/PP3PPP/RN1QKB1R w KQkq - 0 1"
#define PERFT "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"

int main(void) {

    // Random seed initialization, should only be called once
    srand(time(NULL));

	allInit();

	S_BOARD pos[1];
    S_SEARCHINFO info[1];   
	pos->PvTable->pTable = NULL;
    InitPvTable(pos->PvTable);

	Uci_Loop(pos, info);
	free(pos->PvTable->pTable);
	return 0;
}
