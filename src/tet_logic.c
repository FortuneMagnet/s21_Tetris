#include "tetris.h"

void fromNextToFigure(GameInfo_t *t){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            t->figure[i][j] = t->next[i][j];
        }
    }
}

void dropNewFigure(GameInfo_t* t){
    t->x = 4;
    t->y = 0;
    fromNextToFigure(t);
    chooseNext(t); 
}

GameInfo_t* createGame(){
    GameInfo_t* t = malloc(sizeof(GameInfo_t));

    t = createField(t);
    t = createNext(t);
    t = createFigure(t);
    return t;
}

GameInfo_t* createField(GameInfo_t* t){
    t->field = malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++){
        t->field[i] = malloc(cols * sizeof(int));
    }

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            t->field[i][j] = 0;
        }
    }
    return t;
}

GameInfo_t* createNext(GameInfo_t* t){
    t->next = malloc(4 * sizeof(int*));
    for (int i = 0; i < 4; i++){
        t->next[i] = malloc(cols * sizeof(int));
    }
    chooseNext(t);
    return t;
}

GameInfo_t* createFigure(GameInfo_t* t){
    t->figure = malloc(4 * sizeof(int*));
    for (int i = 0; i < 4; i++){
        t->figure[i] = malloc(cols * sizeof(int));
    }
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            t->figure[i][j] = 0;
        }
    }
    dropNewFigure(t);
    return t;
}

void freeGame(GameInfo_t *t){
    if (t){
        if (t->field){
            for (int i = 0; i < cols; i++){
                if (t->field[i])
                    free(t->field[i]);
            }
            free(t->field);
        }
        if (t->figure){
            for (int i = 0; i < 4; i++){
                if (t->figure[i])
                    free(t->figure[i]);
            }
            free(t->figure);
        }
        free(t);
    }
}

void drawfield(GameInfo_t* t){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (t->field[i][j] == 0){
                mvaddch(i, j, 0);
            } else if (t->field[i][j] == 1){
                mvaddch(i, j, 1);
            } else if (t->field[i][j] == 2) { 
                mvaddch(i, j, 2);
            }
        }
        // printf("\n");
    }
}

int checkFigureOnField(GameInfo_t* t){ // возвращает 1 если фигур нет
    int status = 1;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (t->field[i][j] == 2)
                status = 0;
        }
    }
    return status;
}



void dropFigure(GameInfo_t* t){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (t->figure[i][j] == 2)
                t->field[i+t->y][j+t->x] = t->figure[i][j];
        }
    }
}

void deleteFigure(GameInfo_t* t){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
                if (t->figure[i][j] == 2)
                    t->field[i+t->y][j+t->x] = 0;
        }
    }
}

void initActions(GameInfo_t* t, int ch){
    if (ch == Left){
        t->action = Left;
    } else if (ch == Right){
        t->action = Right;
    }
}

void moveFigureDown(GameInfo_t* t){
    t->y++;
}

void moveFigureUp(GameInfo_t* t){
    t->y--;
}

void moveFigureRight(GameInfo_t* t){
    t->x++;
}

void moveFigureLeft(GameInfo_t* t){
    t->x--;
}

// 0 = false не выполнится
// 1 = true
// проверка на то что произошло столкновение
int collisionTet(GameInfo_t* t){ 
    int status = 0; 
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (t->figure[i][j] != 0){
                int fy = t->y + i;
                int fx = t->x + j;
                if (fx < 0 || fx >= cols || fy < 0 || fy >= rows){
                    status++;
                } else if (t->field[fy][fx] != 0)
                    status ++;
            }
        }
    }
    if (status > 0) status = 1;
    // printf("status = %d", status);
    return status;
}

void plantFigure(GameInfo_t* t){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (t->figure[i][j] == 2)
                t->field[i+t->y][j+t->x] = 1 ;
        }
    }
}

int countLines(GameInfo_t* t){
    int lines = 0;
    int lineY = 20;
    int stop = 0;
        for (int i = 0; i < cols; i++){
            if (t->field[lineY][i] == 0){
                stop = 1;
                break;
            }
            if (stop != 1){
            lineY--;
            lines++;

        }
    }
    return lines;
}

int countScore(int lines){
    int score = 0;
    if (lines == 1) score = 100;
    if (lines == 2) score = 300;
    if (lines == 3) score = 700;
    if (lines == 4) score = 1500;
    else score = 1;
    return score;
}

void shiftBlocksDown(GameInfo_t* t){
    for(int i = rows; i > 1; i--){
        for (int j = 0; j < cols; j++)
        t->field[i][j] = t->field[i-1][j];
    }
}

int opsLines(GameInfo_t* t){
    int score = 0;
    int lines = 0;
    lines = countLines(t);
    score = countScore(lines);
    for (int i = 0; i < lines; i++)
        shiftBlocksDown(t);
    return score;
}

// int canMoveFigure(GameInfo_t* t){


// }

GameInfo_t updateCurrentState(GameInfo_t* t){
    ////
    deleteFigure(t);
    if (collisionTet(t))
        t->stop_game = 1;
    moveFigureDown(t);
    if (collisionTet(t)){
        moveFigureUp(t);
        plantFigure(t);
        // t->score += opsLines(t);
        dropNewFigure(t);
        if (collisionTet(t))
            t->stop_game = 1;
    } 
    t->action= Right;
    ///// Обработка ввода игрока
    if (t->action == Left){
        moveFigureLeft(t);
        if (collisionTet(t))
            moveFigureRight(t);
    } else if (t->action == Right){
        moveFigureRight(t);
        if (collisionTet(t))
            moveFigureLeft(t);
    }
    /////

    dropFigure(t);

}
