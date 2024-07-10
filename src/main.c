#include "s21_tetris.h"



int main(int argc, char* argv[]) {
    init_ncurses();
    GameInfo_t* t = createGame();
    t->state = START;
        while (t->state != EXIT){
            initActions(t, getch());
            if (t->state == START){
                draw_start_field();
            }
            if (t->state == PAUSE){
                draw_service_field(t);
            }
            if (t->state == GAME){
                updateCurrentState(t);
                // drawfield(t);
                draw_all(t);
                usleep(1000);
            }
            if (t->state == GAME_OVER){
                while (t->state == GAME_OVER){
                scoreChecker(t);
                draw_service_field(t);
                initActions(t, getch());
                }
                if (t->state == GAME){
                    t = restartGame(t);
                }
            }
        }
    freeGame(t);
    endwin();
    return 0;
}


