#ifndef DEFS_H
#define DEFS_H

// this lib is required to allow using 'true' and 'false'
#include <stdbool.h>

typedef unsigned long long U64;

/*
    This is a custom assertion implementation which allows us
    to use ASSERT() macro.

    Be default this will make the code run in DEBUG mode, to
    disable DEBUG mode for production - comment out this line:
            #define DEBUG
    like this:
            // #define DEBUG
*/
#include "stdlib.h"
#define DEBUG
#ifndef DEBUG
#define ASSERT(n)
#else
#define ASSERT(n) \
if(!(n)) { \
printf("%s - Failed", #n); \
printf("On %s ",__DATE__); \
printf("At %s ",__TIME__); \
printf("In File %s ",__FILE__); \
printf("At Line %d\n",__LINE__); \
exit(1);}
#endif


#define NAME "ViceMirror 1.0"

/*
    This is the total number of squares on a board

    The board consists of an inner and hidden squares. The inner board is
    the normal 8x8 board, the hidden squares are the ones which are not
    visible to a user and are used for identifying valid moves

        +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
        |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |
        +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
        |  10 |  11 |  12 |  13 |  14 |  15 |  16 |  17 |  18 |  19 |
        +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
        |  20 |  21 |  22 |  23 |  24 |  25 |  26 |  27 |  28 |  29 |
        +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
        |  30 |  31 |  32 |  33 |  34 |  35 |  36 |  37 |  38 |  39 |
        +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
        |  40 |  41 |  42 |  43 |  44 |  45 |  46 |  47 |  48 |  49 |
        +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
        |  50 |  51 |  52 |  53 |  54 |  55 |  56 |  57 |  58 |  59 |
        +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
        |  60 |  61 |  62 |  63 |  64 |  65 |  66 |  67 |  68 |  69 |
        +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
        |  70 |  71 |  72 |  73 |  74 |  75 |  76 |  77 |  78 |  79 |
        +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
        |  80 |  81 |  82 |  83 |  84 |  85 |  86 |  87 |  88 |  89 |
        +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
        |  90 |  91 |  92 |  93 |  94 |  95 |  96 |  97 |  98 |  99 |
        +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
        | 100 | 101 | 102 | 103 | 104 | 105 | 106 | 107 | 108 | 109 |
        +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
        | 110 | 111 | 112 | 113 | 114 | 115 | 116 | 117 | 118 | 119 |
        +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
*/
#define BRD_SQ_NUM 120

// it is assumed that there could not be more that this number
// of half moves in a game
#define MAX_GAME_MOVES 2048

// max number of moves that can be in a given position
#define MAX_POSITION_MOVES 256

/*
    This struct allows to store data about each half move
    so we could store them in history and develop "undo move"
    functionality
*/

// https://en.wikipedia.org/wiki/Forsyth-Edwards_Notation
#define START_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

/*
    This enaum contains information about moves. `move` stores info about
    the move itself and `score` is used for moves ordering

    See "GAME MOVE" below which describes how moves are stored

*/
typedef struct {
	int move;
	int score;
} S_MOVE;

typedef struct {
	S_MOVE moves[MAX_POSITION_MOVES];
	int count;
} S_MOVELIST;

typedef struct {
    int move;
    int castlePerm;
    int enPas;
    int fiftyMove;

    U64 posKey;
} S_UNDO;

/*
    This enum represents King castling options

    Here, KCA stand for King side castling and QCA - queen side
    castling
*/
enum {
    WKCA = 1,
    WQCA = 2,
    BKCA = 4,
    BQCA = 8
};

/*
    This enum represents types of pieces which could be found on
    board squares, including EMPTY (13 options)
*/
enum { EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK };

/* This enum represents the columns of the board */
enum { FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NONE };

/* This enum represents the rows of the board */
enum { RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NONE };

enum { WHITE, BLACK, BOTH };

/* This enum represents board square values from BRD_SQ_NUM perspective */
enum {
    A1 = 21, B1, C1, D1, E1, F1, G1, H1,
    A2 = 31, B2, C2, D2, E2, F2, G2, H2,
    A3 = 41, B3, C3, D3, E3, F3, G3, H3,
    A4 = 51, B4, C4, D4, E4, F4, G4, H4,
    A5 = 61, B5, C5, D5, E5, F5, G5, H5,
    A6 = 71, B6, C6, D6, E6, F6, G6, H6,
    A7 = 81, B7, C7, D7, E7, F7, G7, H7,
    A8 = 91, B8, C8, D8, E8, F8, G8, H8,
    NO_SQ,
    OFFBOARD
};

/* Board is defined using this struct below */
typedef struct {

    /*
        this represents all of the board squares and pieces;
        each item in this array can be either

            * EMPTY
                or
            * OFFBOARD
                or
            * a piece e.g.: bB
    */
    int pieces[BRD_SQ_NUM];

    /*
        We are going to store an array of all of the pawns
        located on the board. There are going to be 3 items in
        this array, each item is going to be 64 bits int number.

        Each item is going to represent where on the inner board
        a pawn is located - as each bit in U64 is going to be either
        0 (no pawn) or 1 - pawn

        There are 3 items because we need "pawns data" for black,
        white and both
    */
    U64 pawns[3];

    // these are big pieces - non-pawn pieces, per colour
    int bigPce[2];

    // these are major pieces - rooks and queens, per colour
    int majPce[2];

    // these are minor pieces - bishops and nights, per colour
    int minPce[2];

    // "material" score i.e. the sum of piece values of each side,
    // for more info about piece scores see:
    // https://en.wikipedia.org/wiki/Chess_piece_relative_value
    int material[2];

    // on which squares the kings are located
    int KingSq[2];

    /*
        represents https://en.wikipedia.org/wiki/En_passant,
        this is going to represent a square on which en-passant
        occured for a given position on this board, value of this
        int is expected to be from 0 to 119
    */
    int enPas;

    // current side to move
    int side;

    // number of pieces (+ EMPTY) on the board by piece type
    int pceNum[13];

    // unique key that is generated for each position
    U64 posKey;

    // stores data about any completed or possible
    // castling, values are expected to be from 0 to
    // 15 as there could be 16 different combinations
    int castlePerm;

    // represents https://en.wikipedia.org/wiki/Fifty-move_rule
    // in our case it will be 100 - as we use half moves not full
    // moves
    int fiftyMove;

    // this is the number of half-moves
    int ply;

    // number of half-moves in the game, to determine repeating
    // moves so we could identify a draw
    int hisPly;

    // stores history of all the moves; can store upto
    // MAX_GAME_MOVES number of half moves
    S_UNDO history[MAX_GAME_MOVES];

    /*
        collection of all of the pieces on the board and their
        corresponding location

        The first index (13) represents a piece type, and the
        second (10) - max number of this particular piece that
        could be on the board, for example the max number of white
        rooks is 10 - i.e. 2 initial and 8 if all pawns upgraded to
        rooks

        This array also improves performace of a move generation
        by 20%

        For example, white knigts in the beginning of the game:
            pList[wN][1] = G1;
            pList[wN][2] = B1;
    */
    int pList[13][10];

} S_BOARD;

/* GLOBALS */
extern int Sq120ToSq64[BRD_SQ_NUM];
extern int Sq64ToSq120[64];
extern U64 SetMask[64];
extern U64 ClearMask[64];
extern U64 PieceKeys[13][120];
extern U64 SideKey;
extern U64 CastleKeys[16];
extern char PceChar[];
extern char SideChar[];
extern char RankChar[];
extern char FileChar[];

extern int PieceBig[13];
extern int PieceMaj[13];
extern int PieceMin[13];
extern int PieceVal[13];
extern int PieceCol[13];

extern int FilesBrd[BRD_SQ_NUM];
extern int RanksBrd[BRD_SQ_NUM];

extern int PieceKnight[13];
extern int PieceKing[13];
extern int PieceRookQueen[13];
extern int PieceBishopQueen[13];
extern int PieceSlides[13];

/*
    GAME MOVE 

    If you look at the aquare tables in this file and init.c you will
    see that number of available squares for moves located on the inner
    board are numbered from 21 to 98, which means we just need 7 bits
    to store info about from which square a piece moved and additional
    7 bits to which square a piece moved. This is because 98-21=76, so
    6 bits would not be enough as it maxes out to 63.

    The info which we need to store is shown below. We store:
        "From square" using 7 bits;

        "To square" using 7 bits;

        Captured piece using 4 bits, here 4 bits is enough
        as we have only 12 types of pieces (wP, wN ...) and to 
        represent them 4 bits is enough

        En Passant - 1 bit

        Pawn Start - 1 bit

        Type of piece promotion (if it happend, this applies to
        pawns only) - 4 bits, same as above re captured piece

        Castling - 1 bit

    0000 0000 0000 0000 0000 0111 1111 -> From square:    0x7F
    0000 0000 0000 0011 1111 1000 0000 -> To square:      >> 7, 0x7F
    0000 0000 0011 1100 0000 0000 0000 -> Captured piece: >> 14, 0xF
    0000 0000 0100 0000 0000 0000 0000 -> En Passant:     0x40000
    0000 0000 1000 0000 0000 0000 0000 -> Pawn Start:     0x80000
    0000 1111 0000 0000 0000 0000 0000 -> Promoted Piece: >> 20, 0xF
    0001 0000 0000 0000 0000 0000 0000 -> Castle:         0x1000000   

    The reason info is stored as explained above is this would help
    us get information about moves quickly and efficiently using bitwise
    operations and the macros listed below. If we stored the same data
    using `int`s for each section (i.e. int for "From square", int for
    "To square" etc) then it would a bit more difficult to process and
    understand it. Now we have a single large integer which can be
    represented in hex form to help us understand the details of a move

    Also note that the hex number on the right hand side of each section
    are used to describe the value in hex not decimal as it is easier
    to understand and visualise what bit are populated. The `>>` means 
    shift number of bits. For more details see https://youtu.be/N6yImiyzWpo

    So how would we use the macros now to get the data and how do we use
    the above matrix to store move info? Here's an example:

    int move = 0;  // we start at zero
	int from = 6;  // move was from square number 6
    int to = 12;   // move was to square number 12
	int cap = wR;  // during the move the white rook was captured
    int prom = bR; // the piece was promoted to black rook
	
    // so here's how you can create a move now
	move = ( ( from ) | ( to << 7 ) | ( cap << 14 ) | ( prom << 20) );

    // and here's how you can retreive it
	printf("from:%d to:%d cap:%d prom:%d\n",
		FROMSQ(move),
        TOSQ(move),
        CAPTURED(move),
		PROMOTED(move));

    Now the above will print you:

        from:6 to:12 cap:4 prom:10

    Note that to make it eaiser to create a move a corresponding macro was created
    which is defined in `movegen.c` module
*/

/*
    These are moves specific macros
*/
#define FROMSQ(m) ((m) & 0x7F)
#define TOSQ(m) (((m)>>7) & 0x7F)
#define CAPTURED(m) (((m)>>14) & 0xF)
#define PROMOTED(m) (((m)>>20) & 0xF)

/* These flags are used for bit shifting */
#define MFLAGEP 0x40000
#define MFLAGPS 0x80000
#define MFLAGCA 0x1000000
#define MFLAGCAP 0x7C000
#define MFLAGPROM 0xF00000


/* MACROS */

/*
    for a given file and rank gets the number of the square from
    the board
*/
#define FR2SQ(file, rank) ((21 + (file)) + ((rank) * 10))

/* macros for SetMask array to set a value of a given square to one */
#define SETBIT(bb, sq) ((bb) |= SetMask[(sq)])

/* macros for ClearMask array to set a value of a given square to zero */
#define CLRBIT(bb, sq) ((bb) &= ClearMask[(sq)])

/*
    these macroses help generating 64 bits long pseudo random numbers

    here RAND_15_BITS help generate random number with 15-bits
    "filled-in" and then we shift numbers to left to "compose"
    a 64 long number; last 4 digits are done using 0xf
*/
#define RAND_15_BITS() (rand() & 0x7fff)  /* ensure only 15-bits */
#define RAND_64 ( ((U64)RAND_15_BITS()) + \
                  ((U64)RAND_15_BITS() << 15) + \
                  ((U64)RAND_15_BITS() << 30) + \
                  ((U64)RAND_15_BITS() << 45) + \
                  (((U64)RAND_15_BITS() & 0xf) << 60)     )

