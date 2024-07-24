
 #include <check.h>
 #include <stdlib.h>
 #include "s21_tet_test.h"

START_TEST(test_createGame) {
  GameInfo_t* t = createGame();
  ck_assert_ptr_nonnull(&t); 
  freeGame(t);
}
END_TEST

START_TEST(test_restartGame) {
  GameInfo_t* t = createGame();
  t = restartGame(t);
  ck_assert_ptr_nonnull(&t); 
  freeGame(t);
}
END_TEST

START_TEST(test_createField) {
    GameInfo_t* t = createGame();
    ck_assert_ptr_nonnull(t->field);
    for (int i = 0; i < rows; i++) {
       ck_assert_ptr_nonnull(t->field[i]);
    }
    freeGame(t);
} END_TEST

START_TEST(test_createNext) {
    GameInfo_t* t = createGame();
    ck_assert_ptr_nonnull(t->next);
    for (int i = 0; i < 4; i++) {
        ck_assert_ptr_nonnull(t->next[i]);
    }
    freeGame(t);
} END_TEST

START_TEST(test_createFigure) {
    GameInfo_t* t = createGame();
    ck_assert_ptr_nonnull(t->figure);
    for (int i = 0; i < 4; i++) {
        ck_assert_ptr_nonnull(t->figure[i]);
    }
    freeGame(t);
} END_TEST


START_TEST(test_chooseNext) {
    GameInfo_t* t = createGame();
    chooseNext(t);
    int sum = 0;
    for (int i = 0; i < 4;i++){
        for (int j = 0; j < 4; j++){
            if (t->next[i][j] == 2)
                sum ++;
        }
    }
    ck_assert_int_eq(sum, 4);
    freeGame(t);
} END_TEST


START_TEST(test_chooseO) {
    GameInfo_t* t = createGame();
    chooseO(t);
    int a[4][4] = 
            {{0, 0, 0, 0},
            {0, 2, 2, 0},
            {0, 2, 2, 0},
            {0, 0, 0, 0}};
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            ck_assert_int_eq(t->next[i][j], a[i][j]);
        }
    }
    freeGame(t);
} END_TEST

START_TEST(test_chooseI) {
    GameInfo_t* t = createGame();
    chooseI(t);
    int a[4][4] = 
            {{0, 2, 0, 0,},
            {0, 2, 0, 0,},
            {0, 2, 0, 0,},
            {0, 2, 0, 0,}};
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            ck_assert_int_eq(t->next[i][j], a[i][j]);
        }
    }
    freeGame(t);
} END_TEST

START_TEST(test_chooseL) {
    GameInfo_t* t = createGame();
    chooseL(t);
    int a[4][4] = 
            {{0, 2, 0, 0},
            {0, 2, 0, 0},
            {0, 2, 2, 0},
            {0, 0, 0, 0}};
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            ck_assert_int_eq(t->next[i][j], a[i][j]);
        }
    }
    freeGame(t);
} END_TEST

START_TEST(test_chooseJ) {
    GameInfo_t* t = createGame();
    chooseJ(t);
    int a[4][4] = 
            {{0, 0, 2, 0,},
            {0, 0, 2, 0,},
            {0, 2, 2, 0,},
            {0, 0, 0, 0,}};
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            ck_assert_int_eq(t->next[i][j], a[i][j]);
        }
    }
    freeGame(t);
} END_TEST

START_TEST(test_chooseS) {
    GameInfo_t* t = createGame();
    chooseS(t);
    int a[4][4] = 
            {{0, 0, 0, 0,},
            {0, 0, 2, 2,},
            {0, 2, 2, 0,},
            {0, 0, 0, 0,}};
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            ck_assert_int_eq(t->next[i][j], a[i][j]);
        }
    }
    freeGame(t);
} END_TEST

START_TEST(test_chooseZ) {
    GameInfo_t* t = createGame();
    chooseZ(t);
    int a[4][4] = 
            {{0, 0, 0, 0,},
            {2, 2, 0, 0,},
            {0, 2, 2, 0,},
            {0, 0, 0, 0,}};
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            ck_assert_int_eq(t->next[i][j], a[i][j]);
        }
    }
    freeGame(t);
} END_TEST

START_TEST(test_chooseT) {
    GameInfo_t* t = createGame();
    chooseT(t);
    int a[4][4] = 
            {{0, 0, 0, 0,},
            {0, 2, 2, 2,},
            {0, 0, 2, 0,},
            {0, 0, 0, 0,}};
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            ck_assert_int_eq(t->next[i][j], a[i][j]);
        }
    }
    freeGame(t);
} END_TEST

