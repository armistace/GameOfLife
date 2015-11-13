#include <iostream>
#include <string>
#include <cerrno>
#include <unistd.h> //this is deprecated but I am using it to sleep
#include "../core/cell.h"
#include "../core/cellArray.h"
#include "../core/functions.h"
#include <ncurses.h>
#define SPEED_MULTIPLIER 10000

void gdb()
{
}

int main(int argc, char *argv[])
{
    using namespace std;
    
    //This allows me to LINES and COLS to determine
    //if the arguments are to much for the current screen
    initscr();


    //This is where we set all the arguments 
    int lifeCycles, maxRow, maxColumn, speed;

    if (argc > 5)
    {
        cout << "Usage: " << argv[0] << "<repitions: default - 100, " 
            << "Max Number of Rows: default - 20, " 
                << "Max Number of Columns: default - 20, " 
                   << "Speed: 1 - 10 integer, 1 is slowest>"
            << endl;
        return 1;
    }

    else if(argc == 2)
    {
        lifeCycles = atoi(argv[1]);
        maxRow = 20;
        maxColumn = 20;
        speed = 5;
    }

    else if (argc == 3)
    {
        lifeCycles = atoi(argv[1]);
        maxRow = atoi(argv[2]);
        maxColumn = 20;
        termCheck(&maxRow, &maxColumn);
        speed = 5;
    }

    else if (argc == 4)
    {
        lifeCycles = atoi(argv[1]);
        maxRow = atoi(argv[2]);
        maxColumn = atoi(argv[3]);
        termCheck(&maxRow, &maxColumn);
        speed = 5;
    }
    
    else if (argc == 5)
    {
        lifeCycles = atoi(argv[1]);
        maxRow = atoi(argv[2]);
        maxColumn = atoi(argv[3]);
        termCheck(&maxRow, &maxColumn);
        speed = atoi(argv[4]);
        if (speed > 10 && speed < 1)
        {
            std::cout << "Speed is outside of range, using default" 
                << std::endl;
            speed = 5;
        }
        else
        {
            speed = 10 - speed;
        }
    }

    else
    {
        lifeCycles = 10;
        maxRow = 20;
        maxColumn = 20;
        termCheck(&maxRow, &maxColumn);
        speed = 5;
    }


    //first we create a board
    //I am going to fill it with a default size of
    //30 by 30 but I will have to build in a way for it
    //to take in from a text file of various size
    //this is just to test my initial algorithm will work


    //initialise the board

    CellArray board(maxRow, maxColumn);
   
    //seed the random true false generator
    srand(time(0)); 
    
    //fill the board
    for (int row = 0; row < maxRow; row++)
    {
        for (int column = 0; column < maxColumn; ++column)
        {
            bool randomState = randomTrueFalse();
	        board.get(row, column)->setPosition(row, column);
	        board.get(row, column)->setState(randomState);
        }
    }

    //The above only sets next so we need to switch to turn on
    board.switchState();

    //Draw the board
    //first we initialise the ncurses screen

    //This function handles drawing in the ncurses interface
    board.printBoard();
    
    //print output to the screen
    refresh();

   
    //Let's Play!
    int iterations = 0;

    while (iterations < lifeCycles)
    {
        //first we set the states for the current board
        for (int row = 0; row < maxRow; ++row)
        {
            for(int column = 0; column < maxColumn; ++column)
            {
                //first we set variables to test state
                Cell *currentCell = board.get(row, column);
                bool preCellState = currentCell->isAlive();
                int nearLiveCells = cellsNearby(&board, currentCell);

		        //we then check if that cell is alive
                bool postCellState = rules(nearLiveCells, preCellState);

                //and set the next state
		        currentCell->setState(postCellState);
            }

        }
    
        //usleep is for visual sanity
        //is based on user entered speed and the multiplier
        usleep(speed * SPEED_MULTIPLIER);
	    clear();

        //switch and draw!
	    board.switchState();
	    board.printBoard();
	    refresh();
    
        //iterate
        iterations++;
    }

    //once iterations are finished wait for the user to press a key
    printw("Press a key to exit");
    getch();
    endwin();
    

    return 0;
}

