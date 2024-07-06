#include "s21_tetris.h"



int main(int argc, char* argv[]) {
    init_ncurses();
    GameInfo_t* t = createGame();
    t->state = START;
    // стадия старт
        // draw_start(t);
        // initActions(t, getch());
        // if (t->action == )
    // while (t->state != EXIT){
    //     if (t->state = PAUSE){
    //         while (t->state != GAME)
    //     }

        // cтадия GAME
        while (t->state != GAME_OVER){
            initActions(t, getch());
            if (t->action == Pause){
                draw_all;
            }
            updateCurrentState(t);
            // drawfield(t);
            draw_all(t);
            usleep(1000);
            
        }
    }

    freeGame(t);
    endwin();
    return 0;
}


