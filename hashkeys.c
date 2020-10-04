#include <stdio.h>
#include "defs.h"

/*
    This function is used to generate a hash for a
    given position on the board. It takes a pointer
    to position and extracts all the required info
    to create a unique hash
*/
U64 generatePosKey(const S_BOARD *pos) {

    int sq = 0;
    U64 finalKey = 0;
    int piece = EMPTY;

    /*
        Iterate over the whole board (120 board) and
        ignore squares which are empty or "no-square".

        If the square is neither of the above then that
        means it should contain a piece. Assert that
        the piece is valid piece otherwise we are going
        to be attempting access PieceKeys array element
        outside its bounds


        Now XOR the the final key with the existing hash
        for that square
    */
    for (sq = 0; sq < BRD_SQ_NUM; ++sq) {
        piece = pos->pieces[sq];
        if (piece!=NO_SQ && piece!=EMPTY && piece != OFFBOARD) {
            ASSERT(piece>=wP && piece<=bK);
            finalKey ^= PieceKeys[piece][sq];
        }
    }

    /* also XOR with side hash */
    if (pos->side == WHITE) {
        finalKey ^= SideKey;
    }

    /*
        Check if this position has en-passant

        if current position has no en-passant
        then boards enPas is set to NO_SQ, otherwise
        if the position has en-passant XOR it against
        finalKey as well

        Note that in the PieceKeys array location of
        the en-passant will be identified by pair:

            [EMPTY][<value of enPas on the board struct>]

        Board's enPas value is (from 0 to 119) the square
        on which en-passant occured. Indexing by EMPTY is
        also sensible as all other values would represent
        a piece
    */
    if (pos->enPas != NO_SQ) {
        ASSERT(pos->enPas>=0 && pos->enPas<BRD_SQ_NUM);
        finalKey ^= PieceKeys[EMPTY][pos->enPas];
    }

    /* Also XOR against permitted castling */
    ASSERT(pos->castlePerm>=0 && pos->castlePerm<=15);
    finalKey ^= CastleKeys[pos->castlePerm];

    return finalKey;
}
