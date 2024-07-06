TAGRET = s21_TetGame
CC = gcc

FOLD_SRC = ./
FOLD_OBJ = ./


$(TAGRET) :
	$(CC) $(FOLD_SRC)*.c $(FOLD_SRC)*.h -lncurses -o tet.out

clear:
	rm -rf tet.out

rebuild: clear $(TAGRET)
