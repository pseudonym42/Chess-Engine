#include <stdio.h>
#include <time.h>
#include "defs.h"
#include "stdlib.h"


int main(void) {

    // Random seed initialization, should only be called once
    srand(time(NULL));

    /* intialise default setup*/
    allInit();

	S_BOARD board[1];
	S_MOVELIST list[1];
    parseFEN(START_FEN, board);
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
		} else if (input[0]=='p') {
			PerftTest(4, board);		
		} else {
			Move = ParseMove(input, board);
			if (Move != NOMOVE) {
				MakeMove(board,Move);
				/* if(IsRepetition(board)) {
					printf("REP SEEN\n");
				} */
			} else {
				printf("Move Not Parsed: %s\n",input);
			}
		}	
		
		fflush(stdin);
	}



    return 0;
}
