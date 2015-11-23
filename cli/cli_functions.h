#ifndef CLI_FUNCTIONS_H
#define CLI_FUNCTIONS_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include "../core/position.h"
#include "../core/cell.h"
#include "../core/cellArray.h"
#include "../core/functions.h"


/*
 * checks the requested size fits in the window
 * if not it will change the value of maxRow and
 * maxColumn
 */
void termCheck(int *maxRow, int *maxColumn, WINDOW* MESSAGES);

/*
 * Easy way to Draw a border I might
 * rejig it to take an ncurses window pointer
 */
void DrawBorder();

/*
 * Handles cli arguments
 */
int cliHandler(WINDOW *MESSAGES, char *argv[], int args, int *lifeCycles,
        int *maxRow, int *maxColumn, int *speed);


/*
 * This function handles the input from the ncurses board
 */
void inputHandler(int ch, WINDOW *MESSAGES, int *maxRow, 
        int *maxColumn, int *speed, int *lifeCycles);

#endif
