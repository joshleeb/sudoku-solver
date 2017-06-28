#include "puzzle.h"

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>
#include <numeric>

#include <boost/algorithm/cxx11/any_of.hpp>

puzzle::puzzle(std::vector<int> board) {
    this->board = board;
    this->board_width = std::sqrt(board.size());

    this->fixed_squares = {};
    this->attempts = std::vector<std::vector<int>>(board.size());

    // Set fixed squares.
    for (int i = 0; i < (int)board.size(); i++) {
        if (board[i] == BLANK) this->fixed_squares.push_back(i);
    }
}

void puzzle::solve() {
    int index = 0;
    std::vector<int> moves;

    while (!this->is_solved() && index >= 0 && index < std::pow(this->board_width, 2)) {
        if (this->is_fixed_square(index)) {
            index++;
            continue;
        }

        moves = this->get_moves(index);

        // If there are no available moves, backtrack to try a different branch.
        if (moves.empty()) {
            do {
                if (!this->is_fixed_square(index)) {
                    this->board[index] = BLANK;
                    this->attempts[index].clear();
                }
                index--;
            } while (this->is_fixed_square(index));

            continue;
        }

        this->board[index] = moves[0];
        this->attempts[index].push_back(moves[0]);
        index++;
    }
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
    std::cout << "\n";
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

    // We could also check each region is solved but for brevity I will assume
    // that just checking the rows and columns is enough.
    return true;
}

std::vector<int> puzzle::get_board() {
    return this->board;
}

int puzzle::get_board_width() {
    return this->board_width;
}

bool puzzle::is_fixed_square(int index) {
    return !boost::algorithm::any_of_equal(this->fixed_squares, index);
}

std::vector<int> puzzle::get_moves(int index) {
    std::vector<int> seen{};

    int row = this->get_row(index);
    int col = this->get_column(index);
    int board_index;

    // Add items in rows and columns.
    for (int i = 0; i < this->board_width; i++) {
        for (int j = 0; j < this->board_width; j++) {
            board_index = this->get_index(i, j);

            if (this->board[board_index] == BLANK) continue;
            if (i == row) seen.push_back(this->board[board_index]);
            if (j == col) seen.push_back(this->board[board_index]);
        }
    }

    int region_width = (int)std::sqrt(this->board_width);
    int start_row = row - (row % region_width);
    int start_column = col - (col % region_width);

    // Range of the columns that form the region.
    std::pair<int, int> col_range =
        std::make_pair(start_column, start_column + region_width - 1);

    // Range of the rows that form the region.
    std::pair<int, int> row_range =
        std::make_pair(start_row, start_row + region_width - 1);

    // Add items in region.
    for (int i = row_range.first; i <= row_range.second; i++) {
        for (int j = col_range.first; j <= col_range.second; j++) {
            board_index = this->get_index(i, j);
            if (this->board[board_index] != BLANK) {
                seen.push_back(this->board[board_index]);
            }
        }
    }

    std::vector<int> possible_moves(this->board_width);
    std::iota(possible_moves.begin(), possible_moves.end(), 1);

    // Take the difference of the set of possible squares that can be placed and
    // the squares that were seen. Then remove the set of attempted moves, for
    // that index, from the set of available moves.
    auto available_moves = vec_difference(possible_moves, seen);
    return vec_difference(available_moves, this->attempts[index]);
}

std::vector<int> vec_difference(std::vector<int> a, std::vector<int> b) {
    std::vector<int> result;

    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());

    std::set_difference(a.begin(), a.end(), b.begin(), b.end(),
                        std::back_inserter(result));
    return result;
}
