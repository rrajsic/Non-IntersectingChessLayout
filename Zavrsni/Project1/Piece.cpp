#include <iostream>
#include <cstdlib>
#include "Chessboard.h"
#include "Point2D.h"
#include "Piece.h"

int Piece::fillRowAndCol(Chessboard& board) {

	for (int i = 0; i < g_board_size; i++)
		for (int j = 0; j < g_board_size; j++){
			if (i == m_position.getRow()){

				if (board(i,j) > Type::OCCUPIED)
					return FAILURE;

				board.set(i, j, Type::OCCUPIED);
			}											
			if (j == m_position.getCol()) {

				if (board(i,j) > Type::OCCUPIED)
					return FAILURE;

				else board.set(i, j, Type::OCCUPIED);
			}
		}

	return SUCCESS;
}

int Piece::fillDiagonals(Chessboard& board) {
	for (int i = 0; i < g_board_size; i++) 
		for (int j = 0; j < g_board_size; j++) 
			if (abs(i - m_position.getRow()) == abs(j - m_position.getCol())) {

				if (board(i,j) > Type::OCCUPIED)
					return FAILURE;
				else board.set(i, j, Type::OCCUPIED);
			}
		
	return SUCCESS;
}

int Piece::fillOneSpotAround(Chessboard& board) {
	for (int i = 0; i < g_board_size; i++) 
		for (int j = 0; j < g_board_size; j++) 
			if ((abs(i - m_position.getRow())) <= 1 && (abs(j - m_position.getCol())) <= 1) {

				if (board(i,j) > Type::OCCUPIED)
					return FAILURE;
				else 
					board.set(i, j, Type::OCCUPIED);	
			}
	
	return SUCCESS;
}

int Piece::fill_L(Chessboard& board) {
	for (int i = 0; i < g_board_size; i++) 
		for (int j = 0; j < g_board_size; j++) 
			if ((abs(i - m_position.getRow()) == 2 && abs(j - m_position.getCol()) == 1)
				|| (abs(i - m_position.getRow()) == 1 && abs(j - m_position.getCol()) == 2)) {

				if (board(i,j) > Type::OCCUPIED)
					return FAILURE;
				else board.set(i, j, Type::OCCUPIED);
			}
		
	return SUCCESS;
}