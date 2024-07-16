
 #include <check.h>
 #include <stdlib.h>
 #include "s21_tet_test.h"

START_TEST(test_createGame) {
  GameInfo_t* t = createGame();
  ck_assert_ptr_nonnull(t); // 
  freeGame(t);
}
END_TEST

START_TEST(test_createField) {
    GameInfo_t game;
    createField(&game);
    ck_assert_ptr_nonnull(game.field);
    for (int i = 0; i < rows; i++) {
        ck_assert_ptr_nonnull(game.field[i]);
        for (int j = 0; j < cols; j++) {
            ck_assert_int_eq(game.field[i][j], 0);
        }
    }
    freeGame(&game);
} END_TEST

START_TEST(test_createNext) {
    GameInfo_t game;
    createNext(&game);
    ck_assert_ptr_nonnull(game.next);
    for (int i = 0; i < 4; i++) {
        ck_assert_ptr_nonnull(game.next[i]);
    }
    freeGame(&game);
} END_TEST


 Suite *tetris_suite(void)
 {
     Suite *s;
     TCase *tc_core;

     s = suite_create("Tetris");

     /* Core test case */
     tc_core = tcase_create("Core");

        tcase_add_test(tc_core, test_createGame);
        tcase_add_test(tc_core, test_createField);
        tcase_add_test(tc_core, test_createNext);
    //     tcase_add_test(tc_core, test_createFigure);
    //     tcase_add_test(tc_core, test_freeGame);
    //  tcase_add_test(tc_core, test_chooseNext);
    //  tcase_add_test(tc_core, test_chooseO);
    //  tcase_add_test(tc_core, test_dropFigure);
    //  tcase_add_test(tc_core, test_initActions);
    //  tcase_add_test(tc_core, test_scoreReader);
    //  tcase_add_test(tc_core, test_scoreChecker);
    //  tcase_add_test(tc_core, test_createTempFigure);
    //  tcase_add_test(tc_core, test_freeTempFugire);




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