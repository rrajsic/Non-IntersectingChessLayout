#ifndef BOARD_H
#define BOARD_H
#include "Chessboard.h"
#include "Piece.h"

extern int g_board_size;

class Engine
{
private:
	std::vector<Chessboard*> m_boards;
	std::vector<Chessboard*> m_temp_boards;
	std::vector<Piece*>m_pieces;
	std::vector<std::vector<Piece*>> m_pieces_all_permutations;

public:
	Engine() {}

	//Getters 
	std::vector<Chessboard*> getBoards() { return m_boards; }
	
	//Main engine functions
	bool calculatePossibleLayouts(const Functions function);
	bool saveLayouts(Chessboard& board, std::vector<Piece*> pieces, int piece_index, int piece_count, Combinations combinations);
	void filterBoards(const Functions function);
	
	//Vector Functions
	void pushPiece(Piece* piece);
	void setPiecesPermutations();
	bool doesVectorExist(std::vector<Piece*> v);
	bool areVectorsEqual(std::vector<Piece*> v1, std::vector<Piece*> v2);

	//Rotating board functions
	bool doesBoardExist(Chessboard& board);
	bool doesRotatedOrReflectedBoardExist(Chessboard& const board);

	Chessboard rotateBoard90Degrees(Chessboard &board);
	Chessboard reflectBoardVerticaly(Chessboard &board);
	
};

#endif