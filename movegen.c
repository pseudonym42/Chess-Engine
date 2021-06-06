#include <stdio.h>
#include "defs.h"

#define MOVE(f,t,ca,pro,fl) ( (f) | ((t) << 7) | ( (ca) << 14 ) | ( (pro) << 20 ) | (fl))

#define SQOFFBOARD(sq) (FilesBrd[(sq)]==OFFBOARD)

const int LoopSlidePce[8] = {
	wB, wR, wQ, 0, bB, bR, bQ, 0
};

const int LoopNonSlidePce[6] = {
	wN, wK, 0, bN, bK, 0
};

const int LoopSlideIndex[2] = { 0, 4 };
const int LoopNonSlideIndex[2] = { 0, 3 };

/*
	This and the NumDir array are related. Look
	at the description of the NumDir array. Now
	you can see that nested arrays of directions
	here are zero'ed out as well for the same pieces

	This array indicates relative number of a square
	on which a piece could potentially move

	So if you look at the inner board

		+-----+-----+-----+-----+-----+-----+-----+-----+
		|  21 |  XX |  23 |  XX |  25 |  26 |  27 |  28 |
		+-----+-----+-----+-----+-----+-----+-----+-----+
		|  XX |  32 |  33 |  34 |  XX |  36 |  37 |  38 |
		+-----+-----+-----+-----+-----+-----+-----+-----+
		|  41 |  42 |  !! |  44 |  45 |  46 |  47 |  48 |
		+-----+-----+-----+-----+-----+-----+-----+-----+
		|  XX |  52 |  53 |  54 |  XX |  56 |  57 |  58 |
		+-----+-----+-----+-----+-----+-----+-----+-----+
		|  61 |  XX |  63 |  XX |  65 |  66 |  67 |  68 |
		+-----+-----+-----+-----+-----+-----+-----+-----+
		|  71 |  72 |  73 |  74 |  75 |  76 |  77 |  78 |
		+-----+-----+-----+-----+-----+-----+-----+-----+
		|  81 |  82 |  83 |  84 |  85 |  86 |  87 |  88 |
		+-----+-----+-----+-----+-----+-----+-----+-----+
		|  91 |  92 |  93 |  94 |  95 |  96 |  97 |  98 |
		+-----+-----+-----+-----+-----+-----+-----+-----+

	And let's say we have a white knight i.e. wN, then the
	potential moves are designated with XX. The numbers of
	those square can be calculated from the current square
	(i.e. where the wN is lcoated) by adding the below numbers
	from the corresponding nested array
*/
const int PceDir[13][8] = {
	{ 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0 },
	{ -8, -19,	-21, -12, 8, 19, 21, 12 },
	{ -9, -11, 11, 9, 0, 0, 0, 0 },
	{ -1, -10,	1, 10, 0, 0, 0, 0 },
	{ -1, -10,	1, 10, -9, -11, 11, 9 },
	{ -1, -10,	1, 10, -9, -11, 11, 9 },
	{ 0, 0, 0, 0, 0, 0, 0 },
	{ -8, -19,	-21, -12, 8, 19, 21, 12 },
	{ -9, -11, 11, 9, 0, 0, 0, 0 },
	{ -1, -10,	1, 10, 0, 0, 0, 0 },
	{ -1, -10,	1, 10, -9, -11, 11, 9 },
	{ -1, -10,	1, 10, -9, -11, 11, 9 }
};

/* 
	This array indicates the number of directions for each
	piece, note that it matches the list of pieces from the
	`defs.h` module i.e. 

		EMPTY, wP, wN, wB, wR ...
	
	Note that the zeros are for EMPTY, wP ans bP as this array
	is not used for them
*/
const int NumDir[13] = {
	0, 0, 8, 4, 4, 8, 8, 0, 8, 4, 4, 8, 8
};

int MoveExists(S_BOARD *pos, const int move) {
	
	S_MOVELIST list[1];
    generateAllMoves(pos, list);
      
    int MoveNum = 0;
	for(MoveNum = 0; MoveNum < list->count; ++MoveNum) {	
       
        if (!MakeMove(pos,list->moves[MoveNum].move))  {
            continue;
        }        
        TakeMove(pos);
		if (list->moves[MoveNum].move == move) {
			return true;
		}
    }
	return false;
}

static void addQuietMove(const S_BOARD *pos, int move, S_MOVELIST *list) {
	list->moves[list->count].move = move;
	list->moves[list->count].score = 0;
	list->count++;
}

static void addCaptureMove(const S_BOARD *pos, int move, S_MOVELIST *list) {
	list->moves[list->count].move = move;
	list->moves[list->count].score = 0;
	list->count++;
}

static void addEnPassantMove(const S_BOARD *pos, int move, S_MOVELIST *list) {
	list->moves[list->count].move = move;
	list->moves[list->count].score = 0;
	list->count++;
}

