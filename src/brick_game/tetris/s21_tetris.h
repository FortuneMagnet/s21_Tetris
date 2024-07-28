#ifndef C7_TETRIS_H
#define C7_TETRIS_H

#include <curses.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //Для sleep

#define rows 20
#define cols 10

/*!
 * \brief Enumeration for user actions in the game.
 */
typedef enum {
  Start,     /*!< Start game action */
  Pause,     /*!< Pause game action */
  Terminate, /*!< Terminate game action */
  Left,      /*!< Move figure left action */
  Right,     /*!< Move figure right action */
  Up,        /*!< Rotate figure action */
  Down,      /*!< Move figure down action */
  Action     /*!< Generic action (used for key press handling) */
} UserAction_t;

/*!
 * \brief Structure to store game information.
 */
typedef struct {
  int** field;    /*!< The game field */
  int** next;     /*!< The next figure */
  int score;      /*!< Player score */
  int high_score; /*!< High score */
  int level;      /*!< Current level */
  int speed;      /*!< Game speed */
  int pause;      /*!< Pause state flag */
  int** figure;   /*!< The current figure */
  int x;          /*!< X-coordinate of the figure */
  int y;          /*!< Y-coordinate of the figure */

  int action; /*!< Current user action */

  int ticks; /*!< Game tick counter */
  int state; /*!< Current game state */

} GameInfo_t;

/*!
 * \brief Enumeration for Tetromino shapes.
 */
typedef enum {
  O, /*!< O shape */
  I, /*!< I shape */
  L, /*!< L shape */
  J, /*!< J shape */
  S, /*!< S shape */
  Z, /*!< Z shape */
  T  /*!< T shape */
} Tetramino_t;

/*!
 * \brief Enumeration for game states.
 */
typedef enum {
  START,     /*!< Game start state */
  PAUSE,     /*!< Game paused state */
  GAME,      /*!< Game in progress state */
  GAME_OVER, /*!< Game over state */
  EXIT       /*!< Game exit state */
} GameState_t;

//// LOGIC FUNCTIONS
/*!
 * \brief Copies the next figure to the current figure.
 *
 * \param t Pointer to the GameInfo_t structure.
 */
void fromNextToFigure(GameInfo_t* t);

/*!
 * \brief Drops a new figure.
 *
 *  This function sets the initial position of the new figure, copies the next
 * figure to the current figure, and chooses a new random figure for the next
 * one.
 *
 * \param t Pointer to the GameInfo_t structure.
 */
void dropNewFigure(GameInfo_t* t);

/*!
 * \brief Checks if the current score is higher than the high score.
 *
 *  If the current score is higher, updates the high score in the
 * "hight_score.txt" file.
 *
 * \param t Pointer to the GameInfo_t structure.
 */
void scoreChecker(GameInfo_t* t);

/*!
 * \brief Drops the current figure onto the game field.
 *
 *  Places the current figure onto the game field, marking its cells with the
 * figure value (2).
 *
 * \param t Pointer to the GameInfo_t structure.
 */
void dropFigure(GameInfo_t* t);

/*!
 * \brief Deletes the current figure from the game field.
 *
 *  Clears the cells on the game field that were occupied by the current figure,
 * setting them to 0.
 *
 * \param t Pointer to the GameInfo_t structure.
 */
void deleteFigure(GameInfo_t* t);

/*!
 * \brief Plants the current figure onto the game field.
 *
 *  Places the current figure onto the game field, marking its cells with the
 * planted figure value (1).
 *
 * \param t Pointer to the GameInfo_t structure.
 */
void plantFigure(GameInfo_t* t);

/*!
 * \brief Moves the current figure down.
 *
 *  Increases the Y-coordinate of the figure, moving it down one cell.
 *
 * \param t Pointer to the GameInfo_t structure.
 */
void moveFigureDown(GameInfo_t* t);

/*!
 * \brief Moves the current figure up.
 *
 *  Decreases the Y-coordinate of the figure, moving it up one cell.
 *
 * \param t Pointer to the GameInfo_t structure.
 */
void moveFigureUp(GameInfo_t* t);

/*!
 * \brief Moves the current figure right.
 *
 *  Increases the X-coordinate of the figure, moving it right one cell.
 *
 * \param t Pointer to the GameInfo_t structure.
 */
void moveFigureRight(GameInfo_t* t);

