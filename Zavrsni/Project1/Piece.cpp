#include <iostream>
#include <cstdlib>
#include "Point2D.h"
#include "Piece.h"

int Piece::fillRowAndCol(int** board) {

	for (int i = 0; i < g_board_size; i++)
	{
		for (int j = 0; j < g_board_size; j++)
		{
			if (i == m_position.getRow())
			{
				if (board[i][j] > Type::OCCUPIED)
					return FAILURE;

				board[i][j] = Type::OCCUPIED;
			}											
			if (j == m_position.getCol())
			{
				if (board[i][j] > Type::OCCUPIED)
					return FAILURE;			

				else board[i][j] = Type::OCCUPIED;
			}
		}
	}
	return SUCCESS;
}

int Piece::fillDiagonals(int** board) {
	for (int i = 0; i < g_board_size; i++) {
		for (int j = 0; j < g_board_size; j++) {
			if (abs(i - m_position.getRow()) == abs(j - m_position.getCol())) {
				if (board[i][j] > Type::OCCUPIED)
					return FAILURE;
				else board[i][j] = Type::OCCUPIED;
			}
		}
	}
	return SUCCESS;
}

int Piece::fillOneSpotAround(int** board) {
	for (int i = 0; i < g_board_size; i++) {
		for (int j = 0; j < g_board_size; j++) {
			if ((abs(i - m_position.getRow())) <= 1 && (abs(j - m_position.getCol())) <= 1) {
				if (board[i][j] > Type::OCCUPIED)
					return FAILURE;
				else 
					board[i][j] = Type::BISHOP;
				
			}
		}
	}
	return SUCCESS;
}

int Piece::fill_L(int** board) {
	for (int i = 0; i < g_board_size; i++) {
		for (int j = 0; j < g_board_size; j++) {
			if ((abs(i - m_position.getRow()) == 2 && abs(j - m_position.getCol()) == 1)
				|| (abs(i - m_position.getRow()) == 1 && abs(j - m_position.getCol()) == 2)) {
				if (board[i][j] > Type::OCCUPIED)
					return FAILURE;
				else board[i][j] = Type::OCCUPIED;
			}
		}
	}
	return SUCCESS;
}