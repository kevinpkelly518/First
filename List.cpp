#include "List.hpp"

#include "Exception.hpp"


namespace First {


bool operator==(const Item& left, const Item& right) {
  return left.date == right.date && left.status == right.status;
}

void List::add(unsigned int id) {
  if (items.find(id) != items.end()) {
    throw ExistingIdException();
  }

  items.insert(std::make_pair(id, Item{{}, "New"}));
}

void List::add(unsigned int id, const Date& date) {
  if (items.find(id) != items.end()) {
    throw ExistingIdException();
  }

  items.insert(std::make_pair(id, Item{date, "New"}));
}

void List::edit(unsigned int id, const Date& date) {
  if (items.find(id) == items.end()) {
    throw NoIdException();
  }

  items.at(id).date = date;
}

void List::edit(unsigned int id, const std::string& status) {
  if (items.find(id) == items.end()) {
    throw NoIdException();
  }

  items.at(id).status = status;
}

void List::erase(unsigned int id) {
  if (items.find(id) == items.end()) {
    throw NoIdException();
  }

  items.erase(id);
}

Item List::operator[](unsigned int id) {
  if (items.find(id) == items.end()) {
    throw NoIdException();
  }

  return items.at(id);
}


} // end namespace First