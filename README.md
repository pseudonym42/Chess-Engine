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


# Did I make any changes to the original code?

I tried to add comments to the code as much as I could to provide explanation to some difficult subjects. Apart from that I made minor changes to function and variable names, avoided some of the macros. If you follow the above course you might find the below notes useful. To introduce some naming convention I have kept `PascalCase` for array names but used `camelCase` for function names.

Macros I did NOT use:

* `CNT` as a replacement to `countBits` function
* `POP` as a replacement to `popBit` function
* `SQ120` as a replacement to `Sq64ToSq120` array
* `SQ64` as a replacement to `Sq120ToSq64` array

Changes to the function names:

* `addBlackPawnCapMove` instead of `AddBlackPawnCapMove`
* `addBlackPawnMove` instead of `AddBlackPawnMove`
* `addCaptureMove` instead of `AddCaptureMove`
* `addEnPassantMove` instead of `AddEnPassantMove`
* `allInit` instead of `AllInit`
* `addQuietMove` instead of `AddQuietMove`
* `addWhitePawnCapMove` instead of `AddWhitePawnCapMove`
* `addWhitePawnMove` instead of `AddWhitePawnMove`
* `checkBoard` instead of `CheckBoard`
* `countBits` instead of `CountBits`
* `fileRankValid` instead of `FileRankValid`
* `generateAllMoves` instead of `GenerateAllMoves`
* `generatePosKey` instead of `GeneratePosKey`
* `initBitMasks` instead of `InitBitMasks`
* `initFilesRanksBrd` instead of `InitFilesRanksBrd`
* `initLookUpArrays` instead of `InitSq120To64`
* `parseFEN` instead of `ParseFen`
* `pieceValid` instead of `PieceValid`
* `pieceValidEmpty` instead of `PieceValidEmpty`
* `popBit` instead of `PopBit`
* `printBoard` instead of `PrintBoard`
* `printBitBoard` instead of `PrintBitBoard`
* `printMove` instead of `PrMove`
* `printMoveList` instead of `PrintMoveList`
* `printSq` instead of `PrSq`
* `updateListsMaterial` instead of `UpdateListsMaterial`
* `resetBoard` instead of `ResetBoard`
* `sideValid` instead of `SideValid`
* `sqOnBoard` instead of `SqOnBoard`
* `squareAttacked` instead of `SqAttacked`


# Some common questions?

Q. Why certain functions/arrays are declared in multiple places e.g. in both the `defs.h` file and the `init.c` file?  
A: They are not, read about it [here](https://en.wikipedia.org/wiki/External_variable#Example_.28C_programming_language.29), or [here](https://stackoverflow.com/a/1433387)

Q: How many moves are calculated by AI per second?  
A: Around 500k

# How to use the tool?

The tool is written to conform with the UCI and Winboard protocols. It can also be used to play against PC via console.

Popular commands:

1. Quit: `quit`

2. Set start position: `position startpos`

3. Set certain FEN: `position fen <FEN>`

4. Set an FEN and add moves: `position fen <FEN> moves <MOVES>`

5. Start working in uci mode: `uci`

6. Start working in winboard mode: `xboard`

7. Play game via console mode: `vice`