#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include "BoardImageFactory.h"
#include "Pieces.h"
#include "Engine.h"

using namespace sf;

int size = 106;
int g_board_size;

void loadPosition(int **board, Sprite** f,int board_number) {
	int k = 0;
	for (int i = 0; i < g_board_size; i++) {
		for (int j = 0; j < g_board_size; j++) {
			int n = board[i][j];
			if (!n) continue;
			int x = abs(n) - 1;
			int y = n > 0 ? 1 : 0;
			f[board_number][k].setTextureRect(IntRect(size * x, size * y, size, size));
			f[board_number][k].setPosition(size * j, size * i);
			k++;
		}
	}
}

int main(int argc, char* argv[]) {

	int* x = new int[argc];
	for (int i = 1; i < argc; i++) {
		x[i] = atoi(argv[i]);
	}

	const int functionCall = x[1];
	g_board_size = x[2];
	const int queen_count = x[3];
	const int king_count = x[4];
	const int rook_count = x[5];
	const int bishop_count = x[6];
	const int knight_count = x[7];
	

	const int chess_square_size = 106;
	int board_number = 0;
	
	Engine bEngine = Engine();

	std::vector<Piece*>pieces;

	for (int i = 0; i < queen_count; i++) {
		bEngine.pushPiece(new Queen());
	}
	for (int i = 0; i < king_count; i++) {
		bEngine.pushPiece(new King());
	}
	for (int i = 0; i < rook_count; i++) {
		bEngine.pushPiece(new Rook());
	}
	for (int i = 0; i < bishop_count; i++) {
		bEngine.pushPiece(new Bishop());
	}
	for (int i = 0; i < knight_count; i++) {
		bEngine.pushPiece(new Knight());
	}

	bEngine.setVectors();

	switch (x[1]) {
	case 1:
		if (!bEngine.calculateAllCombinations()) {
			std::cout << "Not possible." << std::endl;
			exit(1);
		}
		break;

	case 2:
		if (!bEngine.calculateFirstCombinationsForEveryPermutation()) {
			std::cout << "Not possible." << std::endl;
			exit(1);
		}
		break;

	case 3: 
		if(!bEngine.calculateFirstCombination()) {
			std::cout << "Not possible." << std::endl;
			exit(1);
		}
		break;
	
		
	default: 
		std::cout << "Error. Wrong function number recieved." << std::endl;
		exit(1);
	}
	
	int number_of_boards = bEngine.getBoards().size();

	RenderWindow window(VideoMode(g_board_size * chess_square_size, g_board_size * chess_square_size), "Chess");

	Texture t1, t2;

	t1.loadFromFile("images/pieces/chess_pieces.png");

	t2.loadFromFile(BoardImageFactory::createBoard());

	Sprite s(t1);
	Sprite sBoard(t2);

	int** chessboard = new int* [g_board_size];
	chessboard = bEngine.getBoards().back()->getBoard();

	int counter{ 0 };
	for (int i = 0; i < bEngine.getBoards().size(); i++)counter++;

	std::cout << "NUMBER OF COMBINATIONS: " << counter << "\n";
	std::cout << "Press space to see next combination" << "\n";
	std::cout << "Press backspace to see previous combination" << "\n";
	
	int *number_of_pieces_per_board = new int[number_of_boards];
	for (int i = 0; i < number_of_boards; i++) {
		number_of_pieces_per_board[i] = bEngine.countOccupied(bEngine.getBoards()[i]->getBoard());
	}

	Sprite** f = new Sprite*[number_of_boards];
	for (int i = 0; i < number_of_boards; i++) {
		f[i] = new Sprite[number_of_pieces_per_board[i]];
	}
	
	for (int i = 0; i < number_of_boards; i++) {
		for (int j = 0; j < number_of_pieces_per_board[i]; j++) {
			f[i][j].setTexture(t1);
		}
	}
	
	for (int k = 0; k < number_of_boards; k++) {
		loadPosition(bEngine.getBoards()[k]->getBoard(), f, k);
	}
	
	float dx = 0, dy = 0;
	int n = 0;

	while (window.isOpen())
	{
		Vector2i pos = Mouse::getPosition(window);

		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();

			if (e.type == Event::KeyPressed) {
				if (e.key.code == Keyboard::Space) {
					if(board_number < number_of_boards-1)board_number++;
				}
				if (e.key.code == Keyboard::BackSpace) {
					if(board_number>0)board_number--;
				}
			}

		}
		////////DRAW///////////////////////
		window.clear();
		window.draw(sBoard);
		for (int i = 0; i < number_of_pieces_per_board[board_number]; i++)window.draw(f[board_number][i]);

		window.display();
		
	}
	
	for (int i = 0; i < g_board_size; i++) {
		delete chessboard[i];
	}
	delete chessboard;
	delete x;
}