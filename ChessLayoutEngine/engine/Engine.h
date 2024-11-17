#pragma once

#include "../boards/Chessboard.h"
#include "../pieces/Piece.h"

extern int g_board_size;

class Engine
{
private:
	std::vector<Chessboard*> m_fundemental_boards;
	std::vector<Chessboard*> m_distinct_boards;
	std::vector<Chessboard*> m_unfiltered_boards;
	std::vector<Piece*>m_pieces;
	std::vector<std::vector<Piece*>> m_pieces_all_permutations;
	Layouts m_layouts;

public:
	Engine(Layouts layout) : m_layouts(layout) {}

	//Getters 
	std::vector<Chessboard*> getBoards();

	
	//Main engine functions
	bool calculatePossibleLayouts();
	bool saveLayouts(Chessboard& board, std::vector<Piece*> pieces, int piece_index);
	void filterBoards();
	
	//Vector Functions
	void pushPiece(Piece* piece);
	void setPiecesPermutations();
	bool doesVectorExist(std::vector<Piece*> v);
	bool areVectorsEqual(std::vector<Piece*> v1, std::vector<Piece*> v2);

	//Rotating board functions
	bool doesBoardExist(Chessboard& board);
	bool doesRotatedOrReflectedBoardExist(Chessboard& board);

	Chessboard rotateBoard90Degrees(Chessboard &board);
	Chessboard reflectBoardVerticaly(Chessboard &board);
	
};