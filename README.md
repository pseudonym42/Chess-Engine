# What is this?

This is a chess engine implementation based on a
[video course](https://www.youtube.com/playlist?list=PLZ1QII7yudbc-Ky058TEaOstZHVbT-2hg) produced by Bluefever Software.

The core functionality is written in C.

# What is this?

How to build and run:

    make && ./chess_exe

# Why did I take this course?

I wanted to learn C and understand better how chess game engines work. As I was going through this course I found some of the topics super challenging but they were extremely rewarding.

To understand at least some basis of how chess games are built use this website - [Chess Programming Wiki](https://www.chessprogramming.org/Main_Page).

# Screenshots

TBC

# Did I make any changes to the original code?

I tried to add comments to the code as much as I could to provide explanation to some difficult subjects. Apart from that I made minor changes to function and variable names, avoided some of the macros. If you follow the above course you might find the below notes useful. To introduce some naming convention I have kept `PascalCase` for array names but used `camelCase` for function names.

Macros I did NOT use:

* `SQ64` as a replacement to `Sq120ToSq64` array
* `SQ120` as a replacement to `Sq64ToSq120` array
* `POP` as a replacement to `popBit` function
* `CNT` as a replacement to `countBits` function

Changes to the function names:

* `allInit` instead of `AllInit`
* `popBit` instead of `PopBit`
* `countBits` instead of `CountBits`
* `initBitMasks` instead of `InitBitMasks`
* `generatePosKey` instead of `GeneratePosKey`
* `initLookUpArrays` instead of `InitSq120To64`
* `resetBoard` instead of `ResetBoard`
* `parseFEN` instead of `Parse_Fen`
* `printBoard` instead of `PrintBoard`
* `updateListsMaterial` instead of `UpdateListsMaterial`
* `initFilesRanksBrd` instead of `InitFilesRanksBrd`
* `checkBoard` instead of `CheckBoard`
* `squareAttacked` instead of `SqAttacked`
* `printSq` instead of `PrSq`
* `printMove` instead of `PrMove`
* `addQuietMove` instead of `AddQuietMove`
* `addCaptureMove` instead of `AddCaptureMove`
* `addEnPassantMove` instead of `AddEnPassantMove`
* `generateAllMoves` instead of `GenerateAllMoves`
* `sqOnBoard` instead of `SqOnBoard`
* `sideValid` instead of `SideValid`
* `fileRankValid` instead of `FileRankValid`
* `pieceValidEmpty` instead of `PieceValidEmpty`
* `pieceValid` instead of `PieceValid`


# Some common questions?

Q. Why certain functions/arrays are declared in multiple places e.g. in both the `defs.h` file and the `init.c` file?  
A: They are not, read about it [here](https://en.wikipedia.org/wiki/External_variable#Example_.28C_programming_language.29), or [here](https://stackoverflow.com/a/1433387)

Q: How many moves are calculated by AI per second?  
A: Around 500k

# Useful links

1. Images for pieces: https://pixabay.com/images/search/chess%20pieces/
