#include "Piece.h"
#include "Point2D.h"
#include "Pieces.h"

bool King::fillBoard(Chessboard& board) {
	if (fillOneSpotAround(board) == FAILURE) {
		return FAILURE;
	}

	board(m_position.getRow(), m_position.getCol()) = m_type;
	return SUCCESS;
}