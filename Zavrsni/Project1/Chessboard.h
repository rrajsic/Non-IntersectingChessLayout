#ifndef CHESSBOARD_H
#define CHESSBOARD_H

extern int g_board_size;
class Chessboard
{
private:
	int** m_board;

public:
	Chessboard(int** board) {
		m_board = board;
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
	static bool equals(Chessboard* testBoard, std::vector<Chessboard*> boards) {
		bool board_equals = false;
		for (auto board : boards) {
			bool field_equals = true;
			for (int i = 0; i < g_board_size; i++) {
				for (int j = 0; j < g_board_size; j++) {
					if (testBoard->getBoard()[i][j] != board->getBoard()[i][j]){
						field_equals = false;
						}
				}
			}
			if (field_equals)board_equals = true;
		}
		return board_equals;
	}

	~Chessboard() {
		for (int i = 0; i < g_board_size; i++)
			delete m_board[i];
		delete m_board;
	}
};

#endif
