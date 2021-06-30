#ifndef PIECE_H
#define PIECE_H


#include<iostream>
#include "Piece.h"
#include "Point2D.h"

extern int g_board_size;

class King : virtual public Piece
{

public:
	King() { m_type = Type::KING; }

	int fillBoard(int** board) {
		if (fillOneSpotAround(board) == FAILURE) {
			return FAILURE;
		}

		board[m_position.getRow()][m_position.getCol()] = m_type;
		return SUCCESS;
	}
};

class Queen : virtual public Piece
{
public:
	Queen(){ m_type = Type::QUEEN; }

	int fillBoard(int** board) {
		if (fillRowAndCol(board) == FAILURE)
			return FAILURE;
		if (fillDiagonals(board) == FAILURE)
			return FAILURE;
			
		board[m_position.getRow()][m_position.getCol()] = m_type;
		return SUCCESS;
	}
};

class Rook : virtual public Piece
{
public:
	Rook() { m_type = Type::ROOK; }

	int fillBoard(int** board) {
		if (fillRowAndCol(board) == FAILURE)
			return FAILURE;

		board[m_position.getRow()][m_position.getCol()] = m_type;
		return SUCCESS;
	}
};


class Bishop : virtual public Piece
{
public:
	Bishop() { m_type = Type::BISHOP; }

	int fillBoard(int** board) {

		if (fillDiagonals(board) == FAILURE)
			return FAILURE;

		board[m_position.getRow()][m_position.getCol()] = m_type;
		return SUCCESS;
	}

};

class Knight : virtual public Piece
{
public:
	Knight() { m_type = Type::KNIGHT; }
	

	int fillBoard(int** board) {
		if (fill_L(board) == FAILURE)
			return FAILURE;

		board[m_position.getRow()][m_position.getCol()] = m_type;
		return SUCCESS;
	}
};

#endif

