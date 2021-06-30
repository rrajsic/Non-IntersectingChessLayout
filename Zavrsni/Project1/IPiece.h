#ifndef IPIECE_H
#define IPIECE_H

#include "EnumType.h"
#include "EnumType2.h"

class IPiece
{
public:
	virtual int placePiece(int x, int y, int** board) = 0;
	const virtual Type getType() = 0;
	virtual int fillBoard(int **board) = 0;
	const virtual Type2 getType2() = 0;
};

#endif
