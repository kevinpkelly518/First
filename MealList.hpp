#pragma once

#include "Date.hpp"
#include "Exception.hpp"

#include <map>
#include <string>
#include <utility>


namespace First {


enum class MealType {
  Breakfast,
  Lunch,
  Dinner
};

using MealKey = std::pair<Date, MealType>;

class MealList {
public:
  bool empty() const;
  int size() const;
  void add(Date&& date, MealType type, const std::string& meal);
  std::string get(const Date& date, MealType type) const;

private:
  std::map<MealKey, std::string> meals;
};


} // end namespace First