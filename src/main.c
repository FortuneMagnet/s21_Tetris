#include "s21_tetris.h"



int main(int argc, char* argv[]) {
    init_ncurses();
    GameInfo_t* t = createGame();
    t->state = START;

        /////// цикл игры
        while (t->state != EXIT){ // поменять на EXIT
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
                draw_service_field(t);
                initActions(t, getch());
                }
                if (t->state == GAME){
                    t = restartGame(t);
                }
            }
        }
        /////// цикл игры
    freeGame(t);
    endwin();
    return 0;
}


