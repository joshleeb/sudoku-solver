#include <iostream>

#include "interface.h"
#include "puzzle.h"

int main() {
    auto initial_board = interface::read_board(std::cin);
    puzzle sudoku_puzzle(initial_board);

    sudoku_puzzle.display();

    return EXIT_SUCCESS;
}
