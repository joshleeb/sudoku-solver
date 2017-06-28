#include <vector>

#include <catch/catch.hpp>

#include "../src/puzzle.h"

SCENARIO("constructing a puzzle", "[puzzle]") {
    GIVEN("a board") {
        std::vector<int> board = {2,  1,  -1, -1, -1, 3,  2,  -1,
                                  -1, -1, -1, 4,  1,  -1, -1, -1};

        THEN("should set the board") {
            puzzle new_puzzle(board);

            REQUIRE(new_puzzle.get_board() == board);
            REQUIRE(new_puzzle.get_board_width() == 4);
        }
    }
}

SCENARIO("solving a puzzle", "[puzzle]") {
    GIVEN("a puzzle with a 4x4 board") {
        puzzle new_puzzle(std::vector<int>{2, 1, -1, -1, 4, -1, -1, 1, 3, -1, -1,
                                           4, -1, -1, -1, 2});

        THEN("should solve the puzzle") {
            new_puzzle.solve();

            std::vector<int> expected_board = {2, 1, 4, 3, 4, 3, 2, 1,
                                               3, 2, 1, 4, 1, 4, 3, 2};
            REQUIRE(new_puzzle.get_board() == expected_board);
        }
    }

    GIVEN("a 9x9 board") {
        puzzle new_puzzle(std::vector<int>{
            5,  3,  -1, -1, 7,  -1, -1, -1, -1, 6,  -1, -1, 1,  9,  5,  -1, -1,
            -1, -1, 9,  8,  -1, -1, -1, -1, 6,  -1, 8,  -1, -1, -1, 6,  -1, -1,
            -1, 3,  4,  -1, -1, 8,  -1, 3,  -1, -1, 1,  7,  -1, -1, -1, 2,  -1,
            -1, -1, 6,  -1, 6,  -1, -1, -1, -1, 2,  8,  -1, -1, -1, -1, 4,  1,
            9,  -1, -1, 5,  -1, -1, -1, -1, 8,  -1, -1, 7,  9,
        });

        THEN("should solve the puzzle") {
            new_puzzle.solve();

            std::vector<int> expected_board = {
                5, 3, 4, 6, 7, 8, 9, 1, 2, 6, 7, 2, 1, 9, 5, 3, 4, 8, 1, 9, 8,
                3, 4, 2, 5, 6, 7, 8, 5, 9, 7, 6, 1, 4, 2, 3, 4, 2, 6, 8, 5, 3,
                7, 9, 1, 7, 1, 3, 9, 2, 4, 8, 5, 6, 9, 6, 1, 5, 3, 7, 2, 8, 4,
                2, 8, 7, 4, 1, 9, 6, 3, 5, 3, 4, 5, 2, 8, 6, 1, 7, 9};
            REQUIRE(new_puzzle.get_board() == expected_board);
        }
    }
}

SCENARIO("checking if puzzle is valid", "[puzzle]") {
    GIVEN("a valid board") {
        puzzle new_puzzle(std::vector<int>{2, 1, -1, -1, -1, 3, 2, -1, -1, -1,
                                           -1, 4, 1, -1, -1, -1});

        THEN("should set the board") {
            REQUIRE(new_puzzle.is_valid());
        }
    }

    GIVEN("an invalid board") {
        WHEN("board has invalid entries") {
            puzzle new_puzzle(std::vector<int>{1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3,
                                               4, 1, 2, 3, 99});

            THEN("should return false") {
                REQUIRE_FALSE(new_puzzle.is_valid());
            }
        }

        WHEN("board is of invalid size") {
            puzzle new_puzzle(std::vector<int>{1, 2, 1, 2});

            THEN("should return false") {
                REQUIRE_FALSE(new_puzzle.is_valid());
            }
        }

        WHEN("board is of invalid configuration") {
            puzzle new_puzzle(std::vector<int>{1, 2, 3, 4, 1, 2, 3, 4, 1, 2,
                                               3, 4, 1, 2, 3, 4, 1, 2, 3, 4});

            THEN("should throw false argument exception") {
                REQUIRE_FALSE(new_puzzle.is_valid());
            }
        }
    }
}
