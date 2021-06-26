#include "BoardFunctions.h"
#include <iostream>
#include <stdlib.h>

std::string createBoard(int board_size) {
	
	std::string board_fileName = "";

	switch (board_size) {
		case 3:
			board_fileName = "board-3x3.png";
			break;
		case 4:
			board_fileName = "board-4x4.png";
			break;
		case 5:
			board_fileName = "board-5x5.png";
			break;
		case 6:
			board_fileName = "board-6x6.png";
			break;
		case 7:
			board_fileName = "board-7x7.png";
			break;
		case 8:
			board_fileName = "board-8x8.png";
			break;
		default:
			std::cout << "Wrong board size. Error\n";
			system("pause");
			exit(EXIT_FAILURE);
	}

	return board_fileName;
}