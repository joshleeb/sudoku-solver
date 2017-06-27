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

void puzzle::solve() {
}

void puzzle::display() {
    int square;

    for (int row = 0; row < this->board_width; row++) {
        for (int col = 0; col < this->board_width; col++) {
            square = this->board[this->get_index(row, col)];

            if (square == BLANK) {
                std::cout << ".";
            } else {
                std::cout << square;
            }
            std::cout << " ";
        }
        std::cout << "\n";
    }
}

bool puzzle::is_valid() {
    // Only support board of size 4x4, or 9x9.
    if (this->board.size() != 16 && this->board.size() != 81) return false;

    // Check board is a square.
    if (std::pow(this->board_width, 2) != this->board.size()) return false;

    // Check there is no square out of range.
    for (auto const& square : this->board) {
        if (square != BLANK && (square < 1 || square > this->board_width)) {
            return false;
        }
    }

    // We could also check that there is at most one instance of each number in
    // every row, column, and region but to keep things simple I will assume that
    // this is the case.
    return true;
}

bool puzzle::is_solved() {
    std::vector<std::vector<int>> rows(this->board_width);
    std::vector<std::vector<int>> cols(this->board_width);

    std::vector<int> solved(this->board_width);
    std::iota(solved.begin(), solved.end(), 1);

    // Split board into rows and columns.
    for (int row = 0; row < this->board_width; row++) {
        rows[row] = {};
        for (int col = 0; col < this->board_width; col++) {
            rows[row].push_back(this->board[this->get_index(row, col)]);
            cols[col].push_back(this->board[this->get_index(row, col)]);
        }
    }

    // Check rows.
    for (auto& row : rows) {
        std::sort(row.begin(), row.end());
        if (row != solved) return false;
    }

    // Check columns.
    for (auto& col : cols) {
        std::sort(col.begin(), col.end());
        if (col != solved) return false;
    }

    // TODO: Check regions.

    return true;
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

inline int puzzle::get_index(int row, int col) {
    return row * this->board_width + col;
}
