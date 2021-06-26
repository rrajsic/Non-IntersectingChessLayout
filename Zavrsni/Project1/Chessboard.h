#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include"Constants.h"
#include<iostream>
class Chessboard
{
public:
	int** m_board;
	int m_board_size;
	Chessboard(int** board,int board_size) {
		m_board = board;
		m_board_size = board_size;
	}

	/*friend bool operator== (const Chessboard& b1, const Chessboard& b2)
	{
		bool areSame = true;
		for (int i = 0; i < m_board_size; i++) {
			for (int j = 0; j < m_board_size; j++) {
				if (b1.m_board[i][j] != b2.m_board[i][j]) {
					areSame = false;
				}
			}
		}
		return areSame;
	}
	friend bool operator!= (const Chessboard& b1, const Chessboard& b2)
	{
		return !(b1 == b2);
	}
	*/
	bool equals(const Chessboard& board) {
		bool areSame = true;
		for (int i = 0; i < m_board_size; i++) {
			for (int j = 0; j < m_board_size; j++) {
				if (m_board[i][j] != board.m_board[i][j]) {
					areSame = false;
				}
			}
		}
		return areSame;
	}

	~Chessboard() {
		for (int i = 0; i < m_board_size; i++)
			delete m_board[i];
		delete m_board;
	}
};

#endif
