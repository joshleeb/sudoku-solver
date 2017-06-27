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

SCENARIO("checking if puzzle is solved", "[puzzle]") {
    GIVEN("a solved puzzle") {
        puzzle new_puzzle(
            std::vector<int>{2, 1, 4, 3, 4, 3, 2, 1, 3, 2, 1, 4, 1, 4, 3, 2});

        THEN("should return true") {
            REQUIRE(new_puzzle.is_solved());
        }
    }

    GIVEN("an unsolved puzzle with blanks") {
        puzzle new_puzzle(
            std::vector<int>{-1, 1, 4, 3, 4, 3, 2, 1, 3, 2, 1, 4, 1, 4, 3, -1});

        THEN("should return false") {
            REQUIRE_FALSE(new_puzzle.is_solved());
        }
    }

    GIVEN("an unsolved puzzle without blanks") {
        puzzle new_puzzle(
            std::vector<int>{2, 1, 4, 3, 4, 3, 2, 1, 3, 2, 1, 4, 1, 4, 2, 3});

        THEN("should return false") {
            REQUIRE_FALSE(new_puzzle.is_solved());
        }
    }
}
