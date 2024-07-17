#include "s21_tetris.h"

GameInfo_t* createGame(){
    GameInfo_t* t = malloc(sizeof(GameInfo_t));
    scoreReader(t);
    t = createField(t);
    t = createNext(t);
    t = createFigure(t);
    t->level = 1;
    return t;
}

GameInfo_t* restartGame(GameInfo_t* t){
    freeGame(t);
    GameInfo_t* newt = createGame();
    return newt;
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

void scoreReader(GameInfo_t* t){
    FILE *fp = fopen("hight_score.txt", "r+");
    char buffer[256];
    if(fp)
    {
        fgets(buffer, sizeof(buffer), fp);
        t->high_score = atoi(buffer);
        fclose(fp);
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
    else if (ch == ' '){
        t->action = Pause;
        if (t->state == GAME)
             t->state = PAUSE;
        else if (t->state == PAUSE)
             t->state = GAME;
    }
    else if (ch == 10 || ch == 13)
      t->state = GAME;
    else if (ch == 'q' || ch == 'Q')
      t->state = EXIT;
    else if (ch == ERR)
        t->action = -1;
}
