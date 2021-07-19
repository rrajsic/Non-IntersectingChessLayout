#include "Piece.h"
#include "Point2D.h"
#include "Pieces.h"

bool Rook::fillBoard(Chessboard& board) {
	if (fill_L(board) == FAILURE)
		return FAILURE;

	board(m_position.getRow(), m_position.getCol()) = m_type;
	return SUCCESS;
}