START_TEST(test_dropFigure) {
    GameInfo_t* t = createGame();
    dropFigure(t);
    int sum = 0;
    for (int i = 0; i < 4;i++){
        for (int j = 0; j < 4; j++){
            if (t->field[t->y + i][t->x + j] == 2)
                sum ++;
        }
    }
    ck_assert_int_eq(sum, 4);
    freeGame(t);
} END_TEST

START_TEST(test_initActions) {
    GameInfo_t* t = createGame();
    initActions(t, KEY_UP);
    ck_assert_int_eq(t->action, Up);
    initActions(t, KEY_DOWN);
    ck_assert_int_eq(t->action, Down);
    initActions(t, KEY_LEFT);
    ck_assert_int_eq(t->action, Left);
    initActions(t, KEY_RIGHT);
    ck_assert_int_eq(t->action, Right);
    initActions(t, ' ');
    ck_assert_int_eq(t->action, Pause);
    initActions(t, 10);
    ck_assert_int_eq(t->state, GAME);
    initActions(t, 'Q');
    ck_assert_int_eq(t->state, EXIT);
    freeGame(t);
} END_TEST

START_TEST(test_scoreReader) {
    GameInfo_t* t = createGame();
    scoreReader(t);
    int flag = 0;
    if (t->high_score >= 0){
        flag = 1;
    }
    ck_assert_int_eq(flag, 1);
    freeGame(t);
} END_TEST



START_TEST(test_createTempFigure) {
    int **temp = createTempFigure();
    
    ck_assert_ptr_nonnull(temp);
    for (int i = 0; i < 4; i++) {
        ck_assert_ptr_nonnull(temp[i]);
    }
    freeTempFugire(temp);
} END_TEST

START_TEST(test_fromNextToFigure) {
    GameInfo_t* t = createGame();
    chooseNext(t);
    fromNextToFigure(t);
    for (int i = 0; i < 4;i++){
        for (int j = 0; j < 4; j++){
            ck_assert_int_eq(t->next[i][j], t->figure[i][j]);
        }
    }
    freeGame(t);
} END_TEST

START_TEST(test_dropNewFigure) {
    GameInfo_t* t = createGame();
    int sum = 0;
    chooseNext(t);
    dropNewFigure(t);
    ck_assert_int_eq(t->x, 4);
    ck_assert_int_eq(t->y, 0);
    for (int i = 0; i < 4;i++){
        for (int j = 0; j < 4; j++){
            if (t->figure[i][j] == 2)
                sum ++;
        }
    }
    ck_assert_int_eq(sum, 4);
    freeGame(t);
} END_TEST

START_TEST(test_deleteFigure) {
    GameInfo_t* t = createGame();
    dropFigure(t);
    deleteFigure(t);
    int sum = 0;
    for (int i = 0; i < 4;i++){
        for (int j = 0; j < 4; j++){
            if (t->field[t->y + i][t->x + j] == 2)
                sum ++;
        }
    }
    ck_assert_int_eq(sum, 0);
    freeGame(t);
} END_TEST

START_TEST(test_plantFigure) {
    GameInfo_t* t = createGame();
    dropFigure(t);
    plantFigure(t);
    int sum = 0;
    for (int i = 0; i < 4;i++){
        for (int j = 0; j < 4; j++){
            if (t->field[t->y + i][t->x + j] == 1)
                sum ++;
        }
    }
    ck_assert_int_eq(sum, 4);
    freeGame(t);
} END_TEST

START_TEST(test_moveFigureDown) {
    GameInfo_t* t = createGame();
    dropNewFigure(t);
    moveFigureDown(t);
    ck_assert_int_eq(t->y, 1);
    freeGame(t);
} END_TEST

START_TEST(test_moveFigureUp) {
    GameInfo_t* t = createGame();
    dropNewFigure(t);
    moveFigureDown(t);
    moveFigureDown(t);
    moveFigureUp(t);
    ck_assert_int_eq(t->y, 1);
    freeGame(t);
} END_TEST

START_TEST(test_moveFigureRight) {
    GameInfo_t* t = createGame();
    dropNewFigure(t);
    moveFigureRight(t);
    ck_assert_int_eq(t->x, 5);
    freeGame(t);
} END_TEST

START_TEST(test_moveFigureLeft) {
    GameInfo_t* t = createGame();
    dropNewFigure(t);
    moveFigureLeft(t);
    ck_assert_int_eq(t->x, 3);
    freeGame(t);
} END_TEST

START_TEST(test_rotateFigure) {
    GameInfo_t* t = createGame();
    chooseT(t);
    fromNextToFigure(t);
    rotateFigure(t);
    int a[4][4] = 
            {{0, 0, 0, 0,},
            {0, 0, 2, 0,},
            {0, 2, 2, 0,},
            {0, 0, 2, 0,}};
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            ck_assert_int_eq(t->figure[i][j], a[i][j]);
        }
    }
    freeGame(t);
} END_TEST

