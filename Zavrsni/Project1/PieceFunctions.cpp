#include<iostream>
#include "PieceFunctions.h"
#include "Point2D.h"
#include "Constants.h"

int fillRowAndCol(int** board, Point position,int board_size) {

	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
		{
			if (i == position.getRow())
			{
				if (board[i][j] > 1)return FAILURE;
				board[i][j] = 1;
			}											//all rows are now taken
			if (j == position.getCol())
			{
				if (board[i][j] > 1)return FAILURE;			//all columns are now taken
				board[i][j] = 1;
			}
		}
	}

	return SUCCESS;
}

int fill_diagonal_DownardRight(int** board, Point position,int board_size)
{
	int x = position.getRow();
	int y = position.getCol();

	for (int i = x; i < board_size; i++)			//Fills diagonal: Right - down
	{
		int j = y;
		if (i + 1 >= board_size)break;
		if (j + 1 >= board_size)break;
		if (board[i + 1][j + 1] > 1)return FAILURE;		//if there is a figure there (king, queen, etc..) 
		board[i + 1][j + 1] = 1;
		y++;
	}

	return SUCCESS;
}

int fill_diagonal_DownardLeft(int** board, Point position,int board_size)
{
	int x = position.getRow();
	int y = position.getCol();

	for (int i = x; i < board_size; i++)			//Fills diagonal: Left - down
	{
		int j = y;
		if (i + 1 >= board_size)break;
		if (j - 1 < 0)break;
		if (board[i + 1][j - 1] > 1)return FAILURE;		//if there is a figure there (king, queen, etc..)
		board[i + 1][j - 1] = 1;
		y--;
	}
	return SUCCESS;
}

int fill_diagonal_UpwardRight(int** board, Point position,int board_size)
{
	int x = position.getRow();
	int y = position.getCol();

	for (int i = x; i >= 0; i--)					//Fills diagonal: Right - up
	{
		int j = y;
		if (i - 1 < 0)break;
		if (j + 1 >= board_size)break;
		if (board[i - 1][j + 1] > 1)return FAILURE;			//if there is a figure there (king, queen, etc..)
		board[i - 1][j + 1] = 1;
		y++;
	}
	return SUCCESS;
}

int fill_diagonal_UpwardLeft(int** board, Point position, int board_size)
{
	int x = position.getRow();
	int y = position.getCol();

	for (int i = x; i >= 0; i--)					//Fills diagonal: Left - up
	{
		int j = y;
		if (i - 1 < 0)break;
		if (j - 1 < 0)break;
		if (board[i - 1][j - 1] > 1)return FAILURE;			//if there is a figure there (king, queen, etc..)
		board[i - 1][j - 1] = 1;
		y--;
	}
	return SUCCESS;
}

int fill_OneSpotAround(int** board, Point position,int board_size)
{
	int x = position.getRow();
	int y = position.getCol();

	//we set all 8 spots to 1 seperately
	if (x + 1 < board_size)
	{
		if (board[x + 1][y] < 2)
			board[x + 1][y] = 1;

		else return FAILURE;

		if (y + 1 < board_size)
		{
			if (board[x + 1][y + 1] < 2)		//if there isn't a figure place 1 
				board[x + 1][y + 1] = 1;
			else return FAILURE;
		}
	}

	if (x - 1 >= 0)
	{
		if (board[x - 1][y] < 2)
			board[x - 1][y] = 1;
		else return FAILURE;

		if (y - 1 >= 0)
		{
			if (board[x - 1][y - 1] < 2)
				board[x - 1][y - 1] = 1;
			else return FAILURE;
		}
	}
	if (y + 1 < board_size)
	{
		if (board[x][y + 1] < 2)
			board[x][y + 1] = 1;
		else return FAILURE;

		if (x - 1 >= 0)
		{
			if (board[x - 1][y + 1] < 2)
				board[x - 1][y + 1] = 1;
			else return FAILURE;
		}
	}
	if (y - 1 >= 0)
	{
		if (board[x][y - 1] < 2)
			board[x][y - 1] = 1;
		else return FAILURE;

		if (x + 1 < board_size)
		{
			if (board[x + 1][y - 1] < 2)
				board[x + 1][y - 1] = 1;
			else return FAILURE;
		}
	}
	return SUCCESS;
}

