#include "s21_tetris.h"


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

// void draw_field_score(int high_score, int score) {
//   WINDOW *score_win;
//   int startx = 26;
//   int starty = 2;
//   int width = 12;
//   int height = 9;

//   score_win = newwin(height, width, starty, startx);
//   mvwprintw(score_win, 0, 1, "HIGH SCORE");
//   mvwprintw(score_win, 2, 4, "%d", high_score);
//   mvwprintw(score_win, 4, 3, "SCORE");
//   mvwprintw(score_win, 6, 4, "%d", score);
//   wbkgd(score_win, COLOR_PAIR(8));
//   wrefresh(score_win);
// }

void draw_all(GameInfo_t* t){
    draw_next(t);
    // draw_score(t);
    // draw_level(t);
    draw_main(t);
}