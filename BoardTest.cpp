#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Board.hpp"
#include "Exception.hpp"

TEST_CASE("Card management") {
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

TEST_CASE("Board Accessors") {
  Board board;
  std::vector<std::string> cards{"Title 1", "Title 2", "Title 3"};

  for (const auto& card : cards) {
    board.create(card);
  }

  CHECK(board.get_cards() == cards);
}

TEST_CASE("Card Prioritization") {
  Board board;

  SUBCASE("Nonexistent card") {
    CHECK_THROWS_AS(board.move("Test", 1), NoCardException);
  }

  SUBCASE("Move Cards") {
    board.create("Title");

    SUBCASE("Invalid Position") {
      CHECK_THROWS_AS(board.move("Title", 2), InvalidIndexException);
    }

    SUBCASE("Multiple Cards") {
      board.create("Title 2");

      SUBCASE("Two Cards") {
        board.move("Title 2", 1);

        CHECK(board.get_cards() == std::vector<std::string>{"Title 2", "Title"});
      }

      SUBCASE("Three Cards") {
        board.create("Title 3");

        board.move("Title 3", 1);

        CHECK(board.get_cards() == std::vector<std::string>{"Title 3", "Title", "Title 2"});
      }
    }
  }
}
