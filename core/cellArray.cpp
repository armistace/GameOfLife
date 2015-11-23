#include <iostream>
#include <ncurses.h>
#include "cell.h"
#include "cellArray.h"
#include "functions.h"

void CellArray::Erase()
{
    delete[] m_cell;
    
    m_length = 0;
    m_width = 0;
}

/*
 * function to change parameters of array
 */
void CellArray::changeSize(int n_width, int n_length)
{
    m_width = n_width;
    m_length = n_length;
}

       
/*
 * printBoard ncurses interface
 * it also only handles the printw() case all other functions
 * to dray on the screen will need to be called around this 
 * function
 */
void CellArray::printBoard(WINDOW* screen)
{
    for (int row = 0; row < m_length; row++)
    {
        for (int column = 0; column < m_width; column++)
        {
		    get(row, column)->isAlive() ? wprintw(screen,"*") : wprintw(screen,".");
        }
        wprintw(screen,"\n");
    }
}

/*
 * TODO: printBoard GTK interface
 */


/*
 * switch old and new state of the board
 */

void CellArray::switchState()
{
	for (int row = 0; row < m_length; row++)
	{
		for (int column = 0; column < m_width; column++)
		{
			get(row, column)->switchState();
		}
	}
}

void CellArray::fillBoard()
{
     for (int row = 0; row < m_length; row++)
     {
         for (int column = 0; column < m_width; ++column)
         {
            bool randomState = randomTrueFalse();
            this->get(row, column)->setPosition(row, column);
            this->get(row, column)->setState(randomState);
         }
     }
}

void CellArray::lifeIteration()
{
	for (int row = 0; row < m_length; ++row)
    {
        for(int column = 0; column < m_width; ++column)
        {
            //first we set variables to test state
            Cell *currentCell = this->get(row, column);
            bool preCellState = currentCell->isAlive();
            int nearLiveCells = cellsNearby(this, currentCell);

            //we then check if that cell is alive
            bool postCellState = rules(nearLiveCells, preCellState);

            //and set the next state
            currentCell->setState(postCellState);
        }

    }
}

