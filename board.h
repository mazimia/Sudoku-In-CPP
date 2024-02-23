#define _CRT_SECURE_NO_WARNINGS
#ifndef BOARD_H_
#define BOARD_H_
#define NUM {1, 2, 3, 4, 5, 6, 7, 8, 9}
#include <iostream>

namespace sudoku {
	class sudokuBoard {
		int board[9][9] {};
		int* numbers;
		int numbersSize;
		int numBase[9] NUM;
		bool possibleNum[9][9][9] = {{{true}}};

        /////////////////////////
        // Number Manipulation //
        /////////////////////////

		/// Goes through possibleNum and creates a list of possible numbers for that cell
		void createNumbers(int row, int column);
		/// Empties numbers 
		void emptyNumbers();
		/// Counts how many numbers are available in cell
		int countNumbers(int row, int column) const;
		/// Shuffles all the available numbers
		void shuffler();

        ////////////////////////
        // Board Manipulation //
        ////////////////////////

		/// Sets a cell
		void setCell(int row, int column, bool set);

		/// Update board state
		void update(int row, int column, int value, bool set);
		/// Updates the columns in possibleNum
		void updateColumn(int row, int column, int value, bool set);
		/// Updates the remaining rows in possibleNum
		void updateRow(int row, int column, int value, bool set);
		/// Updates the 3x3 square 
		void updateSquare(int row, int column, int value, bool set);
		
		/// Returns the square index based on column and row
		int locateSquare(int row, int column);

        ///////////////////////
        // Display Functions //
        ///////////////////////

        std::ostream& displayHeader(std::ostream& os) const;
        std::ostream& displayCell(std::ostream& os, int value) const;
        std::ostream& displaySeparator(std::ostream& os, int j) const;
        std::ostream& displayHorizontalSeparator(std::ostream& os, int i) const;
        std::ostream& displayFooter(std::ostream& os) const;

	public:
		sudokuBoard();
		~sudokuBoard();
		/// Display function to print the grid and return the ostream object
        std::ostream& display(std::ostream& os = std::cout) const;
        /// Debug display
        void displayDebug(int row = -1, int column = -1, int state = 0) const;
    	/// Generate a new board
    	void generate();
		
	};
}

#endif
