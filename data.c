#include "defs.h"


/*
    Note that this sequence matches:

        enum { EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK };

    from the defs.h file
*/
char PceChar[] = ".PNBRQKpnbrqk";

char SideChar[] = "wb-";
char RankChar[] = "12345678";
char FileChar[] = "abcdefgh";


/*

    These mappings help identify whther a piece is Big, Major, Minor
    and its value and colour

    The Big, Major, Minor mappings follow this:

        .PNBRQKpnbrqk

    This is the same as PceChar[] above. So for example the below
    PieceBig has 2 "false" which correcpond to empty (.) and white
    pawn (P) and then it has 5 "true" which correspond to white
    night (N), white bishop (B), white rook (R) etc

    The other arrays work by the the same principle

*/

// This identifies Big pieces as per
int PieceBig[13] = { false, false, true, true, true, true, true, false, true, true, true, true, true };
int PieceMaj[13] = { false, false, false, false, true, true, true, false, false, false, true, true, true };
int PieceMin[13] = { false, false, true, true, false, false, false, false, true, true, false, false, false };

/*
    This represents piece values. Follow the same set of chars as
    the PceChar[] above:

        .PNBRQKpnbrqk

    So empty (.) is 0, white pawn (P) is 100 etc

    Note that 50000 for the Kings is just a arbitrary large number as its
    value does not matter as it never gets captured

*/
int PieceVal[13]= { 0, 100, 325, 325, 550, 1000, 50000, 100, 325, 325, 550, 1000, 50000 };

/*
    This array matches .PNBRQKpnbrqk (both equal 13) and is used to
    identify a piece colour

*/
int PieceCol[13] = { BOTH, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK };

/*
    These 5 arrays below are simply used to identify whether a given piece
    is of certain type based on .PNBRQKpnbrqk
    For example:

        PieceKnight[wN] is going to return true
*/
int PiecePawn[13] = { false, true, false, false, false, false, false, true, false, false, false, false, false };	
int PieceKnight[13] = { false, false, true, false, false, false, false, false, true, false, false, false, false };
int PieceKing[13] = { false, false, false, false, false, false, true, false, false, false, false, false, true };
int PieceRookQueen[13] = { false, false, false, false, true, true, false, false, false, false, true, true, false };
int PieceBishopQueen[13] = { false, false, false, true, false, true, false, false, false, true, false, true, false };

/*
    This array is for identifying whether a piece is a sliding piece i.e. Queen, Rook or Bishop

*/
int PieceSlides[13] = { false, false, false, true, true, true, false, false, false, true, true, true, false };

int Mirror64[64] = {
    56	,	57	,	58	,	59	,	60	,	61	,	62	,	63	,
    48	,	49	,	50	,	51	,	52	,	53	,	54	,	55	,
    40	,	41	,	42	,	43	,	44	,	45	,	46	,	47	,
    32	,	33	,	34	,	35	,	36	,	37	,	38	,	39	,
    24	,	25	,	26	,	27	,	28	,	29	,	30	,	31	,
    16	,	17	,	18	,	19	,	20	,	21	,	22	,	23	,
    8	,	9	,	10	,	11	,	12	,	13	,	14	,	15	,
    0	,	1	,	2	,	3	,	4	,	5	,	6	,	7
};