#pragma once

#include "Date.hpp"

#include <map>
#include <optional>
#include <string>


namespace First {


struct Item {
  std::optional<Date> date;
  std::string status;
};

bool operator==(const Item& left, const Item& right);

class List {
public:
  void add(unsigned int id);
  void add(unsigned int id, const Date& date);

  void edit(unsigned int id, const Date& date);
  void edit(unsigned int id, const std::string& status);

  void erase(unsigned int id);

  Item operator[](unsigned int id);

private:
  std::map<unsigned int, Item> items;
};


} // end namespace First