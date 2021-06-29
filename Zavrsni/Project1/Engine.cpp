#include <vector>
#include <stack>
#include <sstream>
#include <algorithm>
#include <random>
#include "Piece.h"
#include "Constants.h"
#include <unordered_set>
#include "Chessboard.h"
#include "Engine.h"

void Engine::pushPiece(IPiece* piece) {
	m_pieces.push_back(piece);
}

bool Engine::calculateAllCombinations() {
	bool isSuccess = false;
	int** board;
	board = new int* [m_board_size];
	for (int i = 0; i < m_board_size; i++)
		board[i] = new int[m_board_size];
	initializeBoard(board);
	int counter(1);
	int num_of_permutations = m_pieces_all_permutations.size();
	while (!m_pieces_all_permutations.empty()) {
		std::vector<IPiece*> temp_pieces = deepCopyVector(m_pieces_all_permutations.back());
		std::cout << "Calculating permutations: " << counter << "/" << num_of_permutations << "\n";
		if (tryAllCombinations(board, temp_pieces, 0, temp_pieces.size() - 1))isSuccess = true;
		m_pieces_all_permutations.pop_back();
		counter++;
	}
	return isSuccess;
}
bool Engine::tryAllCombinations(int** board, std::vector<IPiece*> pieces, int piece_index, int max_piece_index) {
	bool isSuccess = false;

	int** temp_board;
	temp_board = new int* [m_board_size];
	for (int i = 0; i < m_board_size; i++)
		temp_board[i] = new int[m_board_size];
	temp_board = deepCopyBoard(board);

	for (int i = 0; i < m_board_size; i++) {
		for (int j = 0; j < m_board_size; j++) {
			if (temp_board[i][j] == 0) {
				if (pieces[piece_index]->placePiece(i, j, temp_board) == SUCCESS)
					if (piece_index == max_piece_index) {
						if (!doesEqualRotatedBoardExist(new Chessboard(temp_board, m_board_size)))
							m_boards.push_back(new Chessboard(deepCopyBoard(temp_board), m_board_size));
						temp_board = deepCopyBoard(board);
						isSuccess = true;
					}
					else {
						tryAllCombinations(temp_board, pieces, piece_index + 1, max_piece_index);
						temp_board = deepCopyBoard(board);
					}
			}
		}
	}
	deleteBoard(temp_board);
	return isSuccess;
}

bool Engine::calculateShuffleCombinations() {
	bool isSuccess = false;
	int** board;
	board = new int* [m_board_size];
	for (int i = 0; i < m_board_size; i++)
		board[i] = new int[m_board_size];
	initializeBoard(board);
	int counter(1);
	int num_of_permutations = m_pieces_all_permutations.size();
	while (!m_pieces_all_permutations.empty()) {

		std::vector<IPiece*> temp_pieces = deepCopyVector(m_pieces_all_permutations.back());
		std::cout << "Calculating permutations: " << counter << "/" << num_of_permutations << "\n";
		if (saveFirstPossibleCombination(board, temp_pieces))isSuccess = true;
		m_pieces_all_permutations.pop_back();
		counter++;
	}
	return isSuccess;
}
