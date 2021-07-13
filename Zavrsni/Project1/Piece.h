#ifndef IPIECE_H
#define IPIECE_H

#define SUCCESS 0
#define FAILURE -1

extern int g_board_size;

#include "Chessboard.h"
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
 
	virtual int placePiece(int x, int y, Chessboard& board) {

		setPosition(x, y);

		if (fillBoard(board) == FAILURE)
			return FAILURE;

		return SUCCESS;
	}

	virtual int fillBoard(Chessboard& board) = 0;

	virtual const Type getType() { return m_type; }

	int fillRowAndCol(Chessboard& board);
	int fillDiagonals(Chessboard& board);
	int fillOneSpotAround(Chessboard& board);
	int fill_L(Chessboard& board);
};

#endif
