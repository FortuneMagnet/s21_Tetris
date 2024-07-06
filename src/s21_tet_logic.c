#include "s21_tetris.h"

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
        t->next[i] = malloc(4 * sizeof(int));
    }
    chooseNext(t);
    return t;
}

GameInfo_t* createFigure(GameInfo_t* t){
    t->figure = malloc(4 * sizeof(int*));
    for (int i = 0; i < 4; i++){
        t->figure[i] = malloc(4 * sizeof(int));
    }
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            t->figure[i][j] = 0;
        }
    }
    dropNewFigure(t);
    return t;
}

int** createTempFigure(){
    int **array = (int **)malloc(4 * sizeof(int *));

    for (int i = 0; i < 4; i++) {
        array[i] = (int *)malloc(4 * sizeof(int));
    }
    
    return array;
}

void freeTempFugire(int **array) {
    for (int i = 0; i < 4; i++) {
        free(array[i]);
    }
    free(array);
}

void freeGame(GameInfo_t *t){
    if (t != NULL){
        if (t->field != NULL){
            for (int i = 0; i < cols; i++){
                if (t->field[i] != NULL)
                    free(t->field[i]);
            }
            free(t->field);
        }
        if (t->next){
            for (int i = 0; i < 4; i++){
                if (t->next[i] != NULL)
                    free(t->next[i]);
            }
            free(t->next);
        }
        if (t->figure != NULL){
            for (int i = 0; i < 4; i++){
                if (t->figure[i] != NULL)
                    free(t->figure[i]);
            }
            free(t->figure);
        }
        t->score = 0;
        t->high_score = 0;
        t->level = 0;
        t->speed = 0;
        t->pause = 0;
        t->x = 0;
        t->y = 0;
        t->action = 0;
        t->state = 0;
        t->ticks = 0;
        free(t);
    }
}

void drawfield(GameInfo_t* t){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (t->field[i][j] == 0){
                printw("%s", "..");
            } else if (t->field[i][j] == 1){
                printw("%s", "[]");
            } else if (t->field[i][j] == 2) { 
                printw("%s", "[]");
            }
        }
        printw("\n");
    }
    printw("%d", t->action);
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

void plantFigure(GameInfo_t* t){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (t->figure[i][j] == 2)
                t->field[i+t->y][j+t->x] = 1 ;
        }
    }
}


void initActions(GameInfo_t* t, int ch){
    if (ch == KEY_UP)
      t->action = Up;
    else if (ch == KEY_DOWN)
      t->action = Down;
    else if (ch == KEY_LEFT)
      t->action = Left;
    else if (ch == KEY_RIGHT)
      t->action = Right;
    else if (ch == ' ')
      t->action = Pause;
    else if (ch == 10 || ch == 13)
      t->action = Start;
    else if (ch == 'q' || ch == 'Q')
      t->action = Terminate;
    else if (ch == ERR)
        t->action = -1;
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

void rotateFigure(GameInfo_t* t){
    int **temp = createTempFigure();
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
        temp[i][j] = t->figure[i][j];
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            t->figure[j][4-1 -i] = temp[i][j];
        }
    }
    freeTempFugire(temp);
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

int countScore(int lines){
    int score = 0;
    if (lines == 1) {
        score = 100;
    }
    if (lines == 2) {
        score = 300;
    }
    if (lines == 3) {
        score = 700;
    }
    if (lines == 4) {
        score = 1500;
    }
    return score;
}

void dropLine(int i, GameInfo_t* t){
    if(i == 0){
        for(int j = 0; j < cols; j++)
            t->field[i][j] = 0;
    } else {
        for (int k = i; k > 0; k--){
            for (int j = 0; j < cols; j++){
                t->field[k][j] = t->field[k-1][j];
            }
        }
    }
}

int checkLine(int i, GameInfo_t* t){
    for(int j =0; j< cols; j++){
        if(t->field[i][j] == 0){
            return 0;// поменять выход из функции
        }
    }
    return 1;
}

int eraseLinesTet(GameInfo_t* t){
    int count = 0;
    int score = 0;
    for (int i = rows - 1; i >= 0; i--){
        while(checkLine(i, t)){
            dropLine(i, t);
            count++;
        }
    }
    score = countScore(count);
    return score;
}


GameInfo_t updateCurrentState(GameInfo_t* t){
    ////

    deleteFigure(t);
        if (t->ticks == 0){
            if (collisionTet(t))
                t->state = GAME_OVER;
            moveFigureDown(t);
            if (collisionTet(t)){
                moveFigureUp(t);
                plantFigure(t);
                t->score += eraseLinesTet(t);
                dropNewFigure(t);
                if (collisionTet(t))
                    t->state = GAME_OVER; /// state
            }
            t->ticks = 100;
        }
        ///// Обработка ввода игрока
        if (t->action == Left){
            moveFigureLeft(t);
            if (collisionTet(t))
                moveFigureRight(t);
        }
        if (t->action == Right){
            moveFigureRight(t);
            if (collisionTet(t))
                moveFigureLeft(t);
        }
        if (t->action == Up){
            rotateFigure(t);
            if (collisionTet(t)){
                for (int i = 0; i < 3; i++){
                    rotateFigure(t);
                }
            }
        }
        if (t->action == Down){
            while (1){
                moveFigureDown(t);
                if (collisionTet(t))
                break;
            }
            moveFigureUp(t);
        }
        if (t->action == Pause){
            t->state = PAUSE;
        }
        if (t->action == Terminate){
            t->state == EXIT;
        }
        /////

        t->ticks--;
        dropFigure(t);

}
