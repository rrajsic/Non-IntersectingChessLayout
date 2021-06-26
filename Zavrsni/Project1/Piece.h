#ifndef PIECE_H
#define PIECE_H
#include<iostream>
#include "IPiece.h"
#include "Point2D.h"
#include "Constants.h"
#include "PieceFunctions.h"

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

};




class King : virtual public Piece, virtual public IPiece
{

public:
	King(int board_size) { m_board_size = board_size; m_type = Type::KING; }

	int placePiece(int x, int y, int** board) override {

		setPosition(x, y);


		if (fill_King(board, m_position, m_board_size) == FAILURE) {
			return FAILURE;
		}

		board[x][y] = 2;
		return SUCCESS;
	}

	void printPiece() override { std::cout << "King" << std::endl; }
	const Type getType() { return m_type; }
	
};

class Queen : virtual public Piece, virtual public IPiece
{
public:
	Queen(int board_size){ m_board_size = board_size; m_type = Type::QUEEN; }

	int placePiece(int x, int y, int** board) override {

		setPosition(x, y);

		if (fill_Queen(board, m_position,m_board_size) == FAILURE)
			return FAILURE;


		board[x][y] = 3;
		return SUCCESS;
	}

	void printPiece() override { std::cout << "Queen" << std::endl; }
	const Type getType() { return m_type; }
	
};

class Rook : public Piece, virtual public IPiece
{
public:
	Rook(int board_size) { m_board_size = board_size; m_type = Type::ROOK; }

	int placePiece(int x, int y, int** board) override {

		setPosition(x, y);

		if (fill_Rook(board, m_position,m_board_size) == FAILURE)
			return FAILURE;


		board[x][y] = 6;
		return SUCCESS;
	}
	void printPiece() override { std::cout << "Rook" << std::endl; }
	const Type getType() { return m_type; }

};


class Bishop : public Piece, virtual public IPiece
{
public:
	Bishop(int board_size) { m_board_size = board_size; m_type = Type::BISHOP; }
	int placePiece(int x, int y, int** board) override {

		setPosition(x, y);

		if (fill_Bishop(board, m_position,m_board_size) == FAILURE)
			return FAILURE;


		board[x][y] = 4;
		return SUCCESS;
	}
	void printPiece() override { std::cout << "Bishop" << std::endl; }
	const Type getType() { return m_type; }

};

class Knight : public Piece, virtual public IPiece
{
public:
	Knight(int board_size) { m_board_size = board_size; m_type = Type::KNIGHT; }
	int placePiece(int x, int y, int** board) override {

		setPosition(x, y);

		if (fill_Knight(board, m_position,m_board_size) == FAILURE)
			return FAILURE;


		board[x][y] = 5;
		return SUCCESS;
	}
	void printPiece() override { std::cout << "Knight" << std::endl; }
	const Type getType() { return m_type; }

};

#endif

