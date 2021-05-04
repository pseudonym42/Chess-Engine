all:
	gcc vice.c init.c bitboards.c hashkeys.c data.c board.c attack.c io.c movegen.c -o chess_exe
