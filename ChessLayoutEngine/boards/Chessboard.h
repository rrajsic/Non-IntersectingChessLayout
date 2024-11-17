#pragma once

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
	
	//Overloaded operators
	Chessboard& operator=(const Chessboard& chessboard) = delete;
	Chessboard& operator=(Chessboard&& chessboard) noexcept;
	int& operator()(int row, int col);

	//Setter and getter
	void set(int row, int col, int value) { m_board[row][col] = value; }
	int** getBoard() const { return m_board; }

	//Needed operations
	bool equals(const Chessboard& board);
	void allocateBoard();
	void initializeBoard();
	int countOccupied();

	~Chessboard() {
		for (int i = 0; i < g_board_size; i++)
			delete m_board[i];
		delete m_board;
	}
};