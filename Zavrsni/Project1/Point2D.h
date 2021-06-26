
#ifndef POINT2D_H
#define POINT2D_H
#include <cassert>

class Point
{
private:
	int m_x = 0;
	int m_y = 0;

public:
	Point() = default;

	Point(int x, int y)
	{
		assert(x > 0);
		assert(y > 0);

		m_x = x;
		m_y = y;

	}

	void setRow(int x) { m_x = x; }
	void setCol(int y) { m_y = y; }

	int getRow() { return m_x; }
	int getCol() { return m_y; }
};




#endif