/*!
 * \brief Moves the current figure left.
 *
 *  Decreases the X-coordinate of the figure, moving it left one cell.
 *
 * \param t Pointer to the GameInfo_t structure.
 */
void moveFigureLeft(GameInfo_t* t);

/*!
 * \brief Rotates the current figure.
 *
 *  Rotates the current figure 90 degrees clockwise.
 *
 * \param t Pointer to the GameInfo_t structure.
 */
void rotateFigure(GameInfo_t* t);

/*!
 * \brief Checks for collisions between the current figure and the game field or
 * boundaries.
 *
 *  Returns 1 if a collision is detected, 0 otherwise.
 *
 * \param t Pointer to the GameInfo_t structure.
 * \return 1 if a collision is detected, 0 otherwise.
 */
int collisionTet(GameInfo_t* t);

/*!
 * \brief Calculates the score based on the number of lines erased.
 *
 * \param lines Number of lines erased.
 * \return Score earned for erasing lines.
 */
int countScore(int lines);

/*!
 * \brief Drops a line on the game field.
 *
 *  Shifts all lines above the specified line down one cell, effectively
 * deleting the specified line.
 *
 * \param i Index of the line to drop.
 * \param t Pointer to the GameInfo_t structure.
 */
void dropLine(int i, GameInfo_t* t);

/*!
 * \brief Checks if a line is complete (all cells filled).
 *
 *  Returns 1 if the line is complete, 0 otherwise.
 *
 * \param i Index of the line to check.
 * \param t Pointer to the GameInfo_t structure.
 * \return 1 if the line is complete, 0 otherwise.
 */
int checkLine(int i, GameInfo_t* t);

/*!
 * \brief Erases complete lines from the game field and updates the score.
 *
 *  Iterates through the game field, erases complete lines, drops lines above
 * them, and updates the score based on the number of lines erased.
 *
 * \param t Pointer to the GameInfo_t structure.
 * \return The score earned for erasing lines.
 */
int eraseLinesTet(GameInfo_t* t);

/*!
 * \brief Processes level advancement based on the player's score.
 *
 *  If the player's score exceeds a certain threshold for the current level,
 *  increases the level, adjusts the game speed, and updates the tick rate.
 *
 * \param t Pointer to the GameInfo_t structure.
 */
void levelProcessing(GameInfo_t* t);

GameInfo_t updateCurrentState(GameInfo_t* t);
void gameAlgorithm();

//// FUGIRE FUNCTIONS
/*!
 * \brief Randomly chooses the next figure.
 *
 * This function randomly chooses a figure shape (O, I, L, J, S, Z, or T)
 * and sets the `t->next` array to represent the chosen figure.
 *
 * \param t Pointer to the `GameInfo_t` structure.
 */
void chooseNext(GameInfo_t* t);

/*!
 * \brief Sets the `t->next` array to represent the O shape.
 *
 * \param t Pointer to the `GameInfo_t` structure.
 */
void chooseO(GameInfo_t* t);

/*!
 * \brief Sets the `t->next` array to represent the I shape.
 *
 * \param t Pointer to the `GameInfo_t` structure.
 */
void chooseI(GameInfo_t* t);

/*!
 * \brief Sets the `t->next` array to represent the L shape.
 *
 * \param t Pointer to the `GameInfo_t` structure.
 */
void chooseL(GameInfo_t* t);

/*!
 * \brief Sets the `t->next` array to represent the J shape.
 *
 * \param t Pointer to the `GameInfo_t` structure.
 */
void chooseJ(GameInfo_t* t);

/*!
 * \brief Sets the `t->next` array to represent the S shape.
 *
 * \param t Pointer to the `GameInfo_t` structure.
 */
void chooseS(GameInfo_t* t);

/*!
 * \brief Sets the `t->next` array to represent the Z shape.
 *
 * \param t Pointer to the `GameInfo_t` structure.
 */
void chooseZ(GameInfo_t* t);

/*!
 * \brief Sets the `t->next` array to represent the T shape.
 *
 * \param t Pointer to the `GameInfo_t` structure.
 */
void chooseT(GameInfo_t* t);

//// INIT FUNCTIONS

/*!
 * \brief Creates a new game state.
 *
 * This function allocates memory for a new `GameInfo_t` structure, initializes
 * the game field, the next figure, and the current figure, and sets the initial
 * game state to START.
 *
 * \return A pointer to the newly created `GameInfo_t` structure.
 */
GameInfo_t* createGame();

