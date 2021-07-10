#include <vector>
#include <algorithm>
#include "Pieces.h"
#include "EnumFunctions.h"
#include "EnumBoard.h"
#include "EnumCombinations.h"
#include "Chessboard.h"
#include "Engine.h"


/////////////////////////////Main engine functions////////////////////////////////////////////////

bool Engine::calculatePossibleLayouts(const Functions function) {
	bool isSuccess = false;
	
	int counter(1);
	int num_of_permutations = m_pieces_all_permutations.size();
	while (!m_pieces_all_permutations.empty()) {
		int** board = allocateBoard();
		initializeBoard(board);
		std::vector<Piece*> temp_pieces = deepCopyVector(m_pieces_all_permutations.back());
		std::cout << "Calculating permutations: " << counter << "/" << num_of_permutations << "\n";
		switch (function) {
		case Functions::DISPLAY_ALL_COMBINATIONS:
			if (saveLayouts(board, temp_pieces, 0, temp_pieces.size(),Combinations::EVERY))isSuccess = true;
			break;
		case Functions::DISPLAY_FIRST_COMBINATION_OF_EVERY_PERMUTATION: 
			if (saveLayouts(board, temp_pieces, 0, temp_pieces.size(),Combinations::FIRST))isSuccess = true;
			break;
		case Functions::DISPLAY_FIRST_POSSIBLE_COMBINATION: 
			if (saveLayouts(board, temp_pieces, 0, temp_pieces.size(), Combinations::FIRST))return true;
			break;
		default:
			return -2;
		}	
		m_pieces_all_permutations.pop_back();
		
		counter++;
		deleteBoard(board);
	}
	return isSuccess;
}

bool Engine::saveLayouts(int** board, std::vector<Piece*> pieces, int piece_index, int piece_count,Combinations combinations) {
	bool isSuccess = false;
	int** temp_board = allocateBoard();
	initializeBoard(temp_board);
	temp_board = copyBoard(board);

	for (int i = 0; i < g_board_size; i++) {
		for (int j = 0; j < g_board_size; j++) {
			if (temp_board[i][j] == 0) {
				if (pieces[piece_index]->placePiece(i, j, temp_board) == SUCCESS) {
					if (piece_index == (piece_count-1)) {
						Chessboard* success_board = new Chessboard(temp_board);
						if (!doesEqualRotatedBoardExist(std::move(success_board)))
							m_boards.emplace_back(std::move(success_board));

						isSuccess = true;
						if (combinations == Combinations::FIRST) {
							deleteBoard(temp_board);
							return isSuccess;
						}
					}
					else {
						if (saveLayouts(temp_board, pieces, piece_index + 1, piece_count, combinations)) {
							isSuccess = true;
							if (combinations == Combinations::FIRST) {
								deleteBoard(temp_board);
								return isSuccess;
							}
						}
						else {
							saveLayouts(temp_board, pieces, piece_index, piece_count,combinations);
						}
						temp_board = copyBoard(board);
					}
				}
				temp_board = copyBoard(board);
			}
		}
	}

	deleteBoard(temp_board);
	return isSuccess;
}

////////////////////////////Vector Functions/////////////////////////////////////////////////

void Engine::pushPiece(Piece* piece) {
	m_pieces.push_back(piece);
}

void Engine::setPiecesPermutations() {
	std::cout << "Permuting..." << std::endl;
	int counter(0);
	std::sort(m_pieces.begin(), m_pieces.end(),[](Piece*& p1, Piece*& p2) {
		return p1->getType() < p2->getType();
		});
	do {
		if (!doesVectorExist(m_pieces))
			m_pieces_all_permutations.push_back(deepCopyVector(m_pieces));
		counter++;
	} while (std::next_permutation(begin(m_pieces), end(m_pieces), [](Piece *&p1,Piece* &p2) {
		return p1->getType() < p2->getType();
		}));
}

std::vector<Piece*> Engine::deepCopyVector(std::vector<Piece*> pieces) {
	std::vector<Piece*> temp;
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

bool Engine::doesVectorExist(std::vector<Piece*> v) {
	for (auto i : m_pieces_all_permutations)
	{
		if (areVectorsEqual(i, v))return true;
	}
	return false;
}

bool Engine::areVectorsEqual(std::vector<Piece*> v1, std::vector<Piece*> v2) {
	for (int i = 0; i < v1.size(); i++) {
		if (v1[i]->getType() != v2[i]->getType())return false;
	}
	return true;
}

///////////////////////////////Rotating board functions///////////////////////////////////////

bool Engine::doesEqualRotatedBoardExist(Chessboard* board) {

	for (auto temp : m_boards) {
		if ((*board).equals((*temp)))
			return true;

		auto rotated_tempBoard = std::make_shared<Chessboard>(copyBoard(temp->getBoard()));
		auto reflected_tempBoard = std::make_shared<Chessboard>(copyBoard(temp->getBoard()));

		for (int i = 0; i < 4; i++) {

			rotated_tempBoard = std::make_shared<Chessboard>(rotateBoard90Degrees(rotated_tempBoard->getBoard()));
			reflected_tempBoard = std::make_shared<Chessboard>(reflectBoardVerticaly(rotated_tempBoard->getBoard()));

			if ((*board).equals((*rotated_tempBoard))) {
				return true;
			}

			if ((*board).equals((*reflected_tempBoard))) {
				return true;
			}
		}
	}
	return false;
}


int** Engine::rotateBoard90Degrees(int** board) {
	int** tempBoard = allocateBoard();

	for (int i = 0; i < g_board_size; i++) {
		for (int j = 0; j < g_board_size; j++) {
			tempBoard[i][j] = board[g_board_size - 1 - j][i];
		}
	}
	return tempBoard;
}

int** Engine::reflectBoardVerticaly(int** board) {
	int** tempBoard = allocateBoard();
	
	for (int i = 0; i < g_board_size; i++) {
		for (int j = 0; j < g_board_size; j++) {
			tempBoard[i][j] = board[i][g_board_size - 1 - j];
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

int Engine::countOccupied(int** board) {
	int counter(0);
	for (int i = 0; i < g_board_size; i++) {
		for (int j = 0; j < g_board_size; j++) {
			if (board[i][j] != 0)counter++;
		}
	}
	return counter;
}

void Engine::deleteBoard(int** board) {
	for (int i = 0; i < g_board_size; i++) {
		delete board[i];
	}
	delete board;
}

