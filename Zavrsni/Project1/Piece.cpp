#include "Point2D.h"
#include "Piece.h"
int Piece::fillRowAndCol(int** board) {

	for (int i = 0; i < m_board_size; i++)
	{
		for (int j = 0; j < m_board_size; j++)
		{
			if (i == m_position.getRow())
			{
				if (board[i][j] > 1)return FAILURE;
				board[i][j] = 1;
			}											//all rows are now taken
			if (j == m_position.getCol())
			{
				if (board[i][j] > 1)return FAILURE;			//all columns are now taken
				board[i][j] = 1;
			}
		}
	}

	return SUCCESS;
}

int Piece::fill_diagonal_DownardRight(int** board)
{
	int x = m_position.getRow();
	int y = m_position.getCol();

	for (int i = x; i < m_board_size; i++)			//Fills diagonal: Right - down
	{
		int j = y;
		if (i + 1 >= m_board_size)break;
		if (j + 1 >= m_board_size)break;
		if (board[i + 1][j + 1] > 1)return FAILURE;		//if there is a figure there (king, queen, etc..) 
		board[i + 1][j + 1] = 1;
		y++;
	}

	return SUCCESS;
}

int Piece::fill_diagonal_DownardLeft(int** board)
{
	int x = m_position.getRow();
	int y = m_position.getCol();

	for (int i = x; i < m_board_size; i++)			//Fills diagonal: Left - down
	{
		int j = y;
		if (i + 1 >= m_board_size)break;
		if (j - 1 < 0)break;
		if (board[i + 1][j - 1] > 1)return FAILURE;		//if there is a figure there (king, queen, etc..)
		board[i + 1][j - 1] = 1;
		y--;
	}
	return SUCCESS;
}

int Piece::fill_diagonal_UpwardRight(int** board)
{
	int x = m_position.getRow();
	int y = m_position.getCol();

	for (int i = x; i >= 0; i--)					//Fills diagonal: Right - up
	{
		int j = y;
		if (i - 1 < 0)break;
		if (j + 1 >= m_board_size)break;
		if (board[i - 1][j + 1] > 1)return FAILURE;			//if there is a figure there (king, queen, etc..)
		board[i - 1][j + 1] = 1;
		y++;
	}
	return SUCCESS;
}

int Piece::fill_diagonal_UpwardLeft(int** board)
{
	int x = m_position.getRow();
	int y = m_position.getCol();

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

int Piece::fill_OneSpotAround(int** board)
{
	int x = m_position.getRow();
	int y = m_position.getCol();

	//we set all 8 spots to 1 seperately
	if (x + 1 < m_board_size)
	{
		if (board[x + 1][y] < 2)
			board[x + 1][y] = 1;

		else return FAILURE;

		if (y + 1 < m_board_size)
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
	if (y + 1 < m_board_size)
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

		if (x + 1 < m_board_size)
		{
			if (board[x + 1][y - 1] < 2)
				board[x + 1][y - 1] = 1;
			else return FAILURE;
		}
	}
	return SUCCESS;
}

int Piece::fill_L(int** board)									//this is a knight, but K is busy
{
	int x = m_position.getRow();
	int y = m_position.getCol();
	//we set all 8 spots to 1 seperately
	if ((x + 1 < m_board_size) && (y + 2 < m_board_size))
	{
		if (board[x + 1][y + 2] < 2)							//if there isn't a figure place 1 
			board[x + 1][y + 2] = 1;
		else return FAILURE;
	}
	if ((x + 1 < m_board_size) && (y - 2 >= 0))
	{
		if (board[x + 1][y - 2] < 2)							//if there isn't a figure place 1 
			board[x + 1][y - 2] = 1;
		else return FAILURE;
	}

	if ((x - 1 >= 0) && (y + 2 < m_board_size))
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
	if ((x + 2 < m_board_size) && (y + 1 < m_board_size))
	{
		if (board[x + 2][y + 1] < 2)							//if there isn't a figure place 1 
			board[x + 2][y + 1] = 1;
		else return FAILURE;
	}
	if ((x + 2 < m_board_size) && (y - 1 >= 0))
	{
		if (board[x + 2][y - 1] < 2)							//if there isn't a figure place 1 
			board[x + 2][y - 1] = 1;
		else return FAILURE;
	}

	if ((x - 2 >= 0) && (y + 1 < m_board_size))
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
