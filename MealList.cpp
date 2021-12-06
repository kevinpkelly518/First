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

void MealList::add(const Date& date, MealType type, const std::string& meal) {
  meals[std::make_pair(date, type)] = meal;
}

std::string MealList::get(const Date& date, MealType type) const {
  try {
    return meals.at(std::make_pair(date, type));
  } catch (const std::out_of_range& e) {
    throw NoMealException();
  }
}

void MealList::edit(const Date& date, MealType type, const Date& new_date) {
  edit_key(date, type, new_date, type);
}

void MealList::edit(const Date& date, MealType type, MealType new_type) {
  edit_key(date, type, date, new_type);
}

void MealList::edit(const Date& date, MealType type, const std::string& new_meal) {
  try {
    meals.at(std::make_pair(date, type)) = new_meal;
  } catch (const std::out_of_range& e) {
    throw NoMealException();
  }
}

void MealList::erase(const Date& date, MealType type) {
  const auto meal = meals.find(std::make_pair(date, type));

  if (meal == meals.end()) {
    throw NoMealException();
  }

  meals.erase(meal);
}

void MealList::edit_key(const Date& date, MealType type, const Date& new_date, MealType new_type) {
  const auto meal = meals.find(std::make_pair(date, type));

  if (meal == meals.end()) {
    throw NoMealException();
  }

  const auto new_key = std::make_pair(new_date, new_type);

  if (meals.find(new_key) != meals.end()) {
    throw ExistingMealException();
  }

  meals[new_key] = meal->second;
  meals.erase(meal);
}


} // end namespace First