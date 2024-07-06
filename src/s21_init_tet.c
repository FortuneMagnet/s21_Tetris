#include "s21_tetris.h"

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