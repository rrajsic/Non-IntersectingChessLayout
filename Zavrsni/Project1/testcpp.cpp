//#include<cstdlib>
//#include <iostream>
//#include <string>
//
//int main(int argc, char* argv[])
//{
//
//	int* x = new int[argc];
//	for (int i = 1; i < argc; i++) {
//		x[i] = atoi(argv[i+1]);
//	}
//
//	int board[8][8];
//	int board_size = x[0];
//	int k = 1;
//	int num_of_boards_recieved = (argc - 1) / 64;
//	for (int j = 0; j < num_of_boards_recieved; j++) {
//		for (int i = 0; i < 8; i++) {
//			for (int j = 0; j < 8; j++) {
//				board[i][j] = x[k];
//				++k;
//			}
//		}
//		for (int i = 0; i < 8; i++) {
//			for (int j = 0; j < 8; j++) {
//				std::cout << board[i][j] << " ";
//			}
//			std::cout << std::endl;
//		}
//		std::cout << "\n";
//	}
//	
//	delete x;
//	system("pause");
//	return 0;
//}