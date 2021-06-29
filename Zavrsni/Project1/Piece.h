#ifndef PIECE_H
#define PIECE_H
#include<iostream>
#include "IPiece.h"
#include "Point2D.h"
#include "Constants.h"

class Piece : public IPiece
{
protected:
	Type m_type;
	Point m_position;
	int m_board_size;



public:
	Piece() = default;

	virtual Point getPosition() { return m_position; }
	virtual void setPosition(int x, int y) {
		m_position.setRow(x);
		m_position.setCol(y);
	}

	virtual void printPiece() = 0;

	friend bool operator== (Piece& p1, Piece& p2)
	{
		return (p1.getType() == p2.getType());
	}
	friend bool operator!= (Piece& p1, Piece& p2)
	{
		return !(p1 == p2);
	}

	int fillRowAndCol(int** board);
	int fillDiagonals(int** board);
	int fillOneSpotAround(int** board);
	int fill_diagonal_DownardRight(int** board);
	int fill_diagonal_DownardLeft(int** board);
	int fill_diagonal_UpwardRight(int** board);
	int fill_diagonal_UpwardLeft(int** board);
	int fill_OneSpotAround(int** board);
	int fill_L(int** board);
};




class King : virtual public Piece, virtual public IPiece
{

public:
	King(int board_size) { m_board_size = board_size; m_type = Type::KING; }

	int placePiece(int x, int y, int** board) {

		setPosition(x, y);


		if (fillBoard(board) == FAILURE) {
			return FAILURE;
		}

		board[x][y] = static_cast<int>(Type::KING);
		return SUCCESS;
	}

	int fillBoard(int** board) {
		if (fillOneSpotAround(board) == FAILURE) {
			return FAILURE;
		}

		else return SUCCESS;
	}

	void printPiece() override { std::cout << "King" << std::endl; }
	const Type getType() { return m_type; }
	
};

class Queen : virtual public Piece, virtual public IPiece
{
public:
	Queen(int board_size){ m_board_size = board_size; m_type = Type::QUEEN; }

	int placePiece(int x, int y, int** board) {

		setPosition(x, y);

		if (fillBoard(board) == FAILURE)
			return FAILURE;


		board[x][y] = static_cast<int>(Type::QUEEN);
		return SUCCESS;
	}

	int fillBoard(int** board) {
		if (fillRowAndCol(board) == FAILURE)
			return FAILURE;
		if (fillDiagonals(board) == FAILURE)
			return FAILURE;
			
		return SUCCESS;
	}
	void printPiece() override { std::cout << "Queen" << std::endl; }
	const Type getType() { return m_type; }
};

class Rook : public Piece, virtual public IPiece
{
public:
	Rook(int board_size) { m_board_size = board_size; m_type = Type::ROOK; }

	int placePiece(int x, int y, int** board) {

		setPosition(x, y);

		if (fillBoard(board) == FAILURE)
			return FAILURE;

		board[x][y] = static_cast<int>(Type::ROOK);
		return SUCCESS;
	}
	int fillBoard(int** board) {
		if (fillRowAndCol(board) == FAILURE)
			return FAILURE;

		return SUCCESS;
	}
	void printPiece() override { std::cout << "Rook" << std::endl; }
	const Type getType() { return m_type; }
};


class Bishop : public Piece, virtual public IPiece
{
public:
	Bishop(int board_size) { m_board_size = board_size; m_type = Type::BISHOP; }
	int placePiece(int x, int y, int** board) {

		setPosition(x, y);

		if (fillBoard(board) == FAILURE)
			return FAILURE;


		board[x][y] = static_cast<int>(Type::BISHOP);
		return SUCCESS;
	}
	int fillBoard(int** board) {

		if (fillDiagonals(board) == FAILURE)
			return FAILURE;

		return SUCCESS;
	}
	void printPiece() override { std::cout << "Bishop" << std::endl; }
	const Type getType() { return m_type; }

};

class Knight : public Piece, virtual public IPiece
{
public:
	Knight(int board_size) { m_board_size = board_size; m_type = Type::KNIGHT; }
	int placePiece(int x, int y, int** board) {

		setPosition(x, y);

		if (fillBoard(board) == FAILURE)
			return FAILURE;


		board[x][y] = static_cast<int>(Type::KNIGHT);
		return SUCCESS;
	}

	int fillBoard(int** board) {
		if (fill_L(board) == FAILURE)
			return FAILURE;

		return SUCCESS;
	}
	void printPiece() override { std::cout << "Knight" << std::endl; }
	const Type getType() { return m_type; }
};

#endif

