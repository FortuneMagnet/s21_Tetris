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

    int ticks;
    int state;

} GameInfo_t;

typedef enum{
    O, I, L, J, S, Z, T
} Tetramino_t;

typedef enum{
    START, PAUSE, GAME, GAME_OVER, EXIT
} GameState_t;




//// LOGIC FUNCTIONS
void fromNextToFigure(GameInfo_t *t);
void dropNewFigure(GameInfo_t* t);
void scoreChecker(GameInfo_t* t);
void dropFigure(GameInfo_t* t); //
void deleteFigure(GameInfo_t* t);
void plantFigure(GameInfo_t* t);
void moveFigureDown(GameInfo_t* t);
void moveFigureUp(GameInfo_t* t);
void moveFigureRight(GameInfo_t* t);
void moveFigureLeft(GameInfo_t* t);
void rotateFigure(GameInfo_t* t);
int collisionTet(GameInfo_t* t);
int countScore(int lines);
void dropLine(int i, GameInfo_t* t);
int checkLine(int i, GameInfo_t* t);
int eraseLinesTet(GameInfo_t* t);
void levelProcessing(GameInfo_t* t);
GameInfo_t updateCurrentState(GameInfo_t* t);

//// FUGIRE FUNCTIONS
void chooseNext(GameInfo_t* t); //
void chooseO(GameInfo_t* t);
void chooseI(GameInfo_t* t);
void chooseL(GameInfo_t* t);
void chooseJ(GameInfo_t* t);
void chooseS(GameInfo_t* t);
void chooseZ(GameInfo_t* t);
void chooseT(GameInfo_t* t);


//// INIT FUNCTIONS
GameInfo_t* createGame(); //
GameInfo_t* restartGame(GameInfo_t* t);
GameInfo_t* createField(GameInfo_t* t); //
GameInfo_t* createNext(GameInfo_t* t); //
GameInfo_t* createFigure(GameInfo_t* t); //
int** createTempFigure(); //
void freeTempFugire(int **array); 
void freeGame(GameInfo_t *t);
void scoreReader(GameInfo_t* t);//
void initActions(GameInfo_t* t, int ch);//


// FRONT PART
void draw_main(GameInfo_t* t);
void draw_next(GameInfo_t* t);
// void draw_field_score(int high_score, int score);
void draw_service_field(GameInfo_t* t);
void draw_start_field();
void draw_all(GameInfo_t* t);

#endif 