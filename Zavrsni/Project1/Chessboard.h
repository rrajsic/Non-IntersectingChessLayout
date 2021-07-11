#ifndef CHESSBOARD_H
#define CHESSBOARD_H

extern int g_board_size;
class Chessboard
{
private:
	int** m_board;

public:
	Chessboard(int** board) {
		allocateBoard();
		copyBoard(board);
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
	void copyBoard(int** board) {
		for (int i = 0; i < g_board_size; i++) {
			for (int j = 0; j < g_board_size; j++) {
				m_board[i][j] = board[i][j];
			}
		}
	}
	void allocateBoard() {
		
		m_board = new int* [g_board_size];
		for (int i = 0; i < g_board_size; i++)
			m_board[i] = new int[g_board_size];
	}


	void initializeBoard(int** board) {
		for (int i = 0; i < g_board_size; i++) {
			for (int j = 0; j < g_board_size; j++) {
				board[i][j] = 0;
			}
		}
	}
	~Chessboard() {
		for (int i = 0; i < g_board_size; i++)
			delete m_board[i];
		delete m_board;
	}
};

#endif