static void addWhitePawnCapMove(const S_BOARD *pos, const int from, const int to, const int cap, S_MOVELIST *list) {
	ASSERT(pieceValidEmpty(cap));
	ASSERT(sqOnBoard(from));
	ASSERT(sqOnBoard(to));

	if(RanksBrd[from] == RANK_7) {
		addCaptureMove(pos, MOVE(from,to,cap,wQ,0), list);
		addCaptureMove(pos, MOVE(from,to,cap,wR,0), list);
		addCaptureMove(pos, MOVE(from,to,cap,wB,0), list);
		addCaptureMove(pos, MOVE(from,to,cap,wN,0), list);
	} else {
		addCaptureMove(pos, MOVE(from,to,cap,EMPTY,0), list);
	}
}

static void addWhitePawnMove(const S_BOARD *pos, const int from, const int to, S_MOVELIST *list) {
	ASSERT(sqOnBoard(from));
	ASSERT(sqOnBoard(to));

	if(RanksBrd[from] == RANK_7) {
		addQuietMove(pos, MOVE(from,to,EMPTY,wQ,0), list);
		addQuietMove(pos, MOVE(from,to,EMPTY,wR,0), list);
		addQuietMove(pos, MOVE(from,to,EMPTY,wB,0), list);
		addQuietMove(pos, MOVE(from,to,EMPTY,wN,0), list);
	} else {
		addQuietMove(pos, MOVE(from,to,EMPTY,EMPTY,0), list);
	}
}

static void addBlackPawnCapMove( const S_BOARD *pos, const int from, const int to, const int cap, S_MOVELIST *list ) {
	ASSERT(pieceValidEmpty(cap));
	ASSERT(sqOnBoard(from));
	ASSERT(sqOnBoard(to));

	if(RanksBrd[from] == RANK_2) {
		addCaptureMove(pos, MOVE(from,to,cap,bQ,0), list);
		addCaptureMove(pos, MOVE(from,to,cap,bR,0), list);
		addCaptureMove(pos, MOVE(from,to,cap,bB,0), list);
		addCaptureMove(pos, MOVE(from,to,cap,bN,0), list);
	} else {
		addCaptureMove(pos, MOVE(from,to,cap,EMPTY,0), list);
	}
}

static void addBlackPawnMove( const S_BOARD *pos, const int from, const int to, S_MOVELIST *list ) {
	ASSERT(sqOnBoard(from));
	ASSERT(sqOnBoard(to));

	if(RanksBrd[from] == RANK_2) {
		addQuietMove(pos, MOVE(from,to,EMPTY,bQ,0), list);
		addQuietMove(pos, MOVE(from,to,EMPTY,bR,0), list);
		addQuietMove(pos, MOVE(from,to,EMPTY,bB,0), list);
		addQuietMove(pos, MOVE(from,to,EMPTY,bN,0), list);
	} else {
		addQuietMove(pos, MOVE(from,to,EMPTY,EMPTY,0), list);
	}
}

