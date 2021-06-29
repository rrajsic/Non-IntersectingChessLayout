#ifndef BOARD_H
#define BOARD_H

#include "Chessboard.h"
#include "IPiece.h"

class Engine
{
private:
	std::vector<Chessboard*> m_boards;
	std::vector<IPiece*>m_pieces;
	std::vector<std::vector<IPiece*>> m_pieces_all_permutations;
	int m_board_size;
	

public:
	Engine(int board_size) { m_board_size = board_size;	}

	//Getters 
	std::vector<Chessboard*> getBoards() { return m_boards; }
	
	//Main engine functions
	bool calculateAllCombinations();
	bool calculateShuffleCombinations();
	bool tryAllCombinations(int** board, std::vector<IPiece*> pieces, int piece_index, int max_piece_index);	
	bool saveFirstPossibleCombination(int** board, std::vector<IPiece*> pieces);
	
	//Vector Functions
	void pushPiece(IPiece* piece);
	void setVectors();
	std::vector<IPiece*> deepCopyVector(std::vector<IPiece*> pieces);
	bool doesVectorExist(std::vector<IPiece*> v);
	bool areVectorsEqual(std::vector<IPiece*> v1, std::vector<IPiece*> v2);

	//Rotating board functions
	bool doesEqualRotatedBoardExist(Chessboard* board);
	int** rotateBoard90Degrees(int** board);

	//2D array functions
	int** allocateBoard();
	void initializeBoard(int** board);
	int** copyBoard(int** board);
	void deleteBoard(int** board);
};

#endif