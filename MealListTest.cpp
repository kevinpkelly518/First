#include "doctest.h"

#include "Date.hpp"
#include "MealList.hpp"

// TODO meal list and task list separate objects in board?

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
        meal_list.add({2021, 12, 16}, First::MealType::Dinner, "Cake");
        meal_list.add({2021, 12, 16}, First::MealType::Dinner, "Pizza");

        CHECK(meal_list.size() == 1);
        CHECK(meal_list.get({2021, 12, 16}, First::MealType::Dinner) == "Pizza");;
      }
    }
  }
}
