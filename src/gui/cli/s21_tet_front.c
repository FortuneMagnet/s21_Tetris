#include "../../s21_tetris.h"


void init_ncurses(){
    initscr();      // Инициализация ncurses
    start_color();  // Начало работы с цветами
    curs_set(0);
    cbreak();    // Скрытие курсора
    noecho();  // Отключение отображения введенных символов
    keypad(stdscr, TRUE);  // Включение чтения специальных клавиш
    nodelay(stdscr, true);


    // Инициализация цвета
  // Цвета фигур
  init_pair(1, COLOR_GREEN, COLOR_GREEN);
  init_pair(2, COLOR_GREEN, COLOR_CYAN);
  init_pair(3, COLOR_GREEN, COLOR_BLUE);
  init_pair(4, COLOR_GREEN, COLOR_YELLOW);
  init_pair(5, COLOR_GREEN, COLOR_BLACK);
  init_pair(6, COLOR_GREEN, COLOR_MAGENTA);
  init_pair(7, COLOR_GREEN, COLOR_RED);

  // Цвета боковых полей
  init_pair(8, COLOR_BLUE, COLOR_WHITE);

  // Цвета сервисного поля
  init_pair(9, COLOR_WHITE, COLOR_BLUE);

  // Цвета игрового поля
  init_pair(12, COLOR_WHITE, COLOR_WHITE);
  init_pair(13, COLOR_WHITE, COLOR_BLUE);
}

void draw_main(GameInfo_t* t){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (t->field[i][j] == 0) {
            attron(COLOR_PAIR(12));  // Активация цвета
            mvaddch(2 + i, 4 + j * 2, ' ');
            mvaddch(2 + i, 4 + j * 2 + 1, ' ');
            attroff(COLOR_PAIR(12));  // Деактивация цвета
        }
        if (t->field[i][j] == 1) {
            attron(COLOR_PAIR(6));  // Активация цвета
            mvaddch(2 + i, 4 + j * 2, ' ');
            mvaddch(2 + i, 4 + j * 2 + 1, ' ');
            attroff(COLOR_PAIR(6)); 
            }
        if (t->field[i][j] == 2) {
            attron(COLOR_PAIR(6));  // Активация цвета
            mvaddch(2 + i, 4 + j * 2, ' ');
            mvaddch(2 + i, 4 + j * 2 + 1, ' ');
            attroff(COLOR_PAIR(6)); 
            }           
        }
    }   
}


void draw_next(GameInfo_t* t){
    WINDOW *next_figure_win;
  int startx = 26;
  int starty = 12;
  int width = 12;
  int height = 6;

  next_figure_win = newwin(height, width, starty, startx);
  mvwprintw(next_figure_win, 0, 4, "NEXT");
  wbkgd(next_figure_win, COLOR_PAIR(8));

  wattron(next_figure_win, COLOR_PAIR(1));  // Активация цвета

  int k = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (t->next[i][j] == 2) {
        mvwaddch(next_figure_win, i + 3, j * 2 + 3, ' ');
        mvwaddch(next_figure_win, i + 3, j * 2 + 4, ' ');
      }
      k++;
    }
  }
  wattroff(next_figure_win, COLOR_PAIR(1));  // Деактивация цвета
  wrefresh(next_figure_win);

}

void draw_score(GameInfo_t* t) {
  WINDOW *score_win;
  int startx = 26;
  int starty = 2;
  int width = 12;
  int height = 9;

  score_win = newwin(height, width, starty, startx);
  mvwprintw(score_win, 0, 1, "HIGH SCORE");
  mvwprintw(score_win, 1, 4, "%d", t->high_score);
  mvwprintw(score_win, 3, 3, "SCORE");
  mvwprintw(score_win, 4, 4, "%d", t->score);
  mvwprintw(score_win, 6, 3, "LEVEL");
  mvwprintw(score_win, 7, 4, "%d", t->level);
  wbkgd(score_win, COLOR_PAIR(8));
  wrefresh(score_win);
}

void draw_service_field(GameInfo_t* t) {
  WINDOW *start_win;

  start_win = newwin(6, 18, 9, 5);
  box(start_win, 0, 0);

  if (t->state == PAUSE){
    mvwprintw(start_win, 1, 6, "PAUSE");
    mvwprintw(start_win, 3, 1, "' ' - CONTINUE");
    mvwprintw(start_win, 4, 1, "'Q' - EXIT");
  }
  if (t->state == GAME_OVER){
    mvwprintw(start_win, 1, 4, "GAME OVER!");
    mvwprintw(start_win, 3, 1, "ENTER - ONE MORE");
    mvwprintw(start_win, 4, 1, "'Q' - EXIT");
  }
  wbkgd(start_win, COLOR_PAIR(9));
  wrefresh(start_win);
}

void draw_start_field() {
  WINDOW *start_win;

  start_win = newwin(20, 20, 2, 4);
  box(start_win, 0, 0);

  mvwprintw(start_win, 3, 5, "S21_TETRIS");
  mvwprintw(start_win, 10, 4, "PRESS ENTER");
  mvwprintw(start_win, 11, 6, "TO PLAY");
  mvwprintw(start_win, 18, 1, "by fortunem");
  wbkgd(start_win, COLOR_PAIR(8));
  wrefresh(start_win);
}

void draw_all(GameInfo_t* t){
    draw_next(t);
    draw_score(t);
    // draw_level(t);
    draw_main(t);
}