#ifndef BOARD_H
#define BOARD_H


#include <vector>
#include <stack>
#include "Piece.h"
#include "Constants.h"
#include <algorithm>
#include <random>
#include<set>
#include <unordered_set>
#include "Chessboard.h"
#include <sstream>

class Board
{
public:
	std::vector<Chessboard*> m_boards;
	std::vector<IPiece*>m_pieces;
	std::vector<std::vector<IPiece*>> m_all_pieces_permutations;
	int m_board_size;

public:
	Board(int board_size) {
		m_board_size = board_size;
	}


	void pushPiece(IPiece* piece) {
		m_pieces.push_back(piece);
	}


	void calculateAllCombinations() {

		int** board;
		board = new int* [m_board_size];
		for (int i = 0; i < m_board_size; i++)
			board[i] = new int[m_board_size];
		initializeBoard(board);
		while (!m_all_pieces_permutations.empty()) {
			std::vector<IPiece*> temp_pieces = deepCopyVector(m_all_pieces_permutations.back());
			printPieces(temp_pieces);
			tryAllCombinations(board, temp_pieces, 0, temp_pieces.size() - 1);
			m_all_pieces_permutations.pop_back();
		}

		/*while(!m_all_pieces_permutations.empty()){
				bool isSuccess = false;
				int** board;
				board = new int* [m_board_size];
				for (int i = 0; i < m_board_size; i++)
					board[i] = new int[m_board_size];
				initializeBoard(board);
		
				int piece_counter = 0;
				for (int i = 0; i < m_board_size; i++) {
					for (int j = 0; j < m_board_size; j++) {
						for (int piece_index = 0; piece_index < m_all_pieces_permutations.back().size(); piece_index++) {
							piece_counter = 0;

							if (board[i][j] == 0)
							{
								int** temp_board = deepCopyBoard(board);

								if (m_all_pieces_permutations.back()[piece_index]->placePiece(i, j, board) == SUCCESS) {
									piece_counter++;
									std::cout << "Put " << piece_counter << "\n";
								}


								else board = deepCopyBoard(temp_board);

								deleteBoard(temp_board);
							}

						
					}
				}
					if (piece_counter == m_all_pieces_permutations.back().size())isSuccess = true;
					if (isSuccess) {
						if (!isBoardAllZero(board))
							if (!doesSameBoardExist(new Chessboard(board, m_board_size)))m_boards.push_back(new Chessboard(deepCopyBoard(board), m_board_size));
						std::cout << "Success board:\n";
					}	
				}
				m_all_pieces_permutations.pop_back();
				deleteBoard(board);
		}*/
	}

	void calculateShuffleCombinations() {
		int** board;
		board = new int* [m_board_size];
		for (int i = 0; i < m_board_size; i++)
			board[i] = new int[m_board_size];
		initializeBoard(board);

		while (!m_all_pieces_permutations.empty()) {
			std::vector<IPiece*> temp_pieces = deepCopyVector(m_all_pieces_permutations.back());
			saveFirstPossibleCombination(board, temp_pieces);
			printPieces(temp_pieces);
			m_all_pieces_permutations.pop_back();
		}

	}

