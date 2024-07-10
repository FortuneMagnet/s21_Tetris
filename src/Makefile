TAGRET = s21_TetGame
CC = gcc

FOLD_SRC = ./
FOLD_BACK = ./brick_game/tetris/
FOLD_FRONT = ./gui/cli/
FOLD_OBJ = ./


$(TAGRET) :
	$(CC) $(FOLD_SRC)*.c $(FOLD_BACK)*.c $(FOLD_FRONT)*.c $(FOLD_SRC)*.h -lncurses -o tet.out

clear:
	rm -rf tet.out

rebuild: clear $(TAGRET)
