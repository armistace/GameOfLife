#include <iostream>
#include <string>
#include <cerrno>
#include <unistd.h> //this is deprecated but I am using it to sleep
#include "../core/cell.h"
#include "../core/cellArray.h"
#include "../core/functions.h"
#include <ncurses.h>
#define SPEED_MULTIPLIER 10000

int main(int argc, char *argv[])
{
    using namespace std;
    
    //This allows me to LINES and COLS to determine
    //if the arguments are to much for the current screen
    initscr();

    keypad(stdscr, TRUE);

    //prepare the colors for the terminal
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_BLUE);
    init_pair(2, COLOR_BLACK, COLOR_RED);
    init_pair(3, COLOR_BLACK, COLOR_GREEN);

    //draw the pretty border
    DrawBorder();

    //need to setup some window pointers

    WINDOW* MENU;
    WINDOW* BOARD;
    WINDOW* MESSAGES;
    WINDOW* bMENU;
    WINDOW* bBOARD;
    WINDOW* bMESSAGES;

    //grab some sizeInfo
    int menuSize = COLS - (.8 * COLS);
    int boardSize = COLS - menuSize - 2;
    int messageSize = LINES - (.8 * LINES);

    bMENU = newwin(LINES - messageSize - 3, menuSize, 1, 1);
    wbkgd(bMENU,COLOR_PAIR(3));
    box(bMENU, '|', '-');

    bBOARD = newwin(LINES - messageSize - 3, boardSize, 1, menuSize+1);
    wbkgd(bBOARD, COLOR_PAIR(1));
    box(bBOARD, '|', '-');

    bMESSAGES = newwin(messageSize + 2, COLS - 2, LINES - messageSize - 2, 1);
    wbkgd(bMESSAGES, COLOR_PAIR(2));
    box(bMESSAGES, '|', '-');
    
    MENU = newwin(LINES - messageSize - 5, menuSize - 2, 2, 2);
    wbkgd(MENU,COLOR_PAIR(1));

    BOARD = newwin(LINES - messageSize - 5, boardSize - 2, 2, menuSize+2);
    wbkgd(BOARD, COLOR_PAIR(2));

    MESSAGES = newwin(messageSize, COLS - 4, LINES - messageSize - 1, 2);
    wbkgd(MESSAGES, COLOR_PAIR(3));
    scrollok(MESSAGES, TRUE);

    wprintw(MESSAGES, "WELCOME!\n");
    wprintw(MENU, "OPTIONS\n"
                   "<1>Rows\n"
                   "<2>Columns\n"
                   "<3>Speed\n"
                   "<4>Start\n"
                   "<5>Stop\n"
                   "<6>Finite\n"
                   "<7>Eternal\n"
                   "<8>Quit\n");

    //This is where we set all the arguments based on 
    //the user input
    int lifeCycles, maxRow, maxColumn, speed;
    if (cliHandler(MESSAGES, argv, argc, &lifeCycles, 
            &maxRow, &maxColumn, &speed) != 0)
        return 1;

    //to handle reporting back the user the speed they chose
    //(cliHandler has to convert the figure for something meaningful for usleep
    //I think there is a cleaner way to handle this but meh    
    int speedReturn = speed;
    if (argc == 5)
        speedReturn = atoi(argv[4]);



    //initialise the board
    CellArray board(maxRow, maxColumn);
   
    //seed the random true false generator
    srand(time(0)); 
    
    //fill the board
    board.fillBoard();

    //The above only sets next so we need to switch to turn on
    board.switchState();

    //Draw the board
    //first we initialise the ncurses screen

    //This function handles drawing in the ncurses interface
    board.printBoard(BOARD);
    wprintw(MESSAGES, "ROWS: %d\nCOLUMNS: %d\n", maxRow, maxColumn);
    wprintw(MESSAGES, "Speed: %d\nLifeCycles: %d\n", speedReturn, lifeCycles);
    wprintw(MESSAGES, "Press Key to Start\n"); 
    //print output to the screen
    wrefresh(bBOARD);
    wrefresh(bMENU);
    wrefresh(bMESSAGES);
    wrefresh(BOARD);
    wrefresh(MENU);
    wrefresh(MESSAGES);
    wgetch(MESSAGES);
   
    //Let's Play!
    int iterations = 0;
    bool iterate = true;

    //initialise values to make window do what I want
    cbreak();
    noecho();
    nodelay(MESSAGES, true);
    
    while (iterate)
    {
        int ch; 
        if (ERR != (ch=wgetch(MESSAGES)))
            if (ch==56)
            {
                break;
            }
            else
            {
                inputHandler(ch, MESSAGES, &maxRow, &maxColumn, &speed, &lifeCycles);
                board.changeSize(maxRow, maxColumn);
                board.fillBoard();
                board.switchState();
                board.printBoard(BOARD);
            }

        //first we set the states for the current board
        board.lifeIteration();
    
        //usleep is for visual sanity
        //is based on user entered speed and the multiplier
        usleep(speed * SPEED_MULTIPLIER);
        wclear(BOARD);

        //switch and draw!
	    board.switchState();
	    board.printBoard(BOARD);
	    wrefresh(BOARD);
        wrefresh(MENU);
        wrefresh(MESSAGES);

        //This allows for better user interaction
        //I should be able to use this to cater for 
        //an infinite loop
        //I am going to turn this into a function
        //to make it easier to extend in future

       iterate = iterCheck(lifeCycles, iterations);
       if (iterate)
       {
            iterations++;
       }
       else
       {
           nodelay(MESSAGES, false);
           int response;
           wprintw(MESSAGES, "\nCycles Finished would you like to exit?(y/n): ");
           wrefresh(MESSAGES);
           response = wgetch(MESSAGES);
           while (response != 121 && response != 110)
           {
                wprintw(MESSAGES, "\nUnkown Response please enter y or n: ");
                wprintw(MESSAGES, "\nresponse was %d\n", response);
                wrefresh(MESSAGES);
                response = wgetch(MESSAGES);
           }
           if (response == 110)
           {
               lifeCycles = -1;
               iterate = true;
               wprintw(MESSAGES, "\nContinuing with unlimited Lifecycles\nPlease press a key to continue\n");
               wgetch(MESSAGES);
               nodelay(MESSAGES, true);
           }
           else if(response == 121)
           {
               break;
           }
           else
           {
               wprintw(MESSAGES, "\nUnkown Error, Exiting!\n");
               break;
           }
       }
               

    }
    nodelay(MESSAGES, false);

    //once iterations are finished wait for the user to press a key then destroy the screen
    wprintw(MESSAGES,"\nPress a key to exit\n");
    wrefresh(MESSAGES);
    wgetch(MESSAGES); 
    endwin();
    
    return 0;
}

