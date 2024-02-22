#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "board.h"

namespace sudoku {
    sudokuBoard::sudokuBoard() : numbers(nullptr), numbersSize(9) {
    }

    sudokuBoard::~sudokuBoard() {
        emptyNumbers();
    }

    sudokuBoard::emptyNumbers() {
        if (numbers != nullptr) {
            delete[] numbers;
        }
        numbersSize = 0;
    }

    sudokuBoard::createNumbers(int row, int column) {
        int counter = 0;
        emptyNumbers();
        // generate numbers array
        numbersSize = countNumbers();
        numbers = new int[numbersSize];
        // loop through possible numbers and fill numbers array
        for (int i = 0; i < 9; i++) {
            if(possibleNum[row][column][i]) {
                numbers[counter] = possibleNum[row][column][i];
                counter++;
            }
        }
    }

    sudokuBoard::int countNumbers(int row, int column) const {
        int counter = 0;
        for (int i = 0; i < 9; i++) {
            if(possibleNum[row][column][i]) {
                counter++;
            }
        }
        return counter;
    }

    sudokuBoard::void generate() {
        for (int i = 0; i < 9; i++) {
            1
        }
    }
    
    sudokuBoard::std::ostream& displayDebug(std::ostream& os = std::cout) const {
        // Print top border
        os << "||===|===|===||===|===|===||===|===|===||" << std::endl;

        // Iterate over each row
        for (int i = 0; i < 9; ++i) {
            // Print vertical border for the left side of the grid
            os << "|| ";

            // Iterate over each column
            for (int j = 0; j < 9; ++j) {
                // Print board element or empty space if the value is 0
                if (board[i][j] == 0) {
                    os << " ";
                } else {
                    os << board[i][j];
                }
                
                // Print vertical border after each cell
                os << " | ";
            }

            // Print vertical border for the right side of the grid
            os << "|";
            if ((i + 1) % 3 == 0 && i != 8) {
                os << "|";
            }
            os << std::endl;

            // Print horizontal border after every 3rd row
            if ((i + 1) % 3 == 0 && i != 8) {
                os << "||---|---|---||---|---|---||---|---|---||" << std::endl;
            }
        }

        // Print bottom border
        os << "||===|===|===||===|===|===||===|===|===||" << std::endl;

        // Return the ostream object
        return os;
    }
}

