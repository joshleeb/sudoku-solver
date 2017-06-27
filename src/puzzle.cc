#include "puzzle.h"

#include <vector>

puzzle::puzzle(std::vector<int> board) {
    this->board = board;
    this->fixed_squares = {};

    // TODO: Check board validity.
    // TODO: Set board width.
    // TODO: Set fixed squares.
}

void puzzle::solve() {}
void puzzle::display() {}

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
    (void) index;
    return false;
}

std::vector<int> puzzle::get_moves(int index) {
    (void) index;
    return {};
}
