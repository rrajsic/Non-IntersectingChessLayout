#ifndef BOARD_H
#define BOARD_H
#include "Chessboard.h"
#include "Piece.h"

extern int g_board_size;

class Engine
{
private:
	std::vector<Chessboard*> m_boards;
	std::vector<Piece*>m_pieces;
	std::vector<std::vector<Piece*>> m_pieces_all_permutations;

public:
	Engine() {}

	//Getters 
	std::vector<Chessboard*> getBoards() { return m_boards; }
	
	//Main engine functions
	bool calculateAllCombinations();
	bool tryAllCombinations(int** board, std::vector<Piece*> pieces, int piece_index, int max_piece_index);
	bool calculateShuffleCombinations();
	bool saveFirstPossibleCombination(int** board, std::vector<Piece*> pieces);
	
	//Vector Functions
	void pushPiece(Piece* piece);
	void setVectors();
	std::vector<Piece*> deepCopyVector(std::vector<Piece*> pieces);
	bool doesVectorExist(std::vector<Piece*> v);
	bool areVectorsEqual(std::vector<Piece*> v1, std::vector<Piece*> v2);

	//Rotating board functions
	bool doesEqualRotatedBoardExist(Chessboard* board);
	int** rotateBoard90Degrees(int** board);

	//2D array functions
	int** allocateBoard();
	void initializeBoard(int** board);
	int** copyBoard(int** board);
	int countOccupied(int** board);
	void deleteBoard(int** board);
	
};

#endif