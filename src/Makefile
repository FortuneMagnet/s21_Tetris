CC = gcc
CFLAGS= -Wall -Werror -Wextra -std=gnu11
FOLD_GAME = ./brick_game/
FOLD_LIB = ./brick_game/tetris/
FOLD_FRONT = ./gui/cli/
FOLD_OBJ = ./
FOLD_TEST = ./tests/
PROJECT_NAME = s21_tetris

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



install :
	mkdir build
	cd build && $(CC) $(CFLAGS) ../$(FOLD_LIB)* ../$(FOLD_FRONT)*.c ../$(FOLD_GAME)*.c -lncurses -o tet.out

uninstall:
	rm -rf build

dvi: clean
	doxygen
	open ./doxygen/html/index.html

dist: clean
	mkdir $(PROJECT_NAME)
	cp -r brick_game $(PROJECT_NAME)
	cp -r gui $(PROJECT_NAME)
	cp Makefile $(PROJECT_NAME)
	cp Doxyfile $(PROJECT_NAME)
	tar -cvzf $(PROJECT_NAME).tgz $(PROJECT_NAME)
	rm -rf $(PROJECT_NAME)

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


clean: uninstall
	rm -rf tet.out gcov* *.tgz test ./report ./doxygen

rebuild: clean install

