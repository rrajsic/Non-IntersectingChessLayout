#ifndef PIECEFUNCTIONS_H
#define PIECEFUNCTIONS_H

#include "Point2D.h"
#include "Constants.h"
int fillRowAndCol(int** board, Point position,int board_size);
int fill_diagonal_DownardRight(int** board, Point position, int board_size);
int fill_diagonal_DownardLeft(int** board, Point position, int board_size);
int fill_diagonal_UpwardRight(int** board, Point position, int board_size);
int fill_diagonal_UpwardLeft(int** board, Point position, int board_size);
int fill_OneSpotAround(int** board, Point position, int board_size);
int fill_L(int** board, Point position, int board_size);

int fill_King(int** board, Point position, int board_size);
int fill_Queen(int** board, Point position, int board_size);
int fill_Rook(int** board, Point position, int board_size);
int fill_Bishop(int** board, Point position, int board_size);
int fill_Knight(int** board, Point position, int board_size);

#endif