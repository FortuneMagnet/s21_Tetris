#include "./tetris.h"

void chooseNext(GameInfo_t* t){
    int fnum = rand() % 7;
    if (fnum == O) chooseO(t);
    if (fnum == I) chooseI(t);
    if (fnum == L) chooseL(t);
    if (fnum == J) chooseJ(t);
    if (fnum == S) chooseS(t);
    if (fnum == Z) chooseZ(t);
    if (fnum == T) chooseT(t);
}

void chooseO(GameInfo_t* t){
    int a[4][4] = 
            {{0, 0, 0, 0},
            {0, 0, 0, 0},
            {2, 2, 0, 0},
            {2, 2, 0, 0}};
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            t->next[i][j] = a[i][j]; 
        }
    }
}

void chooseI(GameInfo_t* t){
    int a[4][4] = 
            {{2, 0, 0, 0,},
            {2, 0, 0, 0,},
            {2, 0, 0, 0,},
            {2, 0, 0, 0,}};
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            t->next[i][j] = a[i][j]; 
        }
    }
}

void chooseL(GameInfo_t* t){
    int a[4][4] = 
            {{0, 0, 0, 0},
            {2, 0, 0, 0},
            {2, 0, 0, 0},
            {2, 2, 0, 0}};
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            t->next[i][j] = a[i][j]; 
        }
    }
}

void chooseJ(GameInfo_t* t){
    int a[4][4] = 
            {{0, 0, 0, 0,},
            {0, 2, 0, 0,},
            {0, 2, 0, 0,},
            {2, 2, 0, 0,}};
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            t->next[i][j] = a[i][j]; 
        }
    }
}

void chooseS(GameInfo_t* t){
    int a[4][4] = 
            {{0, 0, 0, 0,},
            {0, 0, 0, 0,},
            {0, 2, 2, 0,},
            {2, 2, 0, 0,}};
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            t->next[i][j] = a[i][j]; 
        }
    }
}

void chooseZ(GameInfo_t* t){
    int a[4][4] = 
            {{0, 0, 0, 0,},
            {0, 0, 0, 0,},
            {2, 2, 0, 0,},
            {0, 2, 2, 0,}};
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            t->next[i][j] = a[i][j]; 
        }
    }
}

void chooseT(GameInfo_t* t){
    int a[4][4] = 
            {{0, 0, 0, 0,},
            {0, 0, 0, 0,},
            {2, 2, 2, 0,},
            {0, 2, 0, 0,}};
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            t->next[i][j] = a[i][j]; 
        }
    }
}
