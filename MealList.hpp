#pragma once

#include "Date.hpp"
#include "Exception.hpp"

#include <string>
#include <unordered_map>
// #include <vector>


namespace First {


enum class MealType {
  Breakfast,
  Lunch,
  Dinner
};

struct Meal {
  MealType type;
  std::string meal;
};

class MealList {
public:
  bool empty() const;
  int size() const;
  void add(Date&& date, const MealType& meal_type, const std::string& meal);
  std::string get(const Date& date, const MealType& meal_type) const;

private:
  std::unordered_multimap<Date, Meal> meals;
};


} // end namespace First