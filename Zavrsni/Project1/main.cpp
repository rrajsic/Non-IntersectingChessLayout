#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <chrono>
#include "BoardImageFactory.h"
#include "Pieces.h"
#include "EnumFunctions.h"
#include "EnumCombinations.h"
#include "Engine.h"

using namespace sf;

int size = 106;
int g_board_size;

void loadPosition(int** board, Sprite** f, int board_number);

int main(int argc, char* argv[]) {

	int* x = new int[argc];
	for (int i = 1; i < argc; i++) 
		x[i] = atoi(argv[i]);
	

	const int functionCall = x[1];
	const Functions function = static_cast<Functions>(x[1]);
	g_board_size = x[2];
	const int queen_count = x[3];
	const int king_count = x[4];
	const int rook_count = x[5];
	const int bishop_count = x[6];
	const int knight_count = x[7];
	
	delete[] x;

	int board_number = 0;
	
	Engine bEngine = Engine();

	for (int i = 0; i < queen_count; i++) 
		bEngine.pushPiece(new Queen());
	
	for (int i = 0; i < king_count; i++) 
		bEngine.pushPiece(new King());
	
	for (int i = 0; i < rook_count; i++) 
		bEngine.pushPiece(new Rook());
	
	for (int i = 0; i < bishop_count; i++) 
		bEngine.pushPiece(new Bishop());
	
	for (int i = 0; i < knight_count; i++) 
		bEngine.pushPiece(new Knight());
	

	bEngine.setPiecesPermutations();

	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	if (bEngine.calculatePossibleLayouts(function) == false) 
		return FAILURE;
	
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	std::cout << "Calculation took " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << " seconds." << std::endl;
	

	RenderWindow window(VideoMode(g_board_size * size, g_board_size * size), "Chessboard Layout");

	Texture piecesTexture, boardTexture;

	piecesTexture.loadFromFile("images/pieces/chess_pieces.png");
	boardTexture.loadFromFile(BoardImageFactory::createBoard());

	Sprite sAllPieces(piecesTexture);
	Sprite sBoard(boardTexture);

	int board_count = bEngine.getBoards().size();

	std::cout << "Number of layouts: " << board_count << "\n\n";
	std::cout << "Press space to see next combination" << "\n";
	std::cout << "Press backspace to see previous combination" << "\n\n";
	
	int *pieces_count_per_board = new int[board_count];
	for (int i = 0; i < board_count; i++) 
		pieces_count_per_board[i] = bEngine.getBoards()[i]->countOccupied();
	

	Sprite** pieceSprite = new Sprite*[board_count];
	for (int i = 0; i < board_count; i++) 
		pieceSprite[i] = new Sprite[pieces_count_per_board[i]];
	
	
	for (int i = 0; i < board_count; i++) 
		for (int j = 0; j < pieces_count_per_board[i]; j++) 
			pieceSprite[i][j].setTexture(piecesTexture);
		
	
	
	for (int k = 0; k < board_count; k++) 
		loadPosition(bEngine.getBoards()[k]->getBoard(), pieceSprite, k);
	
	
	while (window.isOpen()) {
		Event e;
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed)
				window.close();

			if (e.type == Event::KeyPressed) {

				if (e.key.code == Keyboard::Space) 
					if(board_number < board_count-1)board_number++;
				
				if (e.key.code == Keyboard::BackSpace) 
					if(board_number>0)board_number--;
				
				if (e.key.code == Keyboard::Enter) 
					return board_count;
			}
		}
		window.clear();
		window.draw(sBoard);
		for (int i = 0; i < pieces_count_per_board[board_number]; i++)
			window.draw(pieceSprite[board_number][i]);

		window.display();
	}
}

void loadPosition(int** board, Sprite** pieceSprite, int board_number) {
	int k = 0;
	for (int i = 0; i < g_board_size; i++)
		for (int j = 0; j < g_board_size; j++) {
			int n = board[i][j];
			if (!n) 
				continue;
			int x = abs(n) - 1;
			int y = n > 0 ? 1 : 0;
			pieceSprite[board_number][k].setTextureRect(IntRect(size * x, size * y, size, size));
			pieceSprite[board_number][k].setPosition(size * j, size * i);
			k++;
		}
}