int fill_L(int** board, Point position,int board_size)									//this is a knight, but K is busy
{
	int x = position.getRow();
	int y = position.getCol();
	//we set all 8 spots to 1 seperately
	if ((x + 1 < board_size) && (y + 2 < board_size))
	{
		if (board[x + 1][y + 2] < 2)							//if there isn't a figure place 1 
			board[x + 1][y + 2] = 1;
		else return FAILURE;
	}
	if ((x + 1 < board_size) && (y - 2 >= 0))
	{
		if (board[x + 1][y - 2] < 2)							//if there isn't a figure place 1 
			board[x + 1][y - 2] = 1;
		else return FAILURE;
	}

	if ((x - 1 >= 0) && (y + 2 < board_size))
	{
		if (board[x - 1][y + 2] < 2)
			board[x - 1][y + 2] = 1;
		else return FAILURE;
	}
	if ((x - 1 >= 0) && (y - 2 >= 0))
	{
		if (board[x - 1][y - 2] < 2)
			board[x - 1][y - 2] = 1;
		else return FAILURE;
	}
	if ((x + 2 < board_size) && (y + 1 < board_size))
	{
		if (board[x + 2][y + 1] < 2)							//if there isn't a figure place 1 
			board[x + 2][y + 1] = 1;
		else return FAILURE;
	}
	if ((x + 2 < board_size) && (y - 1 >= 0))
	{
		if (board[x + 2][y - 1] < 2)							//if there isn't a figure place 1 
			board[x + 2][y - 1] = 1;
		else return FAILURE;
	}

	if ((x - 2 >= 0) && (y + 1 < board_size))
	{
		if (board[x - 2][y + 1] < 2)
			board[x - 2][y + 1] = 1;
		else return FAILURE;
	}
	if ((x - 2 >= 0) && (y - 1 >= 0))
	{
		if (board[x - 2][y - 1] < 2)
			board[x - 2][y - 1] = 1;
		else return FAILURE;
	}
}

int fill_King(int** board, Point position,int board_size) {
	if (fill_OneSpotAround(board, position, board_size) == FAILURE) {
		return FAILURE;
	}

	else return SUCCESS;
}

int fill_Queen(int** board, Point position,int board_size) {

	if (fillRowAndCol(board, position,board_size) == FAILURE)
		return FAILURE;
	if (fill_diagonal_DownardLeft(board, position,board_size) == FAILURE)
		return FAILURE;
	if (fill_diagonal_UpwardLeft(board, position,board_size) == FAILURE)
		return FAILURE;
	if (fill_diagonal_DownardRight(board, position,board_size) == FAILURE)
		return FAILURE;
	if (fill_diagonal_UpwardRight(board, position,board_size) == FAILURE)
		return FAILURE;

	return SUCCESS;
}

int fill_Rook(int** board, Point position,int board_size) {
	if (fillRowAndCol(board, position,board_size) == FAILURE)
		return FAILURE;

	return SUCCESS;
}

int fill_Bishop(int** board, Point position,int board_size) {

	if (fill_diagonal_DownardLeft(board, position, board_size) == FAILURE)
		return FAILURE;
	if (fill_diagonal_UpwardLeft(board, position, board_size ) == FAILURE)
		return FAILURE;
	if (fill_diagonal_DownardRight(board, position, board_size ) == FAILURE)
		return FAILURE;
	if (fill_diagonal_UpwardRight(board, position, board_size ) == FAILURE)
		return FAILURE;

	return SUCCESS;
}

int fill_Knight(int** board, Point position, int board_size) {
	if (fill_L(board, position, board_size) == FAILURE)
		return FAILURE;

	return SUCCESS;
}