#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <cassert> 
extern int g_board_size;
class Chessboard
{
private:
	int** m_board;

public:
	Chessboard() {
		allocateBoard();
		initializeBoard();
	}

	Chessboard(const Chessboard& chessboard) {
		allocateBoard();

		if (chessboard.m_board) {
			for (int i = 0; i < g_board_size; i++)
				for (int j = 0; j < g_board_size; j++) {
					m_board[i][j] = chessboard.m_board[i][j];
				}
		}
	}
	
	Chessboard& operator=(const Chessboard& chessboard) = delete;

	Chessboard& operator=(Chessboard&& chessboard) noexcept{
		if (&chessboard == this) 
			return *this;
		
		for (int i = 0; i < g_board_size; i++)
			delete[] m_board[i];
		delete m_board;

		allocateBoard();
		for (int i = 0; i < g_board_size; i++)
			for (int j = 0; j < g_board_size; j++) {
				m_board[i][j] = chessboard.m_board[i][j];
			}

		return *this;
	}

	int& operator()(int row, int col) {
		assert(col >= 0 && col < g_board_size);
		assert(row >= 0 && row < g_board_size);

		return m_board[row][col];
	}

	void set(int row, int col, int value) {
		m_board[row][col] = value;
	}

	int** getBoard() const { return m_board; }

	bool equals(const Chessboard& board) {
		bool equals = true;
		for (int i = 0; i < g_board_size; i++) {
			for (int j = 0; j < g_board_size; j++) {
				if (m_board[i][j] != board.getBoard()[i][j]) {
					equals = false;
				}
			}
		}
		return equals;
	}
	
	void allocateBoard() {
		
		m_board = new int* [g_board_size];
		for (int i = 0; i < g_board_size; i++)
			m_board[i] = new int[g_board_size];
	}


	void initializeBoard() {
		for (int i = 0; i < g_board_size; i++) {
			for (int j = 0; j < g_board_size; j++) {
				m_board[i][j] = 0;
			}
		}
	}

	int countOccupied() {
		int counter(0);
		for (int i = 0; i < g_board_size; i++) {
			for (int j = 0; j < g_board_size; j++) {
				if (m_board[i][j] != 0)counter++;
			}
		}
		return counter;
	}
	~Chessboard() {
		for (int i = 0; i < g_board_size; i++)
			delete m_board[i];
		delete m_board;
	}
};

#endif
