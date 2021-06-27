#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include "BoardFunctions.h"
#include "Board.h"
#include "Constants.h"
#include "ChessboardMenu.h"

/////////////////1:28

using namespace sf;

int size = 106;



/*
int boardd[board_size_g][board_size_g] =
{
	-5,-4,-3,-2,-1,-3,-4,-5,
	-6,-6,-6,-6,-6,-6,-6,-6,
	 0, 0, 0, 0, 0, 0, 0, 0,
	 0, 0, 0, 0, 0, 0, 0, 0,
	 0, 0, 0, 0, 0, 0, 0, 0,
	 0, 0, 0, 0, 0, 0, 0, 0,
	 6, 6, 6, 6, 6, 6, 6, 6,
	 5, 4, 3, 2, 1, 3, 4, 5
};
*/


void loadPosition(int **board, Sprite** f,int board_number,int board_size) {
	int k = 0;
	for (int i = 0; i < board_size; i++) {
		for (int j = 0; j < board_size; j++) {
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

int numberOfPieces(int** board,int board_size) {
	int counter(0);
	for (int i = 0; i < board_size; i++) {
		for (int j = 0; j < board_size; j++) {
			if (board[i][j] != 0)counter++;
		}
	}
	return counter;
}

int main() {

	startMenu();

	//const int chess_square_size = 106;
	//int board_number = 0;

	//std::cout << "Enter board size: ";
	//int board_size(0);
	//std::cin >> board_size;
	//std::cout << "Enter number of Queens: ";
	//int num_queens(0);
	//std::cin >> num_queens;
	//std::cout << "Enter number of Kings: ";
	//int num_kings(0);
	//std::cin >> num_kings;
	//std::cout << "Enter number of Rooks: ";
	//int num_rooks(0);
	//std::cin >> num_rooks;
	//std::cout << "Enter number of Bishops: ";
	//int num_bishops(0);
	//std::cin >> num_bishops;
	//std::cout << "Enter number of Knights: ";
	//int num_knights(0);
	//std::cin >> num_knights;

	//Board board = Board(board_size);

	//std::vector<IPiece*>pieces;

	//for (int i = 0; i < num_queens; i++) {
	//	board.pushPiece(new Queen(board_size));
	//}
	//for (int i = 0; i < num_kings; i++) {
	//	board.pushPiece(new King(board_size));
	//}
	//for (int i = 0; i < num_rooks; i++) {
	//	board.pushPiece(new Rook(board_size));
	//}
	//for (int i = 0; i < num_bishops; i++) {
	//	board.pushPiece(new Bishop(board_size));
	//}
	//for (int i = 0; i < num_knights; i++) {
	//	board.pushPiece(new Knight(board_size));
	//}

	//board.setVectors();

	//board.calculateShuffleCombinations();


	//int number_of_boards = board.m_boards.size();


	//RenderWindow window(VideoMode(board_size * chess_square_size, board_size * chess_square_size), "Chess");

	//Texture t1, t2;

	//t1.loadFromFile("figures_wip4.png");

	//t2.loadFromFile(createBoard(board_size));

	//Sprite s(t1);
	//Sprite sBoard(t2);

	//int** chessboard = new int* [board_size];
	//chessboard = board.m_boards.back()->m_board;

	//int counter{ 0 };
	//for (int i = 0; i < board.m_boards.size(); i++)counter++;

	//std::cout << "NUMBER OF COMBINATIONS: " << counter << "\n";
	//
	//int *number_of_pieces_per_board = new int[number_of_boards];
	//for (int i = 0; i < number_of_boards; i++) {
	//	number_of_pieces_per_board[i] = numberOfPieces(board.m_boards[i]->m_board,board_size);
	//}

	//
	//Sprite** f = new Sprite*[number_of_boards];
	//for (int i = 0; i < number_of_boards; i++) {
	//	f[i] = new Sprite[number_of_pieces_per_board[i]];
	//}
	//
	//for (int i = 0; i < number_of_boards; i++) {
	//	for (int j = 0; j < number_of_pieces_per_board[i]; j++) {
	//		f[i][j].setTexture(t1);
	//	}
	//}
	//
	//for (int k = 0; k < number_of_boards; k++) {
	//	loadPosition(board.m_boards[k]->m_board, f, k,board_size);
	//}
	//
	//
	//bool isMove = false;
	//float dx = 0, dy = 0;
	//int n = 0;

	//while (window.isOpen())
	//{
	//	Vector2i pos = Mouse::getPosition(window);

	//	Event e;
	//	while (window.pollEvent(e))
	//	{
	//		if (e.type == Event::Closed)
	//			window.close();

	//		/////////drag AND DROP///////////////

	//		if (e.type == Event::MouseButtonPressed) {
	//			if (e.key.code == Mouse::Left) {
	//				for (int i = 0; i < number_of_pieces_per_board[board_number]; i++)
	//					if (f[board_number][i].getGlobalBounds().contains(pos.x, pos.y)) {
	//						isMove = true;
	//						n = i;
	//						dx = pos.x - f[board_number][i].getPosition().x;
	//						dy = pos.y - f[board_number][i].getPosition().y;
	//					}
	//			}
	//		}

	//		if (e.type == Event::MouseButtonReleased) {
	//			if (e.key.code == Mouse::Left) {
	//				isMove = false;
	//				Vector2f p = f[board_number][n].getPosition() + Vector2f(size / 2, size / 2);
	//				Vector2f newPos = Vector2f(size * int(p.x / size), size * int(p.y / size));
	//				f[board_number][n].setPosition(newPos);
	//			}
	//		}

	//		if (e.type == Event::KeyPressed) {
	//			if (e.key.code == Keyboard::Space) {
	//				if(board_number < number_of_boards-1)board_number++;
	//			}
	//			if (e.key.code == Keyboard::BackSpace) {
	//				if(board_number>0)board_number--;
	//			}
	//		}

	//	}

	//	//dx i dy se stavljaju (delte) zato sto ako se ne stavi razlika onda ce pozicija
	//	//spritea se postaviti na poectak kursora (lijevi vrh spritea uvijek)
	//	if (isMove) f[board_number][n].setPosition(pos.x - dx, pos.y - dy);

	//	////////DRAW///////////////////////
	//	window.clear();
	//	window.draw(sBoard);
	//	for (int i = 0; i < number_of_pieces_per_board[board_number]; i++)window.draw(f[board_number][i]);

	//	window.display();
	//	
	//}
	//
	//for (int i = 0; i < board_size; i++) {
	//	delete chessboard[i];
	//}
	//delete chessboard;
}