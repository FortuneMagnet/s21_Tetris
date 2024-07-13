#include "../../s21_tetris.h"

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


void scoreChecker(GameInfo_t* t){
    if (t->score > t->high_score){
        FILE *fp = fopen("hight_score.txt", "r+");
        if(fp)
        {
            fprintf(fp, "%d", t->score);
            fclose(fp);
        }
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

void plantFigure(GameInfo_t* t){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (t->figure[i][j] == 2)
                t->field[i+t->y][j+t->x] = 1 ;
        }
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
    int status = 1;
    for(int j =0; j< cols; j++){
        if(t->field[i][j] == 0){
            status = 0;
        }
    }
    return status;
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

void levelProcessing(GameInfo_t* t){
    //Добавь в игру механику уровней. Каждый раз, когда игрок набирает 600 очков, уровень увеличивается на 1. Повышается скорость, меняется тикрейт
    if ((t->score > 600 * t->level) && t->level < 10){
        t->level ++;
        t->speed = t->speed - 50;
    }
}

GameInfo_t updateCurrentState(GameInfo_t* t){
    deleteFigure(t);
        if (t->ticks == 0){
            moveFigureDown(t);
            if (collisionTet(t)){
                moveFigureUp(t);
                plantFigure(t);
                t->score += eraseLinesTet(t);
                levelProcessing(t);
                dropNewFigure(t);
                if (collisionTet(t))
                    t->state = GAME_OVER; /// state
            }
            
            t->ticks = 300 - (25 * t->level); // количество пропускаемых кадров
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
        /////
        t->ticks--;
        dropFigure(t);
}
