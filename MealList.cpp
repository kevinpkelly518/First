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

void MealList::add(Date&& date, MealType type, const std::string& meal) {
  meals[std::make_pair(date, type)] = meal;
}

std::string MealList::get(const Date& date, MealType type) const {
  try {
    return meals.at(std::make_pair(date, type));
  } catch(const std::out_of_range& e) {
    throw NoMealException();
  }
}


} // end namespace First