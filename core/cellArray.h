#ifndef CELLARRAY_H
#define CELLARRAY_H

#include <ncurses.h>
#include <iostream>
#include <cassert>
#include "cell.h"

class CellArray
{
    private:
        int m_length;
        int m_width;
        Cell *m_cell;

    public:
        CellArray()
        {
            m_length = 0;
            m_width = 0;
            m_cell = 0;
        }

        CellArray(int nLength, int nWidth)
        {
            m_cell = new Cell[nLength*nWidth];
            m_length = nLength;
            m_width = nWidth;
        }
        
        //this cleans up my messes :p
        ~CellArray()
        {
            delete[] m_cell;
        }
        
        //handy
        int rowLength() const {return m_length; }
        int columnLength() const {return m_width; }

	    Cell *get(int row, int column) 
        {
		    return &m_cell[row * m_length + column];
	    }

        /*
         *erases data without destroying the variable
         */
        void Erase();

        /*
         * prints the board
         * TODO: add gtk handler
         */
        void printBoard(WINDOW* screen);
        
        /*
         * Changes the state of current to next
         */
        void switchState();

        /*
         *fills the board with the random TrueFalse Selection
         */
        void fillBoard();

        /*
         *performs one iteration of the board and
         *sets next state for each cell
         */
        void lifeIteration();

        /*
         * allows the manipulation of the size of hte object
         */
        void changeSize(int n_width, int n_length);
};

#endif

