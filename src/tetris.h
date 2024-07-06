#ifndef C7_TETRIS_H
#define C7_TETRIS_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //Для sleep
#include <curses.h>
#include <ncurses.h>


#define rows 20
#define cols 10

typedef enum {
    Start,
    Pause,
    Terminate,
    Left,
    Right,
    Up,
    Down,
    Action
} UserAction_t;

typedef struct {
    int **field;
    int **next;
    int score;
    int high_score;
    int level;
    int speed;
    int pause;
    int **figure;
    int x;
    int y;

    int action;

    int stop_game;
} GameInfo_t;

typedef enum{
    O, I, L, J, S, Z, T
} Tetramino_t;



// void userInput(UserAction_t action, bool hold);
void dropNewFigure(GameInfo_t* t);
void fromNextToFigure(GameInfo_t *t);


/// LOGIC FUNCTIONS


GameInfo_t* createGame();
GameInfo_t* createField(GameInfo_t* t);
GameInfo_t* createNext(GameInfo_t* t);
GameInfo_t* createFigure(GameInfo_t* t);
void freeGame(GameInfo_t *t);
void drawfield(GameInfo_t* t);
int checkFigureOnField(GameInfo_t* t);
void chooseNext(GameInfo_t* t);
void chooseO(GameInfo_t* t);
void chooseI(GameInfo_t* t);
void chooseL(GameInfo_t* t);
void chooseJ(GameInfo_t* t);
void chooseS(GameInfo_t* t);
void chooseZ(GameInfo_t* t);
void chooseT(GameInfo_t* t);
void dropFigure(GameInfo_t* t);
void initActions(GameInfo_t* t, int ch);

GameInfo_t updateCurrentState();


#endif 