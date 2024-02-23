#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "board.h"

using namespace sudoku;

int main() {
    sudokuBoard A;
    A.display();
    A.generate();
    return 0;
}
