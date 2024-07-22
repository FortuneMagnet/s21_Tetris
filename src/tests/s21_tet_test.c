
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
  restartGame(t);
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
    dropNewFigure(t);
    for (int i = 0; i < 4;i++){
        for (int j = 0; j < 4; j++){
            if (t->field[t->y + i][t->x + j] == 2)
                sum ++;
        }
    }
    ck_assert_int_eq(sum, 4);
    freeGame(t);
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
     // tcase_add_test(tc_core, test_);
     // tcase_add_test(tc_core, test_);
     // tcase_add_test(tc_core, test_);
     // tcase_add_test(tc_core, test_);
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