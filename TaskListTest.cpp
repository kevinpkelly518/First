#include "doctest.h"

#include "TaskList.hpp"
#include "Exception.hpp"

TEST_CASE("Card management") {
  First::TaskList task_list;

  SUBCASE("Empty TaskList") {
    CHECK(task_list.empty());
  }

  SUBCASE("Create/remove/edit cards") {
    task_list.add("Title");

    SUBCASE("Single card") {
      CHECK(!task_list.empty());
      CHECK(task_list.contains("Title"));
    }

    SUBCASE("Same name") {
      CHECK_THROWS_AS(task_list.add("Title"), ExistingCardException);
    }

    SUBCASE("Nonexistent card") {
      CHECK(!task_list.contains("Test"));
    }

    SUBCASE("Multiple cards") {
      task_list.add("Title 2");

      CHECK(task_list.contains("Title"));
      CHECK(task_list.contains("Title 2"));
    }

    SUBCASE("Remove card") {
      task_list.erase("Title");

      CHECK(!task_list.contains("Title"));
    }

    SUBCASE("Remove nonexistent card") {
      CHECK_THROWS_AS(task_list.erase("Test"), NoCardException);
    }

    SUBCASE("Edit card") {
      task_list.edit("Title", "Test");

      CHECK(task_list.contains("Test"));
      CHECK(!task_list.contains("Title"));
    }

    SUBCASE("Edit nonexistent card") {
      CHECK_THROWS_AS(task_list.edit("Test", "Title"), NoCardException);
    }
  }
}

TEST_CASE("Card Prioritization") {
  First::TaskList task_list;

  SUBCASE("Nonexistent card") {
    CHECK_THROWS_AS(task_list.move("Test", 1), NoCardException);
  }

  SUBCASE("Move Cards") {
    task_list.add("Title");

    SUBCASE("Invalid Position") {
      CHECK_THROWS_AS(task_list.move("Title", 2), InvalidIndexException);
    }

    SUBCASE("Multiple Cards") {
      task_list.add("Title 2");

      SUBCASE("Two Cards") {
        task_list.move("Title 2", 1);

        CHECK(task_list == std::vector<std::string>{"Title 2", "Title"});
      }

      SUBCASE("Three Cards") {
        task_list.add("Title 3");

        task_list.move("Title 3", 1);

        CHECK(task_list == std::vector<std::string>{"Title 3", "Title", "Title 2"});
      }
    }
  }
}
