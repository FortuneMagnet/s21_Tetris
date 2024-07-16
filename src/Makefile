CC = gcc
CFLAGS= -Wall -Werror -Wextra -std=c11
FOLD_SRC = ./
FOLD_BACK = ./brick_game/tetris/
FOLD_FRONT = ./gui/cli/
FOLD_OBJ = ./
FOLD_TEST = ./tests/


build :
	$(CC) $(CFLAGS) $(FOLD_BACK)*.c $(FOLD_FRONT)*.c $(FOLD_SRC)*.h -lncurses -o tet.out

test: clean
	$(CC) $(CFLAGS) $(FOLD_BACK)*.c $(FOLD_SRC)*.h $(FOLD_TEST)*.c $(FOLD_TEST)*.h -lncurses -o test

clean:
	rm -rf tet.out

rebuild: clear $(TAGRET)

