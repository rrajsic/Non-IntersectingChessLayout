#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include "BoardFunctions.h"
#include "BoardEngine.h"
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

void printYeah(){}

int main(int argc, char* argv[]) {

	/*int* x = new int[argc];
	for (int i = 1; i < argc; i++) {
		x[i] = atoi(argv[i]);
	}
	const int functionCall = x[1];
	const int board_size = x[2];
	const int queen_count = x[3];
	const int king_count = x[4];
	const int rook_count = x[5];
	const int bishop_count = x[6];
	const int knight_count = x[7];
	*/

	const int chess_square_size = 106;
	int board_number = 0;

	std::cout << "Enter board size: ";
	int board_size(0);
	std::cin >> board_size;
	std::cout << "Enter number of Queens: ";
	int queen_count(0);
	std::cin >> queen_count;
	std::cout << "Enter number of Kings: ";
	int king_count(0);
	std::cin >> king_count;
	std::cout << "Enter number of Rooks: ";
	int rook_count(0);
	std::cin >> rook_count;
	std::cout << "Enter number of Bishops: ";
	int bishop_count(0);
	std::cin >> bishop_count;
	std::cout << "Enter number of Knights: ";
	int knight_count(0);
	std::cin >> knight_count;



	BoardEngine bEngine = BoardEngine(board_size);

	std::vector<IPiece*>pieces;

	for (int i = 0; i < queen_count; i++) {
		bEngine.pushPiece(new Queen(board_size));
	}
	for (int i = 0; i < king_count; i++) {
		bEngine.pushPiece(new King(board_size));
	}
	for (int i = 0; i < rook_count; i++) {
		bEngine.pushPiece(new Rook(board_size));
	}
	for (int i = 0; i < bishop_count; i++) {
		bEngine.pushPiece(new Bishop(board_size));
	}
	for (int i = 0; i < knight_count; i++) {
		bEngine.pushPiece(new Knight(board_size));
	}

	bEngine.setVectors();



	/*switch (x[1]) {
	case 1:
		bEngine.calculateAllCombinations();
		break;
	case 2: 
		bEngine.calculateShuffleCombinations();
		break;
	default: 
		std::cout << "Error. Wrong function number recieved." << std::endl;
		exit(1);
	}*/
	/*
	if (bEngine.calculateAllCombinations() == false) {
		std::cout << "Not possible." << std::endl;
		system("pause");
		exit(1);
	}
	*/
	
	if (bEngine.calculateShuffleCombinations() == false) {
		std::cout << "Not possible." << std::endl;
		system("pause");
		exit(1);
	}
	int number_of_boards = bEngine.m_boards.size();


	RenderWindow window(VideoMode(board_size * chess_square_size, board_size * chess_square_size), "Chess");

	Texture t1, t2;

	t1.loadFromFile("figures_wip4.png");

	t2.loadFromFile(createBoard(board_size));

	Sprite s(t1);
	Sprite sBoard(t2);

	int** chessboard = new int* [board_size];
	chessboard = bEngine.m_boards.back()->m_board;

	int counter{ 0 };
	for (int i = 0; i < bEngine.m_boards.size(); i++)counter++;

	std::cout << "NUMBER OF COMBINATIONS: " << counter << "\n";
	std::cout << "Press space to see next combination" << "\n";
	std::cout << "Press backspace to see previous combination" << "\n";
	
	int *number_of_pieces_per_board = new int[number_of_boards];
	for (int i = 0; i < number_of_boards; i++) {
		number_of_pieces_per_board[i] = numberOfPieces(bEngine.m_boards[i]->m_board,board_size);
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
		loadPosition(bEngine.m_boards[k]->m_board, f, k,board_size);
	}
	
	
	bool isMove = false;
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

			/////////drag AND DROP///////////////

			if (e.type == Event::MouseButtonPressed) {
				if (e.key.code == Mouse::Left) {
					for (int i = 0; i < number_of_pieces_per_board[board_number]; i++)
						if (f[board_number][i].getGlobalBounds().contains(pos.x, pos.y)) {
							isMove = true;
							n = i;
							dx = pos.x - f[board_number][i].getPosition().x;
							dy = pos.y - f[board_number][i].getPosition().y;
						}
				}
			}

			if (e.type == Event::MouseButtonReleased) {
				if (e.key.code == Mouse::Left) {
					isMove = false;
					Vector2f p = f[board_number][n].getPosition() + Vector2f(size / 2, size / 2);
					Vector2f newPos = Vector2f(size * int(p.x / size), size * int(p.y / size));
					f[board_number][n].setPosition(newPos);
				}
			}

			if (e.type == Event::KeyPressed) {
				if (e.key.code == Keyboard::Space) {
					if(board_number < number_of_boards-1)board_number++;
				}
				if (e.key.code == Keyboard::BackSpace) {
					if(board_number>0)board_number--;
				}
			}

		}

		//dx i dy se stavljaju (delte) zato sto ako se ne stavi razlika onda ce pozicija
		//spritea se postaviti na poectak kursora (lijevi vrh spritea uvijek)
		if (isMove) f[board_number][n].setPosition(pos.x - dx, pos.y - dy);

		////////DRAW///////////////////////
		window.clear();
		window.draw(sBoard);
		for (int i = 0; i < number_of_pieces_per_board[board_number]; i++)window.draw(f[board_number][i]);

		window.display();
		
	}
	
	for (int i = 0; i < board_size; i++) {
		delete chessboard[i];
	}
	delete chessboard;
}