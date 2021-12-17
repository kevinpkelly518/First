#include "doctest.h"

#include "Date.hpp"
#include "Exception.hpp"
#include "List.hpp"

TEST_CASE("Add Items") {
  First::List list;

  SUBCASE("Nonexistent ID") {
    CHECK_THROWS_AS(list[1], NoIdException);
  }

  SUBCASE("Add With Date") {
    list.add(1, {2021, 12, 16});

    CHECK(list[1].date == First::Date{2021, 12, 16});
    CHECK(list[1].status == "New");

    SUBCASE("Duplicate ID") {
      CHECK_THROWS_AS(list.add(1, {2021, 12, 17}), ExistingIdException);
    }

    SUBCASE("Multiple") {
      list.add(2, {2021, 12, 17});

      CHECK(list[2].date == First::Date{2021, 12, 17});
      CHECK(list[2].status == "New");
    }
  }

  SUBCASE("Add Without Date") {
    list.add(1);

    CHECK(!list[1].date.has_value());
    CHECK(list[1].status == "New");

    SUBCASE("Duplicate ID") {
      CHECK_THROWS_AS(list.add(1), ExistingIdException);
    }
  }
}

TEST_CASE("Edit Items") {
  First::List list;

  SUBCASE("Nonexistent ID") {
    CHECK_THROWS_AS(list.edit(1, First::Date{2021, 12, 17}), NoIdException);
    CHECK_THROWS_AS(list.edit(1, "Done"), NoIdException);
  }

  list.add(1);

  SUBCASE("Edit Date") {
    list.edit(1, First::Date{2021, 12, 16});

    CHECK(list[1].date == First::Date{2021, 12, 16});
  }

  SUBCASE("Edit Status") {
    list.edit(1, "Done");

    CHECK(list[1].status == "Done");
  }
}

TEST_CASE("Erase Items") {
  First::List list;

  SUBCASE("Nonexistent ID") {
    CHECK_THROWS_AS(list.erase(1), NoIdException);
  }

  list.add(1);

  list.erase(1);

  CHECK_THROWS_AS(list[1], NoIdException);
}
