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
 * should we keep going?
 */

int iterCheck(int lifeCycles, int iterations);


#endif
