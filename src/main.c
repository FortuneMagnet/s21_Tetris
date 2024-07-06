#include "tetris.h"



int main(int argc, char* argv[]) {

    initscr(); // инициализация нкурсес
    // добавить цвет
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    scrollok(stdscr, TRUE);

    GameInfo_t* t = createGame();
    
    while (1){
        int ch = getch();
        initActions(t, ch);

        updateCurrentState(t);
        drawfield(t);
        usleep(100000);
        if (t->stop_game == 1)
            break;
    }
    freeGame(t);
    endwin();
    return 0;
}


