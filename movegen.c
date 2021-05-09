#include <stdio.h>
#include "defs.h"

void addQuietMove( const S_BOARD *pos, int move, S_MOVELIST *list ) {
	list->moves[list->count].move = move;
	list->moves[list->count].score = 0;
	list->count++;
}

void addCaptureMove( const S_BOARD *pos, int move, S_MOVELIST *list ) {
	list->moves[list->count].move = move;
	list->moves[list->count].score = 0;
	list->count++;
}

void addEnPassantMove( const S_BOARD *pos, int move, S_MOVELIST *list ) {
	list->moves[list->count].move = move;
	list->moves[list->count].score = 0;
	list->count++;
}

void generateAllMoves(const S_BOARD *pos, S_MOVELIST *list) {
	list->count = 0;
}