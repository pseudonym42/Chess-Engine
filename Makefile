all:
	# gcc -m32 vice.c init.c bitboards.c hashkeys.c -o vice-exe
	gcc vice.c init.c bitboards.c hashkeys.c data.c board.c -o vice-exe
