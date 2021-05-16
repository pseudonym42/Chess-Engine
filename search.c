#include <stdio.h>
#include "defs.h"

int IsRepetition(const S_BOARD *pos) {
	int index = 0;
	for (index = pos->hisPly - pos->fiftyMove; index < pos->hisPly-1; ++index) {
	
		ASSERT(index >= 0 && index < MAX_GAME_MOVES);
		if (pos->posKey == pos->history[index].posKey) {
			return true;
		}
	}
	
	return false;
}

void SearchPosition(S_BOARD *pos) {
	
}