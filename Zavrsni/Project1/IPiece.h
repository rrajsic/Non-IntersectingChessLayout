#ifndef IPIECE_H
#define IPIECE_H

#include "EnumType.h"
#include "Constants.h"

class IPiece
{
public:
	virtual int placePiece(int x, int y, int** board) = 0;
	const virtual Type getType() = 0;
	virtual void printPiece() = 0;
};

#endif
