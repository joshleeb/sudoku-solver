#include <istream>
#include <vector>

#include <catch/catch.hpp>

#include "../src/interface.h"

SCENARIO("reading board from stream", "[interface]") {
    GIVEN("a stream of board tokens") {
        std::istringstream string_stream("1234.\n56789");
        string_stream.clear();  // Add EOF to stream.

        THEN("should get board") {
            auto board = interface::read_board(string_stream);

            std::vector<int> expected_board = {1, 2, 3, 4, -1, 5, 6, 7, 8, 9};
            REQUIRE(board == expected_board);
        }
    }

    GIVEN("a stream of board tokens with whitespace") {
        std::istringstream string_stream("1  23   4.\n 56 7  89  \n\n");
        string_stream.clear();  // Add EOF to stream.

        THEN("should get board and ignore the spaces") {
            auto board = interface::read_board(string_stream);

            std::vector<int> expected_board = {1, 2, 3, 4, -1, 5, 6, 7, 8, 9};
            REQUIRE(board == expected_board);
        }
    }
}