void generateAllMoves(const S_BOARD *pos, S_MOVELIST *list) {
	ASSERT(checkBoard(pos));
	list->count = 0;	
	
	int pce = EMPTY;
	int side = pos->side;
	int sq = 0;
	int target_sq = 0;
	int pceNum = 0;
	int dir = 0; // direction
	int index = 0;
	int pceIndex = 0;
	
	if(side == WHITE) {
		for(pceNum = 0; pceNum < pos->pceNum[wP]; ++pceNum) {
			sq = pos->pList[wP][pceNum];
			ASSERT(sqOnBoard(sq));
			
			if(pos->pieces[sq + 10] == EMPTY) {
				addWhitePawnMove(pos, sq, sq+10, list);
				if(RanksBrd[sq] == RANK_2 && pos->pieces[sq + 20] == EMPTY) {
					addQuietMove(pos, MOVE(sq,(sq+20),EMPTY,EMPTY,MFLAGPS),list);
				}
			} 
			
			if(!SQOFFBOARD(sq + 9) && PieceCol[pos->pieces[sq + 9]] == BLACK) {
				addWhitePawnCapMove(pos, sq, sq+9, pos->pieces[sq + 9], list);
			}  
			if(!SQOFFBOARD(sq + 11) && PieceCol[pos->pieces[sq + 11]] == BLACK) {
				addWhitePawnCapMove(pos, sq, sq+11, pos->pieces[sq + 11], list);
			} 
			
			if(sq + 9 == pos->enPas) {
				addCaptureMove(pos, MOVE(sq,sq + 9,EMPTY,EMPTY,MFLAGEP), list);
			} 
			if(sq + 11 == pos->enPas) {
				addCaptureMove(pos, MOVE(sq,sq + 11,EMPTY,EMPTY,MFLAGEP), list);
			}	
		}

		if (pos->castlePerm & WKCA) {
			if (pos->pieces[F1] == EMPTY && pos->pieces[G1] == EMPTY) {
				if (!squareAttacked(E1,BLACK,pos) && !squareAttacked(F1,BLACK,pos) ) {
					addQuietMove(pos, MOVE(E1, G1, EMPTY, EMPTY, MFLAGCA), list);
				}
			}
		}
		
		if (pos->castlePerm & WQCA) {
			if (pos->pieces[D1] == EMPTY && pos->pieces[C1] == EMPTY && pos->pieces[B1] == EMPTY) {
				if (!squareAttacked(E1,BLACK,pos) && !squareAttacked(D1,BLACK,pos) ) {
					addQuietMove(pos, MOVE(E1, C1, EMPTY, EMPTY, MFLAGCA), list);
				}
			}
		}

	} else {
		for(pceNum = 0; pceNum < pos->pceNum[bP]; ++pceNum) {
			sq = pos->pList[bP][pceNum];
			ASSERT(sqOnBoard(sq));
			
			if(pos->pieces[sq - 10] == EMPTY) {
				addBlackPawnMove(pos, sq, sq-10, list);
				if(RanksBrd[sq] == RANK_7 && pos->pieces[sq - 20] == EMPTY) {
					addQuietMove(pos, MOVE(sq,(sq-20),EMPTY,EMPTY,MFLAGPS),list);
				}
			} 
			
			if(!SQOFFBOARD(sq - 9) && PieceCol[pos->pieces[sq - 9]] == WHITE) {
				addBlackPawnCapMove(pos, sq, sq-9, pos->pieces[sq - 9], list);
			} 
			
			if(!SQOFFBOARD(sq - 11) && PieceCol[pos->pieces[sq - 11]] == WHITE) {
				addBlackPawnCapMove(pos, sq, sq-11, pos->pieces[sq - 11], list);
			} 
			
			if(sq - 9 == pos->enPas) {
				addCaptureMove(pos, MOVE(sq,sq - 9,EMPTY,EMPTY,MFLAGEP), list);
			} 
			if(sq - 11 == pos->enPas) {
				addCaptureMove(pos, MOVE(sq,sq - 11,EMPTY,EMPTY,MFLAGEP), list);
			}
		}

		if (pos->castlePerm & BKCA) {
			if (pos->pieces[F8] == EMPTY && pos->pieces[G8] == EMPTY) {
				if (!squareAttacked(E8,WHITE,pos) && !squareAttacked(F8,WHITE,pos) ) {
					addQuietMove(pos, MOVE(E8, G8, EMPTY, EMPTY, MFLAGCA), list);
				}
			}
		}
		
		if (pos->castlePerm & BQCA) {
			if (pos->pieces[D8] == EMPTY && pos->pieces[C8] == EMPTY && pos->pieces[B8] == EMPTY) {
				if (!squareAttacked(E8,WHITE,pos) && !squareAttacked(D8,WHITE,pos) ) {
					addQuietMove(pos, MOVE(E8, C8, EMPTY, EMPTY, MFLAGCA), list);
				}
			}
		}
	}

	/* Sliding pieces */
	pceIndex = LoopSlideIndex[side];
	pce = LoopSlidePce[pceIndex];
	pceIndex++;
	while (pce != 0) {
		ASSERT(pieceValid(pce));

		for(pceNum = 0; pceNum < pos->pceNum[pce]; ++pceNum) {
			sq = pos->pList[pce][pceNum];
			ASSERT(sqOnBoard(sq));
			
			for (index = 0; index < NumDir[pce]; ++index) {
				dir = PceDir[pce][index];
				target_sq = sq + dir;
				
				while (!SQOFFBOARD(target_sq)) {				
					// BLACK ^ 1 == WHITE
					// WHITE ^ 1 == BLACK
					if (pos->pieces[target_sq] != EMPTY) {
						if (PieceCol[pos->pieces[target_sq]] == side ^ 1) {
							addCaptureMove(pos, MOVE(sq, target_sq, pos->pieces[target_sq], EMPTY, 0), list);
						}
						break;
					}	
					addQuietMove(pos, MOVE(sq, target_sq, EMPTY, EMPTY, 0), list);
					target_sq += dir;
				}
			}
		}
		pce = LoopSlidePce[pceIndex++];
	}

	/* Non-sliding pieces */
	pceIndex = LoopNonSlideIndex[side];
	pce = LoopNonSlidePce[pceIndex];
	pceIndex++;
	while (pce != 0) {
		ASSERT(pieceValid(pce));

		for (pceNum = 0; pceNum < pos->pceNum[pce]; ++pceNum) {
			sq = pos->pList[pce][pceNum];
			ASSERT(sqOnBoard(sq));
			
			for (index = 0; index < NumDir[pce]; ++index) {
				dir = PceDir[pce][index];
				target_sq = sq + dir;
				
				if (SQOFFBOARD(target_sq)) {				    
					continue;
				}
				
				// BLACK ^ 1 == WHITE
				// WHITE ^ 1 == BLACK
				if (pos->pieces[target_sq] != EMPTY) {
					if (PieceCol[pos->pieces[target_sq]] == side ^ 1) {
						addCaptureMove(pos, MOVE(sq, target_sq, pos->pieces[target_sq], EMPTY, 0), list);
					}
					continue;
				}	
				addQuietMove(pos, MOVE(sq, target_sq, EMPTY, EMPTY, 0), list);
			}
		}
		pce = LoopNonSlidePce[pceIndex++];
	}	
}