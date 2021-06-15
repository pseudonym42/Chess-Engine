#include "stdio.h"
#include "defs.h"
#include "string.h"

int ThreeFoldRep(const S_BOARD *pos) {
	int i = 0, r = 0;
	for (i = 0; i < pos->hisPly; ++i) {
	    if (pos->history[i].posKey == pos->posKey) {
		    r++;
		}
	}
	return r;
}

int DrawMaterial(const S_BOARD *pos) {
    if (pos->pceNum[wP] || pos->pceNum[bP]) return false;
    if (pos->pceNum[wQ] || pos->pceNum[bQ] || pos->pceNum[wR] || pos->pceNum[bR]) return false;
    if (pos->pceNum[wB] > 1 || pos->pceNum[bB] > 1) {return false;}
    if (pos->pceNum[wN] > 1 || pos->pceNum[bN] > 1) {return false;}
    if (pos->pceNum[wN] && pos->pceNum[wB]) {return false;}
    if (pos->pceNum[bN] && pos->pceNum[bB]) {return false;}
    return true;
}

int checkresult(S_BOARD *pos) {

    if (pos->fiftyMove > 100) {
        printf("1/2-1/2 {fifty move rule (claimed by Vice)}\n");
        return true;
    }

    if (ThreeFoldRep(pos) >= 2) {
        printf("1/2-1/2 {3-fold repetition (claimed by Vice)}\n");
        return true;
    }
	
	if (DrawMaterial(pos) == true) {
        printf("1/2-1/2 {insufficient material (claimed by Vice)}\n");
        return true;
    }
	
	S_MOVELIST list[1];
    generateAllMoves(pos,list);
      
    int MoveNum = 0;
	int found = 0;
	for (MoveNum = 0; MoveNum < list->count; ++MoveNum) {
        if (!MakeMove(pos,list->moves[MoveNum].move)) {
            continue;
        }
        found++;
		TakeMove(pos);
		break;
    }
	
	if (found != 0) return false;

	int InCheck = squareAttacked(pos->KingSq[pos->side], pos->side^1, pos);
	
	if (InCheck == true) {
	    if (pos->side == WHITE) {
	        printf("0-1 {black mates (claimed by Vice)}\n");
            return true;
        } else {
	        printf("0-1 {white mates (claimed by Vice)}\n");
            return true;
        }
    } else {
        printf("\n1/2-1/2 {stalemate (claimed by Vice)}\n");
        return true;
    }
	return false;
}

void XBoard_Loop(S_BOARD *pos, S_SEARCHINFO *info) {
	
	setbuf(stdin, NULL);
    setbuf(stdout, NULL);
	
	int depth = -1, movestogo = 30, movetime = -1;
	int time = -1, inc = 0;                             
	int engineSide = BOTH;                    
	int timeLeft;                           
	int mps;    
	int move = NOMOVE;	
	int i, score;
	char inBuf[80], command[80];
	
	while (1) { 

		fflush(stdout);

		if (pos->side == engineSide) {  
			// think
		}

		fflush(stdout); 
	
		memset(&inBuf[0], 0, sizeof(inBuf));
		fflush(stdout);
		if (!fgets(inBuf, 80, stdin))
		continue;
    
		sscanf(inBuf, "%s", command);
    
		if (!strcmp(command, "quit")) { 
			break; 
		}
		
		if (!strcmp(command, "force")) { 
			engineSide = BOTH; 
			continue; 
		} 
		
		if (!strcmp(command, "protover")){
		    printf("feature ping=1 setboard=1 colors=0 usermove=1\n");      
		    printf("feature done=1\n");
		    continue;
		}
		
		if (!strcmp(command, "sd")) {
			sscanf(inBuf, "sd %d", &depth); 
			continue; 
		}
		
		if (!strcmp(command, "st")) {
			sscanf(inBuf, "st %d", &movetime); 
			continue; 
		}    
		
		if (!strcmp(command, "ping")) { 
			printf("pong%s\n", inBuf+4); 
			continue; 
		}
		
		if (!strcmp(command, "new")) { 
			engineSide = BLACK; 
			parseFEN(START_FEN, pos);
			depth = -1; 
			continue; 
		}
		
		if (!strcmp(command, "setboard")){
			engineSide = BOTH;  
			parseFEN(inBuf+9, pos); 
			continue; 
		}   		
		
		if (!strcmp(command, "go")) { 
			engineSide = pos->side;  
			continue; 
		}		
		  
		if (!strcmp(command, "usermove")){
			move = ParseMove(inBuf+9, pos);	
			if (move == NOMOVE) continue;
			MakeMove(pos, move);
            pos->ply=0;
		}    
    }	
}