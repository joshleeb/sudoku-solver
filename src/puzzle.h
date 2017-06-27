#pragma once

#include <vector>

#define BLANK -1

class puzzle {
public:
    puzzle(std::vector<int> board);

    void solve();
    void display();

    bool is_valid();
    bool is_solved();

    std::vector<int> get_board();
    int get_board_width();

private:
    int board_width;
    std::vector<int> board;
    std::vector<int> fixed_squares;

    // Attempted values per square.
    std::vector<std::vector<int>> attempts;

    // Possible values per square.
    std::vector<std::vector<int>> values;

    bool is_fixed_square(int index);

    std::vector<int> get_moves(int index);
    inline int get_index(int row, int col);
};