	void tryAllCombinations(int** board, std::vector<IPiece*> pieces,int piece_index,int max_piece_index) {
		if (pieces.empty())return;

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
							if (!doesSameBoardExist(new Chessboard(temp_board, m_board_size)))m_boards.push_back(new Chessboard(deepCopyBoard(temp_board), m_board_size));
							temp_board = deepCopyBoard(board);
						}
						else {
							tryAllCombinations(temp_board, pieces, piece_index+1, max_piece_index);
							temp_board = deepCopyBoard(board);
						}
				}
			}
		}
		deleteBoard(temp_board);
		}
		
	void saveFirstPossibleCombination(int** board, std::vector<IPiece*> pieces) {
		
		int** temp_board;
		temp_board = new int* [m_board_size];
		for (int i = 0; i < m_board_size; i++)
			temp_board[i] = new int[m_board_size];
		temp_board = deepCopyBoard(board);


		for (int i = 0; i < m_board_size; i++) {
			for (int j = 0; j < m_board_size; j++) {
				if (temp_board[i][j] == 0) {
					if (pieces.back()->placePiece(i, j, temp_board) == SUCCESS) {
						pieces.pop_back();
						if (pieces.empty()) {
							if (!doesSameBoardExist(new Chessboard(temp_board, m_board_size)))m_boards.push_back(new Chessboard(deepCopyBoard(temp_board), m_board_size));
							printBoard(temp_board);
							return;
						}
						else {
							saveFirstPossibleCombination(temp_board, pieces);
						}
					}
				}
				}
			}
		deleteBoard(temp_board);
	}
	
	void setVectors() {
		for (int k = 0; k < permutationWithoutRepetiton(m_pieces.size()); k++) {
			std::next_permutation(m_pieces.begin(), m_pieces.end());
			if (!doesVectorExist(m_pieces))
				m_all_pieces_permutations.push_back(deepCopyVector(m_pieces));
		}
	}
	void printVectors() {
		for (auto i : m_all_pieces_permutations) {
			printPieces(i);
			std::cout << ".....................\n";
		}
	}
	void printPieces() {

		for (int i = 0; i < m_pieces.size(); i++) {
			switch (m_pieces[i]->getType()) {
			case Type::KING:
				std::cout << "King";
				break;
			case Type::QUEEN:
				std::cout << "Queen";
				break;
			case Type::ROOK:
				std::cout << "Rook";
				break;
			case Type::BISHOP:
				std::cout << "Bishop";
				break;
			case Type::KNIGHT:
				std::cout << "Knight";
				break;
			default:
				std::cout << "Unknown piece";
			}
			std::cout << std::endl;
		}
	}

	void printPieces(std::vector<IPiece*> pieces) {

		for (int i = 0; i < pieces.size(); i++) {
			switch (pieces[i]->getType()) {
			case Type::KING:
				std::cout << "King";
				break;
			case Type::QUEEN:
				std::cout << "Queen";
				break;
			case Type::ROOK:
				std::cout << "Rook";
				break;
			case Type::BISHOP:
				std::cout << "Bishop";
				break;
			case Type::KNIGHT:
				std::cout << "Knight";
				break;
			default:
				std::cout << "Unknown piece";
			}
			std::cout << std::endl;
		}
	}



	void printBoards() {
		for (auto i : m_boards) {
			std::cout << "--------\n";
			printBoard(i->m_board);
			std::cout << "--------\n";
		}
	}
	void printBoard(int** board) {
		for (int i = 0; i < m_board_size; i++) {
			for (int j = 0; j < m_board_size; j++) {
				std::cout << board[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}

	int** deepCopyBoard(int** board) {
		int** temp = nullptr;
		temp = new int* [m_board_size];
		for (int i = 0; i < m_board_size; i++) {
			temp[i] = new int[m_board_size];
		}

		for (int i = 0; i < m_board_size; i++) {
			for (int j = 0; j < m_board_size; j++) {
				temp[i][j] = board[i][j];
			}
		}
		return temp;
	}

	std::vector<IPiece*> deepCopyVector(std::vector<IPiece*> pieces) {
		std::vector<IPiece*> temp;
		for (auto i : pieces) {
			switch (i->getType()) {
			case Type::KING:
				temp.push_back(new King(m_board_size));
				break;
			case Type::QUEEN:
				temp.push_back(new Queen(m_board_size));
				break;
			case Type::ROOK:
				temp.push_back(new Rook(m_board_size));
				break;
			case Type::BISHOP:
				temp.push_back(new Bishop(m_board_size));
				break;
			case Type::KNIGHT:
				temp.push_back(new Knight(m_board_size));
				break;
			default:
				std::cout << "Error" << std::endl;
				exit(EXIT_FAILURE);
			}
		}
		return temp;
	}
	std::vector<IPiece*> deepCopyVector() {
		std::vector<IPiece*> temp;
		for (auto i : m_pieces) {
			switch (i->getType()) {
			case Type::KING:
				temp.push_back(new King(m_board_size));
				break;
			case Type::QUEEN:
				temp.push_back(new Queen(m_board_size));
				break;
			case Type::ROOK:
				temp.push_back(new Rook(m_board_size));
				break;
			case Type::BISHOP:
				temp.push_back(new Bishop(m_board_size));
				break;
			case Type::KNIGHT:
				temp.push_back(new Knight(m_board_size));
				break;
			default:
				std::cout << "Error" << std::endl;
				exit(EXIT_FAILURE);
			}
		}
		return temp;
	}

	void deleteBoard(int** temp) {
		for (int i = 0; i < m_board_size; i++) {
			delete temp[i];
		}
		delete temp;
	}

	int fact(int n) {

		int res = 1;
		for (int i = 1; i <= n; i++) {
			res *= i;
		}
		return res;
	}

	void initializeBoard(int** board) {
		for (int i = 0; i < m_board_size; i++) {
			for (int j = 0; j < m_board_size; j++) {
				board[i][j] = 0;
			}
		}
	}

	bool doesVectorExist(std::vector<IPiece*> v) {
		for (auto i : m_all_pieces_permutations)
		{
			if (areVectorsSame(i, v))return true;
		}
		return false;
	}
	bool areVectorsSame(std::vector<IPiece*> v1, std::vector<IPiece*> v2) {
		for (int i = 0; i < v1.size(); i++) {
			if (v1[i]->getType() != v2[i]->getType())return false;
		}
		return true;
	}
	std::vector<IPiece*> shuffleVector(std::vector<IPiece*>& v) {
		if (v.empty())return v;
		auto rng = std::default_random_engine{};
		std::shuffle(std::begin(v), std::end(v), rng);
		return v;
	}

	bool isBoardAllZero(int** board) {
		bool notZero = false;
		for (int i = 0; i < m_board_size; i++) {
			for (int j = 0; j < m_board_size; j++) {
				if (board[i][j] > 0)notZero = true;
			}
		}
		return !notZero;
	}

	bool doesExistSameVector(std::vector<IPiece*>temp) {
		for (int i = 0; i < m_all_pieces_permutations.size(); i++) {
			if (areVectorsSame(m_all_pieces_permutations[i], temp)) {
				return true;

			}
		}
		return false;
	}

	int permutationWithoutRepetiton(int n) {
		int res = 1;

		res = fact(n) / (fact(n - 5));				//5 is the number of possible pieces

		return res;
	}
	

	bool areBoardsSame(int** b1, int** b2) {
		bool isSame = true;
		for (int i = 0; i < m_board_size; i++) {
			for (int j = 0; j < m_board_size; j++) {
				if (b1[i][j] != b2[i][j])
					isSame = false;
			}
		}
		return isSame;
	}
	bool doesSameBoardExist(Chessboard* board)
	{
		for (auto i : m_boards) {
			if ((*board).equals((*i))) 
				return true;
			Chessboard* tempBoard90 = new Chessboard(rotateBoard90Degrees(board->m_board), m_board_size);
			if ((*tempBoard90).equals((*i))){
				delete tempBoard90;
				return true;
			}
			Chessboard* tempBoard180 = new Chessboard(rotateBoard90Degrees(tempBoard90->m_board), m_board_size);

			if ((*tempBoard180).equals((*i))) {
				delete tempBoard90;
				delete tempBoard180;
				return true;
			}
			Chessboard* tempBoard270 = new Chessboard(rotateBoard90Degrees(tempBoard180->m_board), m_board_size);
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

	std::string convertBoardToString(int** board) {
		std::string board_string;
		std::ostringstream os;
		for (int i = 0; i < m_board_size; i++) {
			for (int j = 0; j < m_board_size; j++) {
				os << board[i][j];
			}
		}
		std::string str(os.str());
		std::cout << str;
		return str;
	}
	std::string spacedString(std::string str) {
		std::string spacedString;
		for (auto i : str) {
			spacedString += i;
			spacedString += " ";
		}
		return spacedString;
	}
	int ** rotateBoard90Degrees(int** board) {
		int** tempBoard;
		tempBoard = new int* [m_board_size];
		for (int i = 0; i < m_board_size; i++)
			tempBoard[i] = new int[m_board_size];

		for (int i = 0; i < m_board_size; i++) {
			for (int j = 0; j < m_board_size; j++) {
				tempBoard[i][j] = board[m_board_size-1 - j][i];
			}
		}
		return tempBoard;
	}

};
#endif