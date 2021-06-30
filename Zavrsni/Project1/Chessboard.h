#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include<iostream>
class Chessboard
{
private:
	int** m_board;
	int m_board_size;

public:
	Chessboard(int** board,int board_size) {
		m_board = board;
		m_board_size = board_size;
	}

	int** getBoard() { return m_board; }
	bool equals(const Chessboard& board) {
		bool equals = true;
		for (int i = 0; i < m_board_size; i++) {
			for (int j = 0; j < m_board_size; j++) {
				if (m_board[i][j] != board.m_board[i][j]) {
					equals = false;
				}
			}
		}
		return equals;
	}

	~Chessboard() {
		for (int i = 0; i < m_board_size; i++)
			delete m_board[i];
		delete m_board;
	}
};

#endif