START_TEST(test_collisionTet) {
    GameInfo_t* t = createGame();
    chooseT(t);
    fromNextToFigure(t);
    t->x = 5;
    t->y = 5;
    ck_assert_int_eq(collisionTet(t), 0);
    t->x = 20;
    t->y = 40;
    ck_assert_int_eq(collisionTet(t), 1);
    freeGame(t);
} END_TEST


START_TEST(test_countScore) {
    int line = 1;
    ck_assert_int_eq(countScore(line), 100);
    line = 2;
    ck_assert_int_eq(countScore(line), 300);
    line = 3;
    ck_assert_int_eq(countScore(line), 700);
    line = 4;
    ck_assert_int_eq(countScore(line), 1500);
} END_TEST

START_TEST(test_dropLine) {
    GameInfo_t* t = createGame();
    for (int j = 0; j < cols; j++){
        t->field[19][j] = 1;   
        }
    dropLine(19,t);
    for (int j = 0; j < cols; j++){
        ck_assert_int_eq(t->field[19][j], 0);   
        }
    for (int j = 0; j < cols; j++){
        t->field[0][j] = 1;   
        }
    dropLine(0,t);
    for (int j = 0; j < cols; j++){
        ck_assert_int_eq(t->field[0][j], 0);   
        }
    freeGame(t);
} END_TEST

START_TEST(test_checkLine) {
    GameInfo_t* t = createGame();
    ck_assert_int_eq(checkLine(19,t), 0);
    freeGame(t);
} END_TEST

START_TEST(test_eraseLinesTet) {
    GameInfo_t* t = createGame();
    for (int j = 0; j < cols; j++){
        t->field[19][j] = 1;
        t->field[18][j] = 1;    
        }
    ck_assert_int_eq(eraseLinesTet(t), 300);
    freeGame(t);
} END_TEST

START_TEST(test_levelProcessing) {
    GameInfo_t* t = createGame();
    t->level = 1;
    t->speed = 300;
    t->score = 900;
    levelProcessing(t);
    ck_assert_int_eq(t->speed, 250);
    ck_assert_int_eq(t->level, 2);
} END_TEST

 Suite *tetris_suite(void)
 {
     Suite *s;
     TCase *tc_core;

     s = suite_create("Tetris");

     /* Core test case */
     tc_core = tcase_create("Core");

        tcase_add_test(tc_core, test_createGame);
        tcase_add_test(tc_core, test_restartGame);
        tcase_add_test(tc_core, test_createField);
        tcase_add_test(tc_core, test_createNext);
        tcase_add_test(tc_core, test_createFigure);
        tcase_add_test(tc_core, test_chooseNext);
     
     tcase_add_test(tc_core, test_initActions);
     tcase_add_test(tc_core, test_scoreReader);;
     tcase_add_test(tc_core, test_createTempFigure);

     tcase_add_test(tc_core, test_chooseNext);
     tcase_add_test(tc_core, test_chooseO); 
     tcase_add_test(tc_core, test_chooseI);
    tcase_add_test(tc_core, test_chooseL);
    tcase_add_test(tc_core, test_chooseJ);
    tcase_add_test(tc_core, test_chooseS);
    tcase_add_test(tc_core, test_chooseZ);
    tcase_add_test(tc_core, test_chooseT);



     tcase_add_test(tc_core, test_dropFigure);
     tcase_add_test(tc_core, test_fromNextToFigure);
     tcase_add_test(tc_core, test_dropNewFigure);
     tcase_add_test(tc_core, test_deleteFigure);
     tcase_add_test(tc_core, test_plantFigure);
     tcase_add_test(tc_core, test_moveFigureDown);
     tcase_add_test(tc_core, test_moveFigureUp);
     tcase_add_test(tc_core, test_moveFigureRight);
     tcase_add_test(tc_core, test_moveFigureLeft);
     tcase_add_test(tc_core, test_rotateFigure);
     tcase_add_test(tc_core, test_collisionTet);
     tcase_add_test(tc_core, test_countScore);
     tcase_add_test(tc_core, test_dropLine);
     tcase_add_test(tc_core, test_checkLine);
     tcase_add_test(tc_core, test_eraseLinesTet);
     tcase_add_test(tc_core, test_levelProcessing);
     // tcase_add_test(tc_core, test_);
     // tcase_add_test(tc_core, test_);
     // tcase_add_test(tc_core, test_);


     suite_add_tcase(s, tc_core);

     return s;
 }


 int main(void)
 {
     int number_failed;
     Suite *s;
     SRunner *sr;

     s = tetris_suite();
     sr = srunner_create(s);

     srunner_run_all(sr, CK_NORMAL);
     number_failed = srunner_ntests_failed(sr);
     srunner_free(sr);

     return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
 }