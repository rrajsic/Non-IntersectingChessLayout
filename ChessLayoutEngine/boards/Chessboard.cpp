#include <cassert> 
#include "Chessboard.h"

//Overloaded operators

Chessboard& Chessboard::operator=(Chessboard&& chessboard) noexcept {
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

int& Chessboard::operator()(int row, int col) {
	assert(col >= 0 && col < g_board_size);
	assert(row >= 0 && row < g_board_size);

	return m_board[row][col];
}

//Needed operations

void Chessboard::allocateBoard() {
	m_board = new int* [g_board_size];
	for (int i = 0; i < g_board_size; i++)
		m_board[i] = new int[g_board_size];
}

void Chessboard::initializeBoard() {
	for (int i = 0; i < g_board_size; i++) {
		for (int j = 0; j < g_board_size; j++) {
			m_board[i][j] = 0;
		}
	}
}

bool Chessboard::equals(const Chessboard& board) {
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

int Chessboard::countOccupied() {
	int counter(0);
	for (int i = 0; i < g_board_size; i++) {
		for (int j = 0; j < g_board_size; j++) {
			if (m_board[i][j] != 0)counter++;
		}
	}
	return counter;
}