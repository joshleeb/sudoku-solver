#include <iostream>

#include "interface.h"
#include "puzzle.h"

int main() {
    auto initial_board = interface::read_board(std::cin);
    puzzle sudoku_puzzle(initial_board);

    if (!sudoku_puzzle.is_valid()) {
        std::cout << "invalid board\n";
        return EXIT_SUCCESS;
    }

    sudoku_puzzle.display();
    sudoku_puzzle.solve();
    sudoku_puzzle.display();

    return EXIT_SUCCESS;
}
