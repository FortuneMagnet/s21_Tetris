CC = gcc
CFLAGS= -Wall -Werror -Wextra -std=gnu11
FOLD_GAME = ./brick_game/
FOLD_LIB = ./brick_game/tetris/
FOLD_FRONT = ./gui/cli/
FOLD_OBJ = ./
FOLD_TEST = ./tests/

#============ FLAGS FOR OS ======================================================== 
UNAME:=$(shell uname -s)
ifeq ($(UNAME),Linux)
	LDFLAGS=-lcheck -lsubunit -lm -lrt -lpthread
	OPEN_CMD=xdg-open
endif
ifeq ($(UNAME),Darwin)
	LDFLAGS=-lcheck -lm
	OPEN_CMD=open
endif



build :
	$(CC) $(CFLAGS) $(FOLD_LIB)* $(FOLD_FRONT)*.c $(FOLD_GAME)*.c -lncurses -o tet.out

test: clean
	$(CC) $(CFLAGS) $(FOLD_LIB)* $(FOLD_TEST)* $(LDFLAGS) -o test

gcov_report: clean
	$(CC) $(CFLAGS) $(FOLD_LIB)* $(FOLD_TEST)*.c -o gcov_tests $(LDFLAGS) --coverage
	./gcov_tests
	lcov -c -d . -o gcov_tests.info
	genhtml -o report gcov_tests.info
	chmod 777 report/*
	rm *.gcda *.gcno
	$(OPEN_CMD) ./report/index.html


clean:
	rm -rf tet.out

rebuild: clear $(TAGRET)

