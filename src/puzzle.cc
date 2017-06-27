#include "puzzle.h"

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

#include <boost/algorithm/cxx11/any_of.hpp>

puzzle::puzzle(std::vector<int> board) {
    this->board = board;
    this->fixed_squares = {};

    this->board_width = std::sqrt(board.size());

    // Set fixed squares.
    for (int i = 0; i < (int)board.size(); i++) {
        if (board[i] == BLANK) this->fixed_squares.push_back(i);
    }
}

void puzzle::solve() {}

void puzzle::display() {
    int square;

    for (int row = 0; row < this->board_width; row++) {
        for (int col = 0; col < this->board_width; col++) {
            square = this->board[row * this->board_width + col];

            if (square == BLANK) {
                std::cout << ".";
            } else {
                std::cout << square;
            }
            std::cout << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

bool puzzle::is_valid() {
    return false;
}

bool puzzle::is_solved() {
    return false;
}

std::vector<int> puzzle::get_board() {
    return this->board;
}

int puzzle::get_board_width() {
    return this->board_width;
}

bool puzzle::is_fixed_square(int index) {
    return boost::algorithm::any_of_equal(this->fixed_squares, index);
}

std::vector<int> puzzle::get_moves(int index) {
    (void)index;
    return {};
}
