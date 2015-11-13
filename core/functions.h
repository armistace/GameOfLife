#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include "position.h"
#include "cell.h"
#include "cellArray.h"

/*
 * cellsNearby takes in the current cell and the board
 * and will return the number of nearby live cells
 * for feeding into the rules
 */

int cellsNearby(CellArray *board, Cell *currentCell);

/*
 * rules will return whether or not any given cell
 * should be alive
 */
bool rules (int liveCellsNearby, bool currentLifeCondition);

/*
 * This generates a random true false
 * to seed a board 
 * don't know if for testing or default yet
 */

bool randomTrueFalse();

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
 * should we keep going?
 */

int iterCheck(int lifeCycles, int iterations);

void inputHandler(int ch, WINDOW *MESSAGES, int *maxRow, 
        int *maxColumn, int *speed, int *lifeCycles);

#endif