#define IsBQ(p) (PieceBishopQueen[(p)])
#define IsRQ(p) (PieceRookQueen[(p)])
#define IsKn(p) (PieceKnight[(p)])
#define IsKi(p) (PieceKing[(p)])


/* FUNCTIONS */

/* init.c */
extern void allInit();

/* bitboards.c */
extern void printBitBoard(U64 bb);
extern void printfBinary(U64 number);
extern int popBit(U64 *bb);
extern int countBits(U64 bb);

/* hashkeys.c */
extern U64 generatePosKey(const S_BOARD *pos);

/* board.c */
extern void resetBoard(S_BOARD *pos);
extern void printBoard(const S_BOARD *pos);
extern void updateListsMaterial(S_BOARD *pos);
extern int parseFEN(char *fen, S_BOARD *pos);
extern int checkBoard(const S_BOARD *pos);

/* attack.c */
extern int squareAttacked(const int sq, const int side, const S_BOARD *pos);

/* io.c */
extern char *printMove(const int move);
extern char *printSq(const int sq);
extern void printMoveList(const S_MOVELIST *list);

//validate.c
extern int sqOnBoard(const int sq);
extern int sideValid(const int side);
extern int fileRankValid(const int fr);
extern int pieceValidEmpty(const int pce);
extern int pieceValid(const int pce);

// movegen.c
extern void generateAllMoves(const S_BOARD *pos, S_MOVELIST *list);






#endif
