#include "cell.h"

void Cell::setPosition(int nX, int nY)
{
    m_position.setPosition(nX, nY);
}

void Cell::setState(bool lifeState)
{
    m_alive_next = lifeState;
}

void Cell::switchState()
{
	m_alive = m_alive_next;
}
