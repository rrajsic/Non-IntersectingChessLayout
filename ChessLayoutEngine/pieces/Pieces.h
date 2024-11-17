#pragma once

#include "Piece.h"
#include "../engine/EnumType.h"

extern int g_board_size;

class King : virtual public Piece
{
public:
	King() { m_type = Type::KING; }

	bool fillBoard(Chessboard& board);
};

class Queen : virtual public Piece
{
public:
	Queen(){ m_type = Type::QUEEN; }

	bool fillBoard(Chessboard& board);
};

class Rook : virtual public Piece
{
public:
	Rook() { m_type = Type::ROOK; }

	bool fillBoard(Chessboard& board);
};


class Bishop : virtual public Piece
{
public:
	Bishop() { m_type = Type::BISHOP; }

	bool fillBoard(Chessboard& board);

};

class Knight : virtual public Piece
{
public:
	Knight() { m_type = Type::KNIGHT; }
	
	bool fillBoard(Chessboard& board);
};

