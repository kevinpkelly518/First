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
  void add(const Date& date, MealType type, const std::string& meal);
  std::string get(const Date& date, MealType type) const;
  void edit(const Date& date, MealType type, const Date& new_date);
  void edit(const Date& date, MealType type, MealType new_type);
  void edit(const Date& date, MealType type, const std::string& new_meal);
  void erase(const Date& date, MealType type);

  inline std::map<MealKey, std::string>::iterator begin() noexcept { return meals.begin(); }
  inline std::map<MealKey, std::string>::const_iterator cbegin() const noexcept { return meals.cbegin(); }
  inline std::map<MealKey, std::string>::iterator end() noexcept { return meals.end(); }
  inline std::map<MealKey, std::string>::const_iterator cend() const noexcept { return meals.cend(); }

private:
  void edit_key(const Date& date, MealType type, const Date& new_date, MealType new_type);

  std::map<MealKey, std::string> meals;
};


} // end namespace First