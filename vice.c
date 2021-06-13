#include <stdio.h>
#include <time.h>
#include "defs.h"
#include "stdlib.h"

#define WAC1 "r1b1k2r/ppppnppp/2n2q2/2b5/3NP3/2P1B3/PP3PPP/RN1QKB1R w KQkq - 0 1"


int main(void) {

    // Random seed initialization, should only be called once
    srand(time(NULL));

    /* intialise default setup*/
    allInit();

	S_BOARD board[1];
	InitPvTable(board->PvTable);
	S_MOVELIST list[1];
	S_SEARCHINFO info[1];
    parseFEN(WAC1, board);
	// PerftTest(3, board);


	char input[6];
	int Move = NOMOVE;
	while (1) {
		printBoard(board);
		printf("Please enter a move > ");
		fgets(input, 6, stdin);
		
		if (input[0]=='q') {
			break;
		} else if (input[0]=='t') {
			TakeMove(board);
		} else if (input[0]=='s') {
			info->depth = 6;
			SearchPosition(board, info);	
		} else {
			Move = ParseMove(input, board);
			if (Move != NOMOVE) {
				StorePvMove(board, Move);
				MakeMove(board, Move);
			} else {
				printf("Move Not Parsed: %s\n",input);
			}
		}
		fflush(stdin);
	}

	free(board->PvTable->pTable);

    return 0;
}
