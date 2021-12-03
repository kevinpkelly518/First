#include "MealList.hpp"

#include "Exception.hpp"

#include <algorithm>


namespace First {


bool MealList::empty() const {
  return meals.empty();
}

int MealList::size() const {
  return meals.size();
}

void MealList::add(Date&& date, const MealType& meal_type, const std::string& meal) {
  const auto meals_on_date = meals.equal_range(date);

  if (meals_on_date.first != meals.end()) {
    const auto existing_meal = std::find_if(
        meals_on_date.first,
        meals_on_date.second,
        [&meal_type](const std::pair<const Date, Meal>& meal) {
          return meal.second.type == meal_type;
        }
    );

    if (existing_meal != meals.end()) {
      meals.erase(existing_meal);
    }
  }

  meals.insert(std::make_pair(std::move(date), Meal{meal_type, meal}));
}

std::string MealList::get(const Date& date, const MealType& meal_type) const {
  const auto meals_on_date = meals.equal_range(date);

  if (meals_on_date.first == meals.end()) {
    throw NoMealException();
  }

  const auto meal = std::find_if(
      meals_on_date.first,
      meals_on_date.second,
      [&meal_type](const std::pair<const Date, Meal>& meal) {
        return meal.second.type == meal_type;
      }
  );

  if (meal == meals.end()) {
    throw NoMealException();
  }

  return meal->second.meal;
}


} // end namespace First