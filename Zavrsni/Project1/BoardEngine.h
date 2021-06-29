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

class BoardEngine
{
public:
	std::vector<Chessboard*> m_boards;
	std::vector<IPiece*>m_pieces;
	std::vector<std::vector<IPiece*>> m_pieces_all_permutations;
	int m_board_size;
	

public:
	BoardEngine(int board_size) {
		m_board_size = board_size;	
	}


	void pushPiece(IPiece* piece) {
		m_pieces.push_back(piece);
	}


	bool calculateAllCombinations() {
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
			if(tryAllCombinations(board, temp_pieces, 0, temp_pieces.size() - 1))isSuccess=true;
			m_pieces_all_permutations.pop_back();
			counter++;
		}
		return isSuccess;
	}

	bool calculateShuffleCombinations() {
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
			if(saveFirstPossibleCombination(board, temp_pieces))isSuccess=true;
			m_pieces_all_permutations.pop_back();
			counter++;
		}
		return isSuccess;
	}

	bool tryAllCombinations(int** board, std::vector<IPiece*> pieces,int piece_index,int max_piece_index) {
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
							tryAllCombinations(temp_board, pieces, piece_index+1, max_piece_index);
							temp_board = deepCopyBoard(board);
						}
				}
			}
		}
		deleteBoard(temp_board);
		return isSuccess;
	}
		
	bool saveFirstPossibleCombination(int** board, std::vector<IPiece*> pieces) {
		bool isSuccess = false;

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
								if (!doesEqualRotatedBoardExist(new Chessboard(temp_board, m_board_size)))
									m_boards.push_back(new Chessboard(deepCopyBoard(temp_board), m_board_size));
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
	
	void setVectors() {
		std::cout << "Permuting...\n";
		for (int k = 0; k < permutationWithoutRepetiton(m_pieces.size()); k++) {
			std::next_permutation(m_pieces.begin(), m_pieces.end());
			if (!doesVectorExist(m_pieces))
				m_pieces_all_permutations.push_back(deepCopyVector(m_pieces));
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
		for (auto i : m_pieces_all_permutations)
		{
			if (areVectorsEqual(i, v))return true;
		}
		return false;
	}
	bool areVectorsEqual(std::vector<IPiece*> v1, std::vector<IPiece*> v2) {
		for (int i = 0; i < v1.size(); i++) {
			if (v1[i]->getType() != v2[i]->getType())return false;
		}
		return true;
	}

	int permutationWithoutRepetiton(int n) {
		int res = 1;

		res = fact(n) / (fact(n - 5));				//5 is the number of possible pieces

		return res;
	}

	bool doesEqualRotatedBoardExist(Chessboard* board)
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