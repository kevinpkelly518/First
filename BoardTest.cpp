#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Board.hpp"
#include "Exception.hpp"

TEST_CASE("Board Creation") {
  Board board;

  SUBCASE("Empty Board") {
    CHECK(board.empty());
  }

  SUBCASE("Create/remove/edit cards") {
    board.create("Title");

    SUBCASE("Single card") {
      CHECK(!board.empty());
      CHECK(board.contains("Title"));
    }

    SUBCASE("Same name") {
      CHECK_THROWS_AS(board.create("Title"), ExistingCardException);
    }

    SUBCASE("Nonexistent card") {
      CHECK(!board.contains("Test"));
    }

    SUBCASE("Multiple cards") {
      board.create("Title 2");

      CHECK(board.contains("Title"));
      CHECK(board.contains("Title 2"));
    }

    SUBCASE("Remove card") {
      board.remove("Title");

      CHECK(!board.contains("Title"));
    }

    SUBCASE("Remove nonexistent card") {
      CHECK_THROWS_AS(board.remove("Test"), NoCardException);
    }

    SUBCASE("Edit card") {
      board.edit("Title", "Test");

      CHECK(board.contains("Test"));
      CHECK(!board.contains("Title"));
    }

    SUBCASE("Edit nonexistent card") {
      CHECK_THROWS_AS(board.edit("Test", "Title"), NoCardException);
    }
  }
}
