#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <random>
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
                numbers[counter] = i + 1;
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

    sudokuBoard::void shuffler() {
        std::random_device rd;
        std::mt19937 gen(rd());

        for (int i = numbersSize - 1; i > 0; --i) {
            std::uniform_int_distribution<> dis(0, i);
            int randomIndex = dis(gen);

            int temp = numbers[i];
            numbers[i] = numbers[randomIndex];
            numbers[randomIndex] = temp;
        }
    }

    sudokuBoard::void generate() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                setCell(i, j, true);
                update(i, j, board[i][j], false);
                displayDebug();
            }
        }
    }

    sudokuBoard::void setCell(int row, int column, bool set) {
        createNumbers(row, column);
        shuffler();
        board[row][column] = numbers[0];
    }

    /*
    sudokuBoard::bool canCol(int column, int value) {
        return possibleNum[0][column][value - 1];
    }

    sudokuBoard::bool canRow(int row, int value) {
        return possibleNum[row][0][value - 1];
    }

    sudokuBoard::bool canSquare(int row, int column, int value) {
        return possibleNum[row][column][value - 1];
    }
    */

    sudokuBoard::void update(int row, int column, int value, bool set) {
        updateColumn(row, column, value, set);
        updateRow(row, column, value, set);
        updateSquare(row, column, value, set);
    }
    
    sudokuBoard::void updateColumn(int row, int column, int value, bool set) {
        for (int i = 0; i < 9; i++) {
            possibleNum[i][column][value - 1] = set;
        }
    }

    sudokuBoard::void updateRow(int row, int column, int value, bool set) {
        for (int i = 0; i < 9; i++) {
            possibleNum[row][i][value - 1] = set;
        }
    }

    sudokuBoard::void updateSquare(int row, int column, int value, bool set) {
        int startRow = (row/3) * 3;
        int startColumn = (column/3) * 3;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                possibleNum[startRow + i][startColumn + j][value - 1] = set;
            }
        }
    }

    sudokuBoard::int locateSquare(int row, int column) {
        /// square-row 1
        if (row < 3) {
            /// square-column 1
            if (column < 3) return 1;
            /// square-column 2
            else if (column >= 3 && column < 6) return 2;
            /// square-column 3
            else return 3;
        }
        /// square-row 2
        else if (row >= 3 && row < 6) {
            /// square-column 1
            if (column < 3) return 4;
            /// square-column 2
            else if (column >= 3 && column < 6) return 5;
            /// square-column 3
            else return 6;
        }
        /// square-row 3
        else {
            /// square-column 1
            if (column < 3) return 7;
            /// square-column 2
            else if (column >= 3 && column < 6) return 8;
            /// square-column 3
            else return 9;
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

