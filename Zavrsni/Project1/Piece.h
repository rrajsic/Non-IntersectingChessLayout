#ifndef IPIECE_H
#define IPIECE_H

#define SUCCESS 0
#define FAILURE -1
extern int g_board_size;

#include "EnumType.h"
#include "Point2D.h"

class Piece
{
protected:
	Type m_type;
	Point m_position;

public:
	Piece() = default;

	virtual Point getPosition() { return m_position; }
	virtual void setPosition(int x, int y) {
		m_position.setRow(x);
		m_position.setCol(y);
	}
 
	virtual int placePiece(int x, int y, int** board) {

		setPosition(x, y);

		if (fillBoard(board) == FAILURE)
			return FAILURE;


		return SUCCESS;
	}

	virtual int fillBoard(int **board) = 0;

	virtual const Type getType() { return m_type; }

	int fillRowAndCol(int** board);
	int fillDiagonals(int** board);
	int fillOneSpotAround(int** board);
	int fill_L(int** board);
};

#endif