/*!
 * \brief Restarts the game.
 *
 * This function frees the memory of the current game state, creates a new game
 * state, and returns a pointer to the new state.
 *
 * \param t Pointer to the current game state.
 * \return A pointer to the newly created `GameInfo_t` structure.
 */
GameInfo_t* restartGame(GameInfo_t* t);

/*!
 * \brief Creates the game field.
 *
 * This function allocates memory for the game field and initializes all cells
 * to 0.
 *
 * \param t Pointer to the `GameInfo_t` structure.
 * \return A pointer to the `GameInfo_t` structure with the initialized game
 * field.
 */
GameInfo_t* createField(GameInfo_t* t);

/*!
 * \brief Creates the next figure.
 *
 * This function allocates memory for the next figure and chooses a random shape
 * for it.
 *
 * \param t Pointer to the `GameInfo_t` structure.
 * \return A pointer to the `GameInfo_t` structure with the initialized next
 * figure.
 */
GameInfo_t* createNext(GameInfo_t* t);

/*!
 * \brief Creates the current figure.
 *
 * This function allocates memory for the current figure, initializes it to
 * empty, and drops a new figure onto the game field.
 *
 * \param t Pointer to the `GameInfo_t` structure.
 * \return A pointer to the `GameInfo_t` structure with the initialized current
 * figure.
 */
GameInfo_t* createFigure(GameInfo_t* t);

/*!
 * \brief Creates a temporary figure array.
 *
 * This function allocates memory for a 4x4 temporary array used for figure
 * rotation.
 *
 * \return A pointer to the newly created temporary figure array.
 */
int** createTempFigure();

/*!
 * \brief Frees the temporary figure array.
 *
 * This function frees the memory allocated for the temporary figure array.
 *
 * \param array Pointer to the temporary figure array.
 */
void freeTempFugire(int** array);

/*!
 * \brief Frees the game state memory.
 *
 * This function frees all memory allocated for the game state, including the
 * game field, the next figure, and the current figure.
 *
 * \param t Pointer to the `GameInfo_t` structure.
 */
void freeGame(GameInfo_t* t);

/*!
 * \brief Reads the high score from a file.
 *
 * This function reads the high score from a file named "hight_score.txt".
 *
 * \param t Pointer to the `GameInfo_t` structure.
 */
void scoreReader(GameInfo_t* t);

/*!
 * \brief Initializes user actions based on key input.
 *
 * This function processes user input (key presses) and sets the appropriate
 * action in the `GameInfo_t` structure.
 *
 * \param t Pointer to the `GameInfo_t` structure.
 * \param ch The character representing the key press.
 */
void initActions(GameInfo_t* t, int ch);  //

// FRONT PART
/*!
 * \brief Initializes ncurses library.
 *
 * This function initializes the ncurses library, sets up color pairs, and
 * configures basic terminal settings for the game.
 */
void init_ncurses();

/*!
 * \brief Draws the main game field.
 *
 * This function draws the game field using ncurses, showing the current state
 * of the field with bricks and empty spaces.
 *
 * \param t Pointer to the `GameInfo_t` structure.
 */
void draw_main(GameInfo_t* t);

/*!
 * \brief Draws the "Next" figure area.
 *
 * This function displays the next figure in a separate area on the screen,
 * using ncurses for visual representation.
 *
 * \param t Pointer to the `GameInfo_t` structure.
 */
void draw_next(GameInfo_t* t);

/*!
 * \brief Draws the score, high score, and level information.
 *
 * This function uses ncurses to display the current score, high score, and
 * level in designated areas on the screen.
 *
 * \param t Pointer to the `GameInfo_t` structure.
 */
void draw_score(GameInfo_t* t);

/*!
 * \brief Draws the service field for pause or game over states.
 *
 * This function displays a message box with appropriate text for pause or game
 * over states, using ncurses for visual presentation.
 *
 * \param t Pointer to the `GameInfo_t` structure.
 */
void draw_service_field(GameInfo_t* t);

/*!
 * \brief Draws the starting screen for the Tetris game.
 *
 * This function displays a welcome message and instructions for starting the
 * game using ncurses.
 */
void draw_start_field();

/*!
 * \brief Draws all components of the Tetris game.
 *
 * This function calls other drawing functions to draw the game field, next
 * figure, score, and other relevant information for the current game state.
 *
 * \param t Pointer to the `GameInfo_t` structure.
 */
void draw_all(GameInfo_t* t);

#endif