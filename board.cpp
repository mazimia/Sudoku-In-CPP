#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <random>
#include "board.h"

using namespace sudoku;
namespace sudoku {

    sudokuBoard::sudokuBoard() : numbers(nullptr), numbersSize(9) {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                for (int k = 0; k < 9; ++k) {
                    possibleNum[i][j][k] = true;
                }
            }
        }
    }

    sudokuBoard::~sudokuBoard() {
        emptyNumbers();
    }

    void sudokuBoard::emptyNumbers() {
        if (numbers != nullptr) {
            delete[] numbers;
            numbers = nullptr;
        }
        numbersSize = 0;
    }

    void sudokuBoard::createNumbers(int row, int column) {
        int counter = 0;
        emptyNumbers();
        // generate numbers array
        numbersSize = countNumbers(row, column);
        numbers = new int[numbersSize];
        // loop through possible numbers and fill numbers array
        for (int i = 0; i < 9; i++) {
            if(possibleNum[row][column][i]) {
                numbers[counter] = i + 1;
                counter++;
            }
        }
    }

    int sudokuBoard::countNumbers(int row, int column) const {
        int counter = 0;
        for (int i = 0; i < 9; i++) {
            if(possibleNum[row][column][i]) {
                counter++;
            }
        }
        return counter;
    }

    void sudokuBoard::shuffler() {
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

    void sudokuBoard::generate() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                setCell(i, j, true);
                //update(i, j, board[i][j], false);
                //displayDebug();
            }
        }
    }

    void sudokuBoard::setCell(int row, int column, bool set) {
        // forward track mode
        if (set) {
            createNumbers(row, column);
            if (numbersSize > 0) {
                if (numbersSize != 1) {
                    shuffler();
                }

                board[row][column] = numbers[0];
                displayDebug(row, column, 1);
                update(row, column, board[row][column], !set);
            } else {
                setCell(row, column - 1, false);
                displayDebug(row, column, 2);
            }
        }

        // backtrack mode
        else {
            update(row, column, board[row][column], !set);
            board[row][column] = 0;
            displayDebug(row, column, 3);
            setCell(row, column, !set);
        }
    }

    void sudokuBoard::update(int row, int column, int value, bool set) {
        updateColumn(row, column, value, set);
        updateRow(row, column, value, set);
        updateSquare(row, column, value, set);
    }
    
    void sudokuBoard::updateColumn(int row, int column, int value, bool set) {
        for (int i = 0; i < 9; i++) {
            possibleNum[i][column][value - 1] = set;
        }
    }

    void sudokuBoard::updateRow(int row, int column, int value, bool set) {
        for (int i = 0; i < 9; i++) {
            possibleNum[row][i][value - 1] = set;
        }
    }

    void sudokuBoard::updateSquare(int row, int column, int value, bool set) {
        int startRow = (row/3) * 3;
        int startColumn = (column/3) * 3;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                possibleNum[startRow + i][startColumn + j][value - 1] = set;
            }
        }
    }

    int sudokuBoard::locateSquare(int row, int column) {
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

    ///////////////////////
    // Display Functions //
    ///////////////////////

    std::ostream& sudokuBoard::displayHeader(std::ostream& os) const {
        // Print top border
        os << "∥===|===|===∥===|===|===∥===|===|===∥" << std::endl;
        return os;
    }

    std::ostream& sudokuBoard::displayCell(std::ostream& os, int value) const {
        // Print board element or empty space if the value is 0
        if (value == 0) os << " ";
        else os << value;
        return os;
    }

    std::ostream& sudokuBoard::displaySeparator(std::ostream& os, int j) const {
        // Print vertical border after each cell
        if ((j + 1) % 3 == 0 && j != 8) os << " ∥ ";
        else if (j != 8) os << " | ";
        return os;
    }

    std::ostream& sudokuBoard::displayHorizontalSeparator(std::ostream& os, int i) const {
        // Print horizontal border after every 3rd row
        if ((i + 1) % 3 == 0 && i != 8) {
            os << "∥---|---|---∥---|---|---∥---|---|---∥" << std::endl;
        }
        return os;
    }

    std::ostream& sudokuBoard::displayFooter(std::ostream& os) const {
        // Print bottom border
        os << "∥===|===|===∥===|===|===∥===|===|===∥\n\n" << std::endl;
        return os;
    }

    std::ostream& sudokuBoard::display(std::ostream& os) const {
        displayHeader(os);

        // Iterate over each row
        for (int i = 0; i < 9; ++i) {
            // Print vertical border for the left side of the grid
            os << "∥ ";

            // Iterate over each column
            for (int j = 0; j < 9; ++j) {
                displayCell(os, board[i][j]);
                displaySeparator(os, j);
            }

            // Print vertical border for the right side of the grid
            os << " ∥";
            os << std::endl;

            // Print horizontal border after every 3rd row
            displayHorizontalSeparator(os, i);
        }

        displayFooter(os);

        // Return the ostream object
        return os;
    }

    void sudokuBoard::displayDebug(int row, int column, int state) const {
        switch (state) {
            case 1:
                std::cout << row << "," << column << " Set Successfully" << std::endl;
                break;
            case 2:
                std::cout << row << "," << column << " Backtracking started" << std::endl;
                break;
            case 3:
                std::cout << row << "," << column << " Reset state" << std::endl;
                break;
            default:
                break;
        }
        // Print top border
        std::cout << "    1   2   3   4   5   6   7   8   9" << std::endl;
        std::cout << "  ∥===|===|===∥===|===|===∥===|===|===∥" << std::endl;

        // Iterate over each row
        for (int i = 0; i < 9; ++i) {
            // Print vertical border for the left side of the grid
            std::cout << i + 1 << " ∥ ";

            // Iterate over each column
            for (int j = 0; j < 9; ++j) {
                // Print board element or empty space if the value is 0
                if (board[i][j] == 0) {
                    std::cout << " ";
                } else {
                    std::cout << board[i][j];
                }

                // Print vertical border after each cell
                if ((j+1) % 3 == 0 && j != 8) std::cout << " ∥ ";
                else if (j != 8) std::cout << " | ";
            }

            // Print vertical border for the right side of the grid
            std::cout << " ∥";
            std::cout << std::endl;

            // Print horizontal border after every 3rd row
            if ((i + 1) % 3 == 0 && i != 8) {
                std::cout << "  ∥---|---|---∥---|---|---∥---|---|---∥" << std::endl;
            }

        }

        // Print bottom border
        std::cout << "  ∥===|===|===∥===|===|===∥===|===|===∥" << std::endl;
        std::cout << "    1   2   3   4   5   6   7   8   9\n" << std::endl;

        if (row != -1) {
            for (int i = 0; i < 9; i++) {
                std::cout << i + 1 << ": " << possibleNum[row][column][i] << "\n";
            }
            std::cout << "===========================================\n\n\n" << std::endl;
        }
    }

}


