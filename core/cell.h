#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <cassert>
#include "position.h"

class Cell
{
    private:
        Position m_position;
        bool m_alive;
	    bool m_alive_next;


    public:
        Cell(Position position, bool alive):  m_position(position), m_alive(alive)
        {
        }

        Cell() : m_alive(false)
        {
        }

    	~Cell()
	    {
        }
        

        bool isAlive() {return m_alive;}

        int cellX() const {return m_position.getX(); }
        int cellY() const {return m_position.getY(); }

        void setPosition(int nX, int nY);

        void setState(bool LifeState);

	    void switchState();

};

#endif        
