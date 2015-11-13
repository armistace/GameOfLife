#ifndef POSITION_H
#define POSITION_H

#include <iostream>

class Position
{
    private:
        int m_posX;
        int m_posY;

    public:
        Position(): m_posX(0), m_posY(0)
        {
        }

        Position(int nX, int nY): m_posX(nX), m_posY(nY)
        {
        }

        friend std::ostream& operator<<(std::ostream& out, const Position &point)
        {
            out << "(" << point.getX() << ", " << point.getY() << ")";
            return out;
        }

        void setPosition(int nX, int nY)
        {
            m_posX = nX;
            m_posY = nY;
        }

        int getX() const {return m_posX; }
        int getY() const {return m_posY; }
};

#endif
