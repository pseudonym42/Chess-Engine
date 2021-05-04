#include <stdio.h>
#include <time.h>
#include "defs.h"
#include "stdlib.h"

#define FEN1 "8/3q4/8/8/4Q3/8/8/8 w - - 0 2 "
#define FEN2 "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2"
#define FEN3 "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2"
#define FEN4 "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"


int main(void) {

    // Random seed initialization, should only be called once
    srand(time(NULL));

    /* intialise default setup*/
    allInit();

	// S_BOARD board[1];
    // parseFEN(FEN1, board);
    // printBoard(board);
    // ASSERT(checkBoard(board));

    int move = 0;
	int from = A2;
    int to = H7;

	int cap = wR;
    int prom = wB;
	
	move = ( ( from ) | ( to << 7 ) | ( cap << 14 ) | ( prom << 20) );
			
	printf("from:%d to:%d cap:%d prom:%d\n",
		FROMSQ(move),TOSQ(move),CAPTURED(move),
		PROMOTED(move));
	
	printf("Algebraic from:%s\n",printSq(from));
	printf("Algebraic to:%s\n",printSq(to));
	printf("Algebraic move:%s\n",printMove(move));

    return 0;
}
