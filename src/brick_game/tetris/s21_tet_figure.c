#include "../../s21_tetris.h"

void chooseNext(GameInfo_t* t){
    int fnum = (rand() + 1) % 7;
    if (fnum == O) chooseO(t);
    else if (fnum == I) chooseI(t);
    else if (fnum == L) chooseL(t);
    else if (fnum == J) chooseJ(t);
    else if (fnum == S) chooseS(t);
    else if (fnum == Z) chooseZ(t);
    else if (fnum == T) chooseT(t);
}

void chooseO(GameInfo_t* t){
    int a[4][4] = 
            {{0, 0, 0, 0},
            {0, 2, 2, 0},
            {0, 2, 2, 0},
            {0, 0, 0, 0}};
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            t->next[i][j] = a[i][j]; 
        }
    }
}

void chooseI(GameInfo_t* t){
    int a[4][4] = 
            {{0, 2, 0, 0,},
            {0, 2, 0, 0,},
            {0, 2, 0, 0,},
            {0, 2, 0, 0,}};
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            t->next[i][j] = a[i][j]; 
        }
    }
}

void chooseL(GameInfo_t* t){
    int a[4][4] = 
            {{0, 2, 0, 0},
            {0, 2, 0, 0},
            {0, 2, 2, 0},
            {0, 0, 0, 0}};
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            t->next[i][j] = a[i][j]; 
        }
    }
}

void chooseJ(GameInfo_t* t){
    int a[4][4] = 
            {{0, 0, 2, 0,},
            {0, 0, 2, 0,},
            {0, 2, 2, 0,},
            {0, 0, 0, 0,}};
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            t->next[i][j] = a[i][j]; 
        }
    }
}

void chooseS(GameInfo_t* t){
    int a[4][4] = 
            {{0, 0, 0, 0,},
            {0, 0, 2, 2,},
            {0, 2, 2, 0,},
            {0, 0, 0, 0,}};
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            t->next[i][j] = a[i][j]; 
        }
    }
}

void chooseZ(GameInfo_t* t){
    int a[4][4] = 
            {{0, 0, 0, 0,},
            {2, 2, 0, 0,},
            {0, 2, 2, 0,},
            {0, 0, 0, 0,}};
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            t->next[i][j] = a[i][j]; 
        }
    }
}

void chooseT(GameInfo_t* t){
    int a[4][4] = 
            {{0, 0, 0, 0,},
            {0, 2, 2, 2,},
            {0, 0, 2, 0,},
            {0, 0, 0, 0,}};
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            t->next[i][j] = a[i][j]; 
        }
    }
}
