#include "MealList.hpp"

#include "Exception.hpp"

#include <algorithm>
#include <stdexcept>


namespace {


std::string get_string(First::MealType type) {
  switch (type) {
  case First::MealType::Breakfast:
    return "Breakfast";
  case First::MealType::Lunch:
    return "Lunch";
  case First::MealType::Dinner:
    return "Dinner";
  default:
    return "";
  }
}


} // end namespace


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

void MealList::edit(const Date& date, MealType type, const Date& new_date, MealType new_type) {
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

std::vector<std::vector<std::string>> MealList::to_string() const {
  std::vector<std::vector<std::string>> meal_list;

  for (const auto& [key, value] : meals) {
    meal_list.push_back({key.first.to_string(), get_string(key.second), value});
  }

  return meal_list;
}


} // end namespace First