#pragma once

#include <tuple>
#include <vector>

#define BLANK -1

class puzzle {
public:
    puzzle(std::vector<int> board);

    void solve();
    void display();

    bool is_valid();

    std::vector<int> get_board();
    int get_board_width();

private:
    int board_width;
    std::vector<int> board;

    // Squares provided in the initial board.
    std::vector<int> fixed_squares;

    // Attempted values per square.
    std::vector<std::vector<int>> attempts;

    // Get the available moves for a square based on the current board.
    std::vector<int> get_moves(int index);

    bool is_fixed_square(int index);

    inline int get_index(int row, int col) { return row * this->board_width + col; }
    inline int get_row(int index) { return index / this->board_width; }
    inline int get_column(int index) { return index % this->board_width; }
};

std::vector<int> vec_difference(std::vector<int> a, std::vector<int> b);
