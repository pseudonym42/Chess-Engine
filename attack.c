#include <stdio.h>
#include "defs.h"

/*
    Logic in this module is used to check if for
    a given square there are any pieces which can
    attack the square

    For example on this board:

    +-----+-----+-----+-----+-----+-----+-----+-----+
    |  21 |  22 |  23 |  24 |  25 |  26 |  27 |  28 |
    +-----+-----+-----+-----+-----+-----+-----+-----+
    |  31 |  32 |  33 |  34 |  35 |  36 |  37 |  38 |
    +-----+-----+-----+-----+-----+-----+-----+-----+
    |  41 |  42 |  43 |  44 |  45 |  46 |  47 |  48 |
    +-----+-----+-----+-----+-----+-----+-----+-----+
    |  51 |  52 |  53 |  54 |  55 |  56 |  57 |  58 |
    +-----+-----+-----+-----+-----+-----+-----+-----+
    |  61 |  62 |  63 |  64 |  65 |  66 |  67 |  68 |
    +-----+-----+-----+-----+-----+-----+-----+-----+
    |  71 |  72 |  73 |  74 |  75 |  76 |  77 |  78 |
    +-----+-----+-----+-----+-----+-----+-----+-----+
    |  81 |  82 |  83 |  84 |  85 |  86 |  87 |  88 |
    +-----+-----+-----+-----+-----+-----+-----+-----+
    |  91 |  92 |  93 |  94 |  95 |  96 |  97 |  98 |
    +-----+-----+-----+-----+-----+-----+-----+-----+

    If we take square 55 as an example then potentially
    it can be attacked by:

        1) pawns from 44/46 or 64/66 depending on the side
        2) bishops or queens from 22, 33, 44, 66, 77, 88,
                                  46, 37, 28, 64, 73, 82, 91
        3) rooks or queens from 25, 35, 45, 65, 75, 85, 95,
                                51, 52, 53, 54, 56, 57, 58
        4) knights from 43, 34, 36, 47, 67, 76, 74, 63
*/


/*
    These are arrays representing Knight, Rook, Bishop
    and King attack directions

    From the above examplary board one can see certain patterns.
    For example, a location of a rook which could attack a piece
    could be calculated via adding/substracting 1 or 10:

        25 = 55 - 3*10
        35 = 55 - 2*10
        ..
        85 = 55 + 3*10

        or

        51 = 55 - 4*1
        ..
        58 = 55 + 3*1

    The below arrays a constructed and hardcoded based on the
    above logic
*/
const int KnDir[8] = { -8, -19, -21, -12, 8, 19, 21, 12 };
const int RkDir[4] = { -1, -10, 1, 10 };
const int BiDir[4] = { -9, -11, 11, 9 };
const int KiDir[8] = { -1, -10, 1, 10, -9, -11, 11, 9 };

/* Identifies whether a given square is under attack

    sq     square which is being attacked
    side   attacking side
    pos    position
*/
int squareAttacked(const int sq, const int side, const S_BOARD *pos) {

    int pce,
        index,
        t_sq,
        dir;

    ASSERT(sqOnBoard(sq));
	ASSERT(sideValid(side));
	ASSERT(checkBoard(pos));

    // check pawn attacks
    if (side == WHITE) {
        if (pos->pieces[sq-11] == wP || pos->pieces[sq-9] == wP) {
            return true;
        }
    } else {
        if (pos->pieces[sq+11] == bP || pos->pieces[sq+9] == bP) {
            return true;
        }
    }

    // knights attacks
    for (index = 0; index < 8; ++index) {
        pce = pos->pieces[sq + KnDir[index]];
        if (pce != OFFBOARD && IsKn(pce) && PieceCol[pce]==side) {
            return true;
        }
    }

    // rooks and queens attacks
    for (index = 0; index < 4; ++index) {
        dir = RkDir[index];
        t_sq = sq + dir;
        pce = pos->pieces[t_sq];
        while (pce != OFFBOARD) {
            if (pce != EMPTY) {
                if (IsRQ(pce) && PieceCol[pce] == side) {
                    return true;
                }
                break;
            }
            t_sq += dir;
            pce = pos->pieces[t_sq];
        }
    }

    // bishops and queens attacks
    for (index = 0; index < 4; ++index) {
        dir = BiDir[index];
        t_sq = sq + dir;
        pce = pos->pieces[t_sq];
        while (pce != OFFBOARD) {
            if (pce != EMPTY) {
                if (IsBQ(pce) && PieceCol[pce] == side) {
                    return true;
                }
                break;
            }
            t_sq += dir;
            pce = pos->pieces[t_sq];
        }
    }

    // kings attacks
    for (index = 0; index < 8; ++index) {
        pce = pos->pieces[sq + KiDir[index]];
        if (pce != OFFBOARD && IsKi(pce) && PieceCol[pce]==side) {
            return true;
        }
    }

    return false;
}
