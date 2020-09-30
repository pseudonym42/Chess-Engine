# What is this?

This is a chess engine implementation based on a
[video course](https://www.youtube.com/playlist?list=PLZ1QII7yudbc-Ky058TEaOstZHVbT-2hg) produced by Bluefever Software.

The core functionality is written in C.

# Why did I take this course?

I wanted to learn C and understand better how chess games are
developed. As I was working on this course I found some of the topics super challenging but they were extremely rewarding.

To understand at least some basis of how chess games are built one would have to spend a lot of time on this website - [Chess Programming Wiki](https://www.chessprogramming.org/Main_Page).

# Screenshots

TBC

# Did I make any changes to the original code?

I just tried adding comments to the code as much as I could to provide explanation to some difficult subjects. Apart from that I just made very minor changes to function and variable names, avoided some of the macros. if you follow the above course you might find the below notes useful.

Macros I did not use:

* `SQ64` as a replacement to `Sq120ToSq64` array
* `POP` as a replacement to `popBit` array
* `CNT` as a replacement to `countBits` array

Changes to the function names:

* `allInit` instead of `AllInit`
* `popBit` instead of `PopBit`
* `countBits` instead of `CountBits`
* `initBitMasks` instead of `InitBitMasks`
* `generatePosKey` instead of `GeneratePosKey`
* `resetBoard` instead of `ResetBoard`
* `parseFEN` instead of `Parse_Fen`
* `printBoard` instead of `PrintBoard`

# Some common questions?

Q. Why certain functions/arrays are declared in multiple places e.g. in both the `defs.h` file and the `init.c` file?  
A: They are not, read about it [here](https://en.wikipedia.org/wiki/External_variable#Example_.28C_programming_language.29)  

Q: Why..?  
A: ...

# Useful links

1. Images for pieces: https://pixabay.com/images/search/chess%20pieces/
