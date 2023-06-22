CFLAGS = -Wall -pedantic -std=c11 

all: tictactoe

tmp:	tictactoe.o
		gcc $(CFLAGS) tictactoe.o -o tictactoe

tmp.o: 	tictactoe.c
		gcc $(CFLAGS) -c tictactoe.c -o tictactoe.o

clean:
		rm -f *.o
