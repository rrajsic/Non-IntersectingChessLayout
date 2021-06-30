#include <vector>
#include <algorithm>
#include <unordered_set>
#include "Piece.h"
#include "Chessboard.h"
#include "MathFunctions.h"
#include "Engine.h"


/////////////////////////////Main engine functions////////////////////////////////////////////////

bool Engine::calculateAllCombinations() {
	bool isSuccess = false;
	int** board = allocateBoard();
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
	int** temp_board = allocateBoard();
	temp_board = copyBoard(board);

	for (int i = 0; i < g_board_size; i++) {
		for (int j = 0; j < g_board_size; j++) {
			if (temp_board[i][j] == 0) {
				if (pieces[piece_index]->placePiece(i, j, temp_board) == SUCCESS)
					if (piece_index == max_piece_index) {
						if (!doesEqualRotatedBoardExist(new Chessboard(temp_board, g_board_size)))
							m_boards.push_back(new Chessboard(copyBoard(temp_board), g_board_size));
						temp_board = copyBoard(board);
						isSuccess = true;
					}
					else {
						if(tryAllCombinations(temp_board, pieces, piece_index + 1, max_piece_index))
							isSuccess=true;
						temp_board = copyBoard(board);
					}
			}
		}
	}
	deleteBoard(temp_board);
	return isSuccess;
}

bool Engine::calculateShuffleCombinations() {
	bool isSuccess = false;
	int** board = allocateBoard();
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

bool Engine::saveFirstPossibleCombination(int** board, std::vector<IPiece*> pieces) {
	bool isSuccess = false;

	int** temp_board = allocateBoard();
	temp_board = copyBoard(board);

	for (int i = 0; i < g_board_size; i++) {
		for (int j = 0; j < g_board_size; j++) {
			if (temp_board[i][j] == 0) {
				if (pieces.back()->placePiece(i, j, temp_board) == SUCCESS) {
					pieces.pop_back();
					if (pieces.empty()) {
						if (!doesEqualRotatedBoardExist(new Chessboard(temp_board, g_board_size)))
							m_boards.push_back(new Chessboard(copyBoard(temp_board), g_board_size));
						return true;
					}
					else {
						saveFirstPossibleCombination(temp_board, pieces);
					}
				}
			}
		}
	}
	deleteBoard(temp_board);
	return false;
}

////////////////////////////Vector Functions/////////////////////////////////////////////////

void Engine::pushPiece(IPiece* piece) {
	m_pieces.push_back(piece);
}

void Engine::setVectors() {
	
	/*
	std::vector<Type> types;
	for (auto i : m_pieces) {
		types.push_back(i->getType());
	}
	int counter(0);
	do {
			counter++;
	} while (std::next_permutation(types.begin(), types.end(), [](IPiece* p1, IPiece* p2) {
		return p1->getType() == p2->getType();
		}));
		*/
	int counter(0);
	std::sort(m_pieces.begin(), m_pieces.end(),[](IPiece*& p1, IPiece*& p2) {
		return p1->getType() <= p2->getType();
		});
	do {
		counter++;
		if (!doesVectorExist(m_pieces))
			m_pieces_all_permutations.push_back(deepCopyVector(m_pieces));
	} while (std::next_permutation(begin(m_pieces), end(m_pieces), [](IPiece *&p1,IPiece* &p2) {
		return p1->getType() < p2->getType();
		}));

	for (auto i : m_pieces_all_permutations) {
		for (auto j : i) {
			std::cout << j->getType() << std::endl;
		}
		std::cout << std::endl;
	}

	std::cout << "COUNTER: " << counter << "\n";
}

std::vector<IPiece*> Engine::deepCopyVector(std::vector<IPiece*> pieces) {
	std::vector<IPiece*> temp;
	for (auto i : pieces) {
		switch (i->getType()) {
		case Type::KING:
			temp.push_back(new King());
			break;
		case Type::QUEEN:
			temp.push_back(new Queen());
			break;
		case Type::ROOK:
			temp.push_back(new Rook());
			break;
		case Type::BISHOP:
			temp.push_back(new Bishop());
			break;
		case Type::KNIGHT:
			temp.push_back(new Knight());
			break;
		default:
			std::cout << "Error" << std::endl;
			exit(EXIT_FAILURE);
		}
	}
	return temp;
}

bool Engine::doesVectorExist(std::vector<IPiece*> v) {
	for (auto i : m_pieces_all_permutations)
	{
		if (areVectorsEqual(i, v))return true;
	}
	return false;
}

bool Engine::areVectorsEqual(std::vector<IPiece*> v1, std::vector<IPiece*> v2) {
	for (int i = 0; i < v1.size(); i++) {
		if (v1[i]->getType() != v2[i]->getType())return false;
	}
	return true;
}

///////////////////////////////Rotating board functions///////////////////////////////////////
bool Engine::doesEqualRotatedBoardExist(Chessboard* board)
{
	for (auto i : m_boards) {
		if ((*board).equals((*i)))
			return true;
		Chessboard* tempBoard90 = new Chessboard(rotateBoard90Degrees(board->getBoard()), g_board_size);
		if ((*tempBoard90).equals((*i))) {
			delete tempBoard90;
			return true;
		}
		Chessboard* tempBoard180 = new Chessboard(rotateBoard90Degrees(tempBoard90->getBoard()), g_board_size);

		if ((*tempBoard180).equals((*i))) {
			delete tempBoard90;
			delete tempBoard180;
			return true;
		}
		Chessboard* tempBoard270 = new Chessboard(rotateBoard90Degrees(tempBoard180->getBoard()), g_board_size);
		if ((*tempBoard270).equals((*i))) {
			delete tempBoard90;
			delete tempBoard180;
			delete tempBoard270;
			return true;
		}
		delete tempBoard90;
		delete tempBoard180;
		delete tempBoard270;
	}
	return false;
}

int** Engine::rotateBoard90Degrees(int** board) {
	int** tempBoard;
	tempBoard = new int* [g_board_size];
	for (int i = 0; i < g_board_size; i++)
		tempBoard[i] = new int[g_board_size];

	for (int i = 0; i < g_board_size; i++) {
		for (int j = 0; j < g_board_size; j++) {
			tempBoard[i][j] = board[g_board_size - 1 - j][i];
		}
	}
	return tempBoard;
}

/////////////////////////////////////2D Array functions//////////////////////////////////////

int** Engine::allocateBoard() {
	int** board;
	board = new int* [g_board_size];
	for (int i = 0; i < g_board_size; i++)
		board[i] = new int[g_board_size];

	return board;
}


void Engine::initializeBoard(int** board) {
	for (int i = 0; i < g_board_size; i++) {
		for (int j = 0; j < g_board_size; j++) {
			board[i][j] = 0;
		}
	}
}

int** Engine::copyBoard(int** board) {
	int** temp = allocateBoard();

	for (int i = 0; i < g_board_size; i++) {
		for (int j = 0; j < g_board_size; j++) {
			temp[i][j] = board[i][j];
		}
	}
	return temp;
}

void Engine::deleteBoard(int** board) {
	for (int i = 0; i < g_board_size; i++) {
		delete board[i];
	}
	delete board;
}

