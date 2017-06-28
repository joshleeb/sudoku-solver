#include <vector>

#include <catch/catch.hpp>

#define private public
#include "../src/puzzle.h"

SCENARIO("getting available moves", "[puzzle]") {
    GIVEN("a puzzle with a valid 9x9 board") {
        std::vector<int> expected_moves{};
        puzzle new_puzzle(std::vector<int>{
            5,  3,  -1, -1, 7,  -1, -1, -1, -1, 6,  -1, -1, 1,  9,  5,  -1, -1,
            -1, -1, 9,  8,  -1, -1, -1, -1, 6,  -1, 8,  -1, -1, -1, 6,  -1, -1,
            -1, 3,  4,  -1, -1, 8,  -1, 3,  -1, -1, 1,  7,  -1, -1, -1, 2,  -1,
            -1, -1, 6,  -1, 6,  -1, -1, -1, -1, 2,  8,  -1, -1, -1, -1, 4,  1,
            9,  -1, -1, 5,  -1, -1, -1, -1, 8,  -1, -1, 7,  9,
        });

        THEN("should return available moves") {
            expected_moves = {1, 2, 4};
            REQUIRE(new_puzzle.get_moves(2) == expected_moves);

            expected_moves = {2, 6};
            REQUIRE(new_puzzle.get_moves(3) == expected_moves);

            expected_moves = {2, 4, 6, 8};
            REQUIRE(new_puzzle.get_moves(5) == expected_moves);

            expected_moves = {1, 4, 8, 9};
            REQUIRE(new_puzzle.get_moves(6) == expected_moves);

            expected_moves = {1, 2, 4, 9};
            REQUIRE(new_puzzle.get_moves(7) == expected_moves);

            expected_moves = {2, 4, 8};
            REQUIRE(new_puzzle.get_moves(8) == expected_moves);
        }

        WHEN("having already tried options") {
            new_puzzle.attempts[7] = std::vector<int>{1, 2, 4};

            THEN("should return available moves without tries options") {
                expected_moves = {9};
                REQUIRE(new_puzzle.get_moves(7) == expected_moves);
            }
        }
    }

    GIVEN("a puzzle with a valid 4x4 board") {
        std::vector<int> expected_moves{};
        puzzle new_puzzle(std::vector<int>{2, 1, -1, -1, -1, 3, 2, -1, -1, -1,
                                           -1, 4, 1, -1, -1, -1});

        THEN("should return available moves") {
            expected_moves = {3, 4};
            REQUIRE(new_puzzle.get_moves(2) == expected_moves);

            expected_moves = {3};
            REQUIRE(new_puzzle.get_moves(3) == expected_moves);

            expected_moves = {4};
            REQUIRE(new_puzzle.get_moves(4) == expected_moves);

            expected_moves = {1};
            REQUIRE(new_puzzle.get_moves(7) == expected_moves);

            expected_moves = {3};
            REQUIRE(new_puzzle.get_moves(8) == expected_moves);

            expected_moves = {2};
            REQUIRE(new_puzzle.get_moves(9) == expected_moves);

            expected_moves = {1, 3};
            REQUIRE(new_puzzle.get_moves(10) == expected_moves);

            expected_moves = {2, 4};
            REQUIRE(new_puzzle.get_moves(13) == expected_moves);

            expected_moves = {3};
            REQUIRE(new_puzzle.get_moves(14) == expected_moves);

            expected_moves = {2, 3};
            REQUIRE(new_puzzle.get_moves(15) == expected_moves);
        }

        WHEN("having already tried options") {
            new_puzzle.attempts[2] = std::vector<int>{3};

            THEN("should return available moves without tries options") {
                expected_moves = {4};
                REQUIRE(new_puzzle.get_moves(2) == expected_moves);
            }
        }
    }
}

SCENARIO("getting index from row and column", "[puzzle]") {
    GIVEN("a puzzle") {
        puzzle new_puzzle({});
        new_puzzle.board_width = 16;

        THEN("should get index of row and column") {
            REQUIRE(new_puzzle.get_index(1, 4) == 20);
        }
    }
}

SCENARIO("getting row from index", "[puzzle]") {
    GIVEN("a puzzle") {
        puzzle new_puzzle({});
        new_puzzle.board_width = 16;

        THEN("should get row from index") {
            REQUIRE(new_puzzle.get_row(20) == 1);
        }
    }
}

SCENARIO("getting column from index", "[puzzle]") {
    GIVEN("a puzzle") {
        puzzle new_puzzle({});
        new_puzzle.board_width = 16;

        THEN("should get column from index") {
            REQUIRE(new_puzzle.get_column(20) == 4);
        }
    }
}
