#include <iostream>
#include <cstdlib>
#include <ctime>
#include "position.h"
#include "cell.h"
#include "cellArray.h"

/*
 * this will generate a random true false
 * to fill a random board
 * I may leave this as default or remove it
 * and keep it just for testing srand will need to be called
 * before it
 */
bool randomTrueFalse()
{
    //generate a random number between 0 and 100
    int r = rand() % 10001;
        
    bool returnValue;
    //true if above 5000 false if below

    r > 5000 ? returnValue = true : returnValue = false;

    return returnValue;
}

/*
 * cellsNearby takes in a cell array pointer 
 * and cell and will return the number of live cells nearby
 */
int cellsNearby(CellArray *board, Cell *currentCell ) // currently is still returning 1 to many many need to examine
{
    //this lets us determine how many cells nearby
    int liveCellsNearby = 0;

    int row, column, maxRow, maxColumn;

    //this logic works better than my inital
    //it does use more memory than mine by doing checks for every cell 
    for (row = currentCell->cellY() - 1; row <= currentCell->cellY() + 1; row++)
    {
	    if (row < 0 || row >= board->rowLength())
		    continue;

	    for (column = currentCell->cellX() - 1; column <= currentCell->cellX() + 1; column++) 
        {
		    if (column < 0 || column >= board->columnLength())
			    continue;

		    if (board->get(row, column)->isAlive())
			    liveCellsNearby++;
	    }
    }

    //we minus one so as not include the actual cell being counted
    return liveCellsNearby - 1;
}

/*
 * Implements the rules of LIFE!
 */
bool rules(int liveCellsNearby, bool currentLifeCondition) 
{
    if (!currentLifeCondition)
    {
        switch(liveCellsNearby)
        {
            case(2):
                return true;
            case(3):
                return true;
            default:
                return false;
        }
    }
    else
    {
        switch(liveCellsNearby)
        {
            case(3):
                return true;
            default:
                return false;
        }
    }
}

/*
 * This function will handle the iterations
 * It will return false on any condition of the following
 * conditions:
 * lifeCycles < iterations
 * input from getch() (through ch) has been detected
 * if neither of these conditions have been met it will return true
 */

bool iterCheck(int lifeCycles, int iterations)
{
    if (lifeCycles == -1)
        return true;
    if (iterations < lifeCycles)
    {
        return true;
    }
    else
    {
        return false;
    }
     
}



              
    

