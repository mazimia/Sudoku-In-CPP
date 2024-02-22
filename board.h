#define _CRT_SECURE_NO_WARNINGS
#ifndef BOARD_H_
#define BOARD_H_
#define NUM {1, 2, 3, 4, 5, 6, 7, 8, 9}
#include <iostream>

namespace sudoku {
	class sudokuBoard {
		int board[9][9] {};
		int* numbers[];
		int numbersSize;
		int numBase[9] NUM;
		bool possibleNum[9][9][9] = {{{true}}};

		/// Goes through possibleNum and creates a list of possible numbers for that cell
		void createNumbers(int row, int column);
		/// Empties numbers 
		void emptyNumbers();
		/// Counts how many numbers are available in cell
		int countNumbers(int row, int column) const;
	public:
		sudokuBoard();
		~sudokuBoard();
		/// Display function to print the grid and return the ostream object
    	std::ostream& displayDebug(std::ostream& os = std::cout) const;
    	/// Generate a new board
    	void generate();
		
	};
}
