#include <stdbool.h>
#include "defs.h"

int sqOnBoard(const int sq) {
	return FilesBrd[sq]==OFFBOARD ? false : true;
}

int sideValid(const int side) {
	return (side==WHITE || side == BLACK) ? true : false;
}

int fileRankValid(const int fr) {
	return (fr >= 0 && fr <= 7) ? true : false;
}

int pieceValidEmpty(const int pce) {
	return (pce >= EMPTY && pce <= bK) ? true : false;
}

int pieceValid(const int pce) {
	return (pce >= wP && pce <= bK) ? true : false;
}