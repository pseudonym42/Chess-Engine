#include <stdio.h>
#include "defs.h"


/*
    These are look-up arrays which are used to identify
    relations between squares on "real" and "user-facing"
    boards
*/
int Sq120ToSq64[BRD_SQ_NUM];
int Sq64ToSq120[64];

/*
    These mask arrays are wrapped by macros which allow
    setting a given square to zero or one, see corresponding
    macros in defs.h file
*/
U64 SetMask[64];
U64 ClearMask[64];

/*
    These arrays below are used to store hashes of positions

    Note that CastleKeys has 16 items. This is because there
    are 4 types of castling available (see defs.h):

        enum {
            WKCA = 1,
            WQCA = 2,
            BKCA = 4,
            BQCA = 8
        };

    Which means there could be 16 different combinations, that
    is 2^4 = 16.

*/
U64 PieceKeys[13][120];
U64 SideKey;
U64 CastleKeys[16];

/*
    These arrays help get file or rank number of square
    by square number
*/
int FilesBrd[BRD_SQ_NUM];
int RanksBrd[BRD_SQ_NUM];


/* Print binary representation of a U64 number */
void printfBinary(U64 number) {
    int shift_count, bit;

    for (shift_count = 63; shift_count >= 0; shift_count--) {
        bit = number >> shift_count;

        if (bit & 1)
            printf("1");
        else
            printf("0");
    }
    printf("\n");
}

/*
    Initilises arrays which are used for getting file
    and rank for a given square
*/
void initFilesRanksBrd() {
    int index = 0,
        file = FILE_A,
        rank = RANK_1,
        sq = A1;

    /* set everything to OFFBOARD initially */
    for (index = 0; index < BRD_SQ_NUM; ++index) {
        FilesBrd[index] = OFFBOARD;
        RanksBrd[index] = OFFBOARD;
    }

    for (rank = RANK_1; rank <= RANK_8; ++rank) {
        for (file = FILE_A; file <= FILE_H; ++file) {
            // get the square number from the combination
            // of the file and the rank
            sq = FR2SQ(file, rank);
            FilesBrd[sq] = file;
            RanksBrd[sq] = rank;
        }
    }
}


/*
    Before game starts, this function initialises a
    random hash to:
    1. represent which side move it is
    2. populate PieceKeys array with random numbers
    3. popuate CastleKeys array with random numbers
*/
void initHashKeys() {
    short unsigned int i, i2;

    for (i = 0; i < 13; ++i) {
        for (i2 = 0; i2 < 120; ++i2) {
            PieceKeys[i][i2] = RAND_64;
        }
    }

    SideKey = RAND_64;
    for (i = 0; i < 16; ++i) {
        CastleKeys[i] = RAND_64;
    }
}

/*
    Initialise masks, to know more about masks read this:

        https://stackoverflow.com/a/10493604

    In short: a mask defines which bits you want to keep,
    and which bits you want to clear.
*/
void initBitMasks() {
    int index = 0;

    for (index = 0; index < 64; index++) {
        SetMask[index] = 0ULL;
        ClearMask[index] = 0ULL;
    }

    for (index = 0; index < 64; index++) {
        SetMask[index] |= (1ULL << index);

        // invert the value of SetMask[index]
        // and assign it to ClearMask[index]
        ClearMask[index] = ~SetMask[index];
    }

    /*
        After the second loop the SetMask is
        going to look like this:

            00000....001  <--- 64 bits obviously
            00000....010
            00000....100
            ...
            10000....000

        And ClearMask will look like:

            11111....110
            11111....101
            11111....011
            ...
            01111....111

    */
}

void initLookUpArrays() {
    int index = 0;
    int file = FILE_A;
    int rank = RANK_1;

    int sq = A1;
    int sq64 = 0;

    /*
        set all the values in the Sq120ToSq64 array to 65, as 65 is not
        a valid value for Sq120ToSq64, which should only return values from
        0 to 63
    */
    for (index = 0; index < BRD_SQ_NUM; ++index) {
        Sq120ToSq64[index] = 65;
    }

    /*
        set all the values in the Sq64ToSq120 array to 120, as 120 is not
        a valid value for Sq64ToSq120, which should only return values from
        0 to 119
    */
    for (index = 0; index < 64; ++index) {
        Sq64ToSq120[index] = 120;
    }

    for (rank = RANK_1; rank <= RANK_8; ++rank) {
        for (file = FILE_A; file <= FILE_H; ++file) {
            sq = FR2SQ(file, rank);
            Sq64ToSq120[sq64] = sq;
            Sq120ToSq64[sq] = sq64;
            sq64++;
        }
    }
    /*
        The above loop populates the arrays, so Sq64ToSq120 is going
        to look like this:

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

        and Sq120ToSq64 is going to look like this:

            +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
            |  65 |  65 |  65 |  65 |  65 |  65 |  65 |  65 |  65 |  65 |
            +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
            |  65 |  65 |  65 |  65 |  65 |  65 |  65 |  65 |  65 |  65 |
            +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
            |  65 |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  65 |
            +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
            |  65 |  8  |  9  |  10 |  11 |  12 |  13 |  14 |  15 |  65 |
            +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
            |  65 |  16 |  17 |  18 |  19 |  20 |  21 |  22 |  23 |  65 |
            +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
            |  65 |  24 |  25 |  26 |  27 |  28 |  29 |  30 |  31 |  65 |
            +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
            |  65 |  32 |  33 |  34 |  35 |  36 |  37 |  38 |  39 |  65 |
            +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
            |  65 |  40 |  41 |  42 |  43 |  44 |  45 |  46 |  47 |  65 |
            +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
            |  65 |  48 |  49 |  50 |  51 |  52 |  53 |  54 |  55 |  65 |
            +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
            |  65 |  56 |  57 |  58 |  59 |  60 |  61 |  62 |  63 |  65 |
            +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
            |  65 |  65 |  65 |  65 |  65 |  65 |  65 |  65 |  65 |  65 |
            +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
            |  65 |  65 |  65 |  65 |  65 |  65 |  65 |  65 |  65 |  65 |
            +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+

    */

}

void allInit(void) {
    initLookUpArrays();
    initBitMasks();
    initHashKeys();
    initFilesRanksBrd();
    InitMvvLva();
}
