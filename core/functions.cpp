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
 * This does bounds checking for rows and columns 
 * depends on ncurses
 */

void termCheck(int *maxRow, int *maxColumn, WINDOW *MESSAGES)
{
    int boardLines = LINES - ((.8 * LINES) - 5);
    if (*maxRow > LINES - boardLines)
    {
        *maxRow = LINES - boardLines;
        wprintw(MESSAGES, "Number of Rows greater than terminal size"
            ", reducing to fit terminal\n");
    }

    //the cols figure is based on the drawable board size or
    //which is 80% of the the windo
   
    int boardCols = COLS - ((.2 * COLS) - 4);

    //deal with the menu
    if (*maxColumn > boardCols - 9)
    {
        *maxColumn = boardCols - 9;
        wprintw(MESSAGES, "Number of Columns greater than terminal size"
            ", reducing to fit terminal\n");
    }
}

/*
 *easy way to draw stuff around the screen
 */
void DrawBorder()
{
    clear();
    box(stdscr, '-', '-');
}

/*
 *This function is designed to handle the cli arguments it needs all these pointers as this
 *it what sets up the rest of the game
 */
int cliHandler(WINDOW *MESSAGES, char *argv[], int args, int *lifeCycles, int *maxRow, int *maxColumn, int *speed)
{
	using namespace std;

	if (args > 5)
    {
        cout << "Usage: " << argv[0] << "<repitions: default - infinite, "
             << "Max Number of Rows: default - 20, " 
             << "Max Number of Columns: default - 20, " 
             << "Speed: 1 - 10 integer, 1 is slowest>"
             << endl;
        return 1;
    }

    else if(args == 2)
    {
        *lifeCycles = atoi(argv[1]);
        *maxRow = 20;
        *maxColumn = 20;
        *speed = 5;
		return 0;
    }

    else if (args == 3)
    {
        *lifeCycles = atoi(argv[1]);
        *maxRow = atoi(argv[2]);
        *maxColumn = 20;
        termCheck(maxRow, maxColumn, MESSAGES);
        *speed = 5;
		return 0;
    }

    else if (args == 4)
    {
        *lifeCycles = atoi(argv[1]);
        *maxRow = atoi(argv[2]);
        *maxColumn = atoi(argv[3]);
        termCheck(maxRow, maxColumn, MESSAGES);
        *speed = 5;
		return 0;
    }
	else if (args == 5)
    {
        *lifeCycles = atoi(argv[1]);
        *maxRow = atoi(argv[2]);
        *maxColumn = atoi(argv[3]);
        termCheck(maxRow, maxColumn, MESSAGES);
        *speed = atoi(argv[4]);
        if (*speed > 10 || *speed < 1)
        {
            std::cout << "Speed is outside of range, using default"
                << std::endl;
            *speed = 5;
        }
        else
        {
            *speed = 11 - *speed;
        }
		return 0;
    }

    else
    {
        *lifeCycles = -1;
        *maxRow = 20;
        *maxColumn = 20;
        termCheck(maxRow, maxColumn, MESSAGES);
        *speed = 5;
        return 0;
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

/*
 * depends on ncurses
 * it will handle the cli input while the program is running
 * TODO: Error handling in this is atrocius and needs rework
 */
void inputHandler(int ch, WINDOW *MESSAGES, int *maxRow, int *maxColumn, int *speed, int *lifeCycles)
{
    switch(ch)
    {
        case(49):
            char stringRows[10];
            int numRows;
            nodelay(MESSAGES, false);
            wprintw(MESSAGES, "Please enter number of rows: ");
            wrefresh(MESSAGES);
            wgetnstr(MESSAGES, stringRows, 9);
            numRows = atoi(stringRows);
            wprintw(MESSAGES, "\nNumber of Rows will change from %d to %d\nPress a key to continue\n", *maxRow, numRows);
            wgetch(MESSAGES);
            *maxColumn = numRows;
            termCheck(maxColumn, maxRow, MESSAGES);
            nodelay(MESSAGES, true);
            break;
        
        case(50):
            char stringCols[10];
            int numCols;
            nodelay(MESSAGES, false);
            wprintw(MESSAGES, "Please enter number of columns: ");
            wrefresh(MESSAGES);
            wgetnstr(MESSAGES, stringCols, 9);
            numCols = atoi(stringCols);
            wprintw(MESSAGES, "\nNumber of Columns will change from %d to %d\nPress a key to continue\n", *maxColumn, numCols);
            wgetch(MESSAGES);
            *maxRow = numCols;
            termCheck(maxColumn, maxRow, MESSAGES);
            nodelay(MESSAGES, true);
            break;
        
        case(51):
            char stringSpeed[10];
            int numSpeed;
            nodelay(MESSAGES,false);
            wprintw(MESSAGES,"Please enter new speed: ");
            wrefresh(MESSAGES);
            wgetnstr(MESSAGES, stringSpeed, 9);
            numSpeed = atoi(stringSpeed);
            wprintw(MESSAGES, "\nSpeed will change from %d to %d\nPress a key to continue\n", *speed, numSpeed);
            wgetch(MESSAGES);
            *speed = numSpeed;
            if (*speed > 10 || *speed < 1)
            {
                wprintw(MESSAGES,"Speed is outside of range, using 5\n");
                *speed = 5;
            }
            else
            {
                *speed = 11 - *speed;
            }
            nodelay(MESSAGES, true);
            break;
        
        case(52):
            wprintw(MESSAGES, "Now Starting\n");
            nodelay(MESSAGES, true);
            break;

        case(53):
            wprintw(MESSAGES, "Now Stopping\n");
            nodelay(MESSAGES, false);
            break;

        case(54):
            char stringCycles[10];
            int numCycles;
            nodelay(MESSAGES, false);
            wprintw(MESSAGES, "Please enter number of life cycles: ");
            wrefresh(MESSAGES);
            wgetnstr(MESSAGES, stringCycles, 9);
            numCycles = atoi(stringCycles);
            wprintw(MESSAGES, "\nLife Cycles will change from %d to %d\nPress a key to continue\n", *lifeCycles, numCycles);
            wgetch(MESSAGES);
            *lifeCycles = numCycles;
            nodelay(MESSAGES, true);
            break;

        case(55):
            nodelay(MESSAGES, false);
            wprintw(MESSAGES, "Now moving to unlimited life cycles\n Press a key to continue\n");
            wrefresh(MESSAGES);
            wgetch(MESSAGES);
            *lifeCycles = -1;
            nodelay(MESSAGES, true);
            break;


 
       //default:
         //   wprintw(MESSAGES, "ch = %d", ch);
           // break;
    }
    
}


              
    

