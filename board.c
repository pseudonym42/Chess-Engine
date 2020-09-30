#include <stdio.h>
#include "defs.h"



void UpdateListsMaterial(S_BOARD *pos) {

    int piece,
        sq,
        index,
        colour;

    for (index = 0; index < BRD_SQ_NUM; ++index) {
        sq = index;
        piece = pos->pieces[index];
        if (piece!=OFFBOARD && piece!= EMPTY) {
            colour = PieceCol[piece];

            if ( PieceBig[piece] == true) pos->bigPce[colour]++;
            if ( PieceMin[piece] == true) pos->minPce[colour]++;
            if ( PieceMaj[piece] == true) pos->majPce[colour]++;

            pos->material[colour] += PieceVal[piece];

            // piece list
            // pList[wP][0] = a1;
            // pList[wP][1] = a2;

            pos->pList[piece][pos->pceNum[piece]] = sq;
            pos->pceNum[piece]++;

            if (piece==wK) pos->KingSq[WHITE] = sq;
            if (piece==bK) pos->KingSq[BLACK] = sq;
        }
    }
}


int parseFEN (char *fen, S_BOARD *pos) {
    ASSERT(fen!=NULL);
    ASSERT(pos!=NULL);

    int  rank = RANK_8,
         file = FILE_A,
         piece = 0,
         count = 0,
         i = 0,
         sq64 = 0,
         sq120 = 0;

    resetBoard(pos);

    /*
        This loop will iterate over FEN until it hits
        the last RANK (row on a chess board)
    */
    while ((rank >= RANK_1) && *fen) {
        count = 1;
        switch (*fen) {
            case 'p': piece = bP; break;
            case 'r': piece = bR; break;
            case 'n': piece = bN; break;
            case 'b': piece = bB; break;
            case 'k': piece = bK; break;
            case 'q': piece = bQ; break;
            case 'P': piece = wP; break;
            case 'R': piece = wR; break;
            case 'N': piece = wN; break;
            case 'B': piece = wB; break;
            case 'K': piece = wK; break;
            case 'Q': piece = wQ; break;

            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
                piece = EMPTY;
                /*
                    here we are using this hack to convert a char
                    representing a number e.g. '5' to an int, for
                    example: '5' - '0' would return an int 5

                    This works as each char can be represented as
                    an integer so difference between them is an
                    integer number
                */
                count = *fen - '0';
                break;

            case '/':
            case ' ':
                rank--;
                file = FILE_A;
                fen++;
                continue;

            default:
                printf("FEN error \n");
                return -1;
        }

        /*
            This loop sets the given piece which we just
            read in the above switch statement in the right
            place on the board S_BOARD

            Note that in cases when piece is EMPTY then count
            value would be larger that 1, so in this case there
            will be multiple iterations done by this loop and we
            will jump multiple empty squares by doing file++
        */
        for (i = 0; i < count; i++) {
            sq64 = rank * 8 + file; /* get the square sequence number */
            sq120 = Sq64ToSq120[sq64];
            if (piece != EMPTY) {
                pos->pieces[sq120] = piece;
            }
            file++;
        }
        fen++;
    }

    /*
        Now that iteration over RANKs is complete we
        got to the point where we process the rest of
        the FEN, first we process side
    */
    ASSERT(*fen == 'w' || *fen == 'b');
    if (*fen == 'w') {
        pos->side = WHITE;
    } else {
        pos->side = BLACK;
    }
    fen += 2; /* move to castling section of FEN */

    /*
        Process FEN castling section which has 4 chars,
        note how we use bitwise OR
    */
    for (i = 0; i < 4; i++) {
        if (*fen == ' ') {
            break;
        }
        switch(*fen) {
            case 'K': pos->castlePerm |= WKCA; break;
            case 'Q': pos->castlePerm |= WQCA; break;
            case 'k': pos->castlePerm |= BKCA; break;
            case 'q': pos->castlePerm |= BQCA; break;
            default: break;
        }
        fen++;
    }
    fen++;
    ASSERT(pos->castlePerm>=0 && pos->castlePerm <= 15);

    /*
        Process en passant square; if we are not
        pointing at a dash '-' that means we have
        en passant
    */
    if (*fen != '-') {
        file = fen[0] - 'a';
        rank = fen[1] - '1';

        ASSERT(file>=FILE_A && file <= FILE_H);
        ASSERT(rank>=RANK_1 && rank <= RANK_8);

        pos->enPas = FR2SQ(file, rank);
    }

    pos->posKey = generatePosKey(pos);


    return 0;
}


void resetBoard (S_BOARD *pos) {
    int index = 0;

    for(index = 0; index < BRD_SQ_NUM; ++index) {
        pos->pieces[index] = OFFBOARD;
    }

    for(index = 0; index < 64; ++index) {
        pos->pieces[Sq64ToSq120[index]] = EMPTY;
    }

    for (index = 0; index < 2; ++index) {
        pos->bigPce[index] = 0;
        pos->majPce[index] = 0;
        pos->minPce[index] = 0;
        pos->pawns[index] = 0ULL;
    }

    for(index = 0; index < 13; ++index) {
        pos->pceNum[index] = 0;
    }

    pos->KingSq[WHITE] = pos->KingSq[BLACK] = NO_SQ;
    pos->side = BOTH;
    pos->enPas = NO_SQ;
    pos->fiftyMove = 0;
    pos->ply = 0;
    pos->hisPly = 0;
    pos->castlePerm = 0;
    pos->posKey = 0ULL;
}

void printBoard(const S_BOARD *pos) {

    int sq, file, rank, piece;
    printf("\nGame Board:\n\n");

    for (rank = RANK_8; rank >= RANK_1; rank--) {
        printf("%d  ", rank + 1);
        for (file = FILE_A; file <= FILE_H; file++) {
            sq = FR2SQ(file, rank);
            piece = pos->pieces[sq];
            printf("%3c", PceChar[piece]);
        }
        printf("\n");
    }

    printf("\n   ");
    for (file = FILE_A; file <= FILE_H; file++) {
        /*
            'a' + 0 --> 'a'
            'a' + 1 --> 'b'
            etc
        */
        printf("%3c", 'a' + file);
    }
    printf("\n");
    printf("side:%c\n", SideChar[pos->side]);
    printf("enPas:%d\n", pos->enPas);
    printf(
        "castle:%c%c%c%c\n",
        pos->castlePerm & WKCA ? 'K' : '-',
        pos->castlePerm & WQCA ? 'Q' : '-',
        pos->castlePerm & BKCA ? 'k' : '-',
        pos->castlePerm & BQCA ? 'q' : '-'
    );
    printf("PosKey:%llX\n", pos->posKey);
}
