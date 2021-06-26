#include<iostream>
#include<string>

int main()
{
	std::string board[64] = { "5", "4", "3", "2", "1", "3", "4", "5",
								"6", "6", "6", "6", "6", "6", "6", "6",
								"0", "0", "0", "0", "0", "0", "0", "0",
								"0", "0", "0", "0", "0", "0", "0", "0",
								"0", "0", "0", "0", "0", "0", "0", "0",
								"0", "0", "0", "0", "0", "0", "0", "0",
								"6", "6", "6", "6", "6", "6", "6", "6",
								"5", "4", "3", "2", "1", "3", "4", "5" };

	std::string fileWithParams = "testcpp.cpp";
	for (int i = 0; i < 64; i++) {
		fileWithParams += " " + board[i];
	}

	system(fileWithParams.c_str());
	/*
	system("testcpp.cpp " + board[0] + board[1] + board[2] + board[3] + board[4] + board[5] + board[6] + board[7] + board[8] + board[9] +
		board[10] + board[11] + board[12] + board[13] + board[14] + board[15] + board[16] + board[17] + board[18] + board[19] +
		board[20] + board[21] + board[22] + board[23] + board[24] + board[25] + board[26] + board[27] + board[28] + board[29] +
		board[30] + board[31] + board[32] + board[33] + board[34] + board[35] + board[36] + board[37] + board[38] + board[39] +
		board[40] + board[41] + board[42] + board[43] + board[44] + board[45] + board[46] + board[47] + board[48] + board[49] +
		board[50] + board[51] + board[52] + board[53] + board[54] + board[55] + board[56] + board[57] + board[58] + board[59] +
		board[60] + board[61] + board[62] + board[63]);*/
	return 0;
}