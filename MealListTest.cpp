#include "doctest.h"

#include "Date.hpp"
#include "MealList.hpp"

TEST_CASE("Dates") {
  First::MealList meal_list;

  SUBCASE("Nonexistent date") {
    CHECK_THROWS_AS(meal_list.add({2021, 1, 0}, First::MealType::Dinner, "Cake"), InvalidDateException);
    CHECK_THROWS_AS(meal_list.add({2021, 1, 32}, First::MealType::Dinner, "Cake"), InvalidDateException);
    CHECK_THROWS_AS(meal_list.add({2021, 2, 29}, First::MealType::Dinner, "Cake"), InvalidDateException);
    CHECK_THROWS_AS(meal_list.add({2021, 4, 31}, First::MealType::Dinner, "Cake"), InvalidDateException);
    CHECK_THROWS_AS(meal_list.add({2021, 6, 31}, First::MealType::Dinner, "Cake"), InvalidDateException);
    CHECK_THROWS_AS(meal_list.add({2021, 9, 31}, First::MealType::Dinner, "Cake"), InvalidDateException);
    CHECK_THROWS_AS(meal_list.add({2021, 11, 31}, First::MealType::Dinner, "Cake"), InvalidDateException);

    CHECK_THROWS_AS(meal_list.add({2021, 0, 1}, First::MealType::Dinner, "Cake"), InvalidDateException);
    CHECK_THROWS_AS(meal_list.add({2021, 13, 1}, First::MealType::Dinner, "Cake"), InvalidDateException);
  }

  SUBCASE("Leap Year") {
    meal_list.add({2020, 2, 29}, First::MealType::Dinner, "Cake");

    CHECK(meal_list.get({2020, 2, 29}, First::MealType::Dinner) == "Cake");
  }
}

TEST_CASE("Meal List") {
  First::MealList meal_list;

  CHECK(meal_list.empty());

  SUBCASE("No Meal Exception") {
    CHECK_THROWS_AS(meal_list.get({2021, 12, 16}, First::MealType::Dinner), NoMealException);
  }

  SUBCASE("Add Meal") {
    meal_list.add({2021, 12, 16}, First::MealType::Dinner, "Cake");

    CHECK(!meal_list.empty());
    CHECK(meal_list.size() == 1);
    CHECK(meal_list.get({2021, 12, 16}, First::MealType::Dinner) == "Cake");

    SUBCASE("No Meal Exception") {
      CHECK_THROWS_AS(meal_list.get({2021, 1, 1}, First::MealType::Dinner), NoMealException);
      CHECK_THROWS_AS(meal_list.get({2021, 12, 16}, First::MealType::Breakfast), NoMealException);
    }

    SUBCASE("Multiple Meals") {
      SUBCASE("Different Dates") {
        meal_list.add({2021, 12, 17}, First::MealType::Dinner, "Pizza");

        CHECK(meal_list.size() == 2);
        CHECK(meal_list.get({2021, 12, 16}, First::MealType::Dinner) == "Cake");
        CHECK(meal_list.get({2021, 12, 17}, First::MealType::Dinner) == "Pizza");
      }

      SUBCASE("Different Meal Types") {
        meal_list.add({2021, 12, 16}, First::MealType::Breakfast, "Pizza");

        CHECK(meal_list.size() == 2);
        CHECK(meal_list.get({2021, 12, 16}, First::MealType::Breakfast) == "Pizza");
        CHECK(meal_list.get({2021, 12, 16}, First::MealType::Dinner) == "Cake");
      }

      SUBCASE("Overwrite") {
        meal_list.add({2021, 12, 16}, First::MealType::Dinner, "Pizza");

        CHECK(meal_list.size() == 1);
        CHECK(meal_list.get({2021, 12, 16}, First::MealType::Dinner) == "Pizza");
      }
    }
  }
}

TEST_CASE("Edit Meal") {
  First::MealList meal_list;

  SUBCASE("Nonexistent Entry") {
    CHECK_THROWS_AS(meal_list.edit({2021, 12, 16}, First::MealType::Dinner, "Cake"), NoMealException);
    CHECK_THROWS_AS(meal_list.edit({2021, 12, 16}, First::MealType::Dinner, First::Date{2021, 1, 1}), NoMealException);
    CHECK_THROWS_AS(meal_list.edit({2021, 12, 16}, First::MealType::Dinner, First::MealType::Breakfast), NoMealException);
  }

  SUBCASE("Edit") {
    meal_list.add({2021, 12, 16}, First::MealType::Dinner, "Cake");

    SUBCASE("Edit Meal") {
      meal_list.edit({2021, 12, 16}, First::MealType::Dinner, "Pizza");

      CHECK(meal_list.size() == 1);
      CHECK(meal_list.get({2021, 12, 16}, First::MealType::Dinner) == "Pizza");
    }

    SUBCASE("Edit Meal Type") {
      meal_list.edit({2021, 12, 16}, First::MealType::Dinner, First::MealType::Breakfast);

      CHECK(meal_list.size() == 1);
      CHECK(meal_list.get({2021, 12, 16}, First::MealType::Breakfast) == "Cake");
    }

    SUBCASE("Edit Date") {
      meal_list.edit({2021, 12, 16}, First::MealType::Dinner, First::Date{2021, 1, 1});

      CHECK(meal_list.size() == 1);
      CHECK(meal_list.get({2021, 1, 1}, First::MealType::Dinner) == "Cake");
    }

    SUBCASE("Edit To Existing Key") {
      meal_list.add({2021, 12, 17}, First::MealType::Dinner, "Pizza");

      CHECK_THROWS_AS(meal_list.edit({2021, 12, 17}, First::MealType::Dinner, First::Date{2021, 12, 16}), ExistingMealException);
      CHECK_THROWS_AS(meal_list.edit({2021, 12, 17}, First::MealType::Dinner, First::MealType::Dinner), ExistingMealException);
    }
  }
}

TEST_CASE("Remove Meal") {
  First::MealList meal_list;

  SUBCASE("Nonexistent Entry") {
    CHECK_THROWS_AS(meal_list.erase({2021, 12, 16}, First::MealType::Dinner), NoMealException);
  }

  SUBCASE("Erase") {
    meal_list.add({2021, 12, 16}, First::MealType::Dinner, "Cake");

    meal_list.erase({2021, 12, 16}, First::MealType::Dinner);

    CHECK(meal_list.empty());
  }
}