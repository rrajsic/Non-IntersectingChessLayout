#pragma once

#define SUCCESS true
#define FAILURE false

extern int g_board_size;

#include "../boards/Chessboard.h"
#include "../engine/EnumType.h"
#include "../engine/Point2D.h"

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
 
	virtual bool placePiece(int x, int y, Chessboard& board) {

		setPosition(x, y);

		if (fillBoard(board) == FAILURE)
			return FAILURE;

		return SUCCESS;
	}

	virtual bool fillBoard(Chessboard& board) = 0;

	virtual const Type getType() { return m_type; }

	bool fillRowAndCol(Chessboard& board);
	bool fillDiagonals(Chessboard& board);
	bool fillOneSpotAround(Chessboard& board);
	bool fill_L(Chessboard& board);
};
