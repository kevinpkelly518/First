#include "TaskList.hpp"

#include "Exception.hpp"

#include <algorithm>
#include <iostream>


namespace First {


bool operator==(const TaskList& lhs, const std::vector<std::string>& rhs) {
  return lhs.tasks == rhs;
}

void TaskList::add(const std::string& title) {
  const auto found = std::find(tasks.begin(), tasks.end(), title);

  if (found != tasks.end()) {
    throw ExistingCardException();
  }

  tasks.push_back(title);
}

bool TaskList::contains(const std::string& title) const {
  return std::find(tasks.begin(), tasks.end(), title) != tasks.end();
}

bool TaskList::empty() const {
  return tasks.empty();
}

void TaskList::erase(const std::string& title) {
  const auto found = std::find(tasks.begin(), tasks.end(), title);

  if (found == tasks.end()) {
    throw NoCardException();
  }

  tasks.erase(found);
}

void TaskList::edit(const std::string& title, const std::string& new_title) {
  const auto found = std::find(tasks.begin(), tasks.end(), title);

  if (found == tasks.end()) {
    throw NoCardException();
  }

  *found = new_title;
}

void TaskList::move(const std::string& title, const unsigned int position) {
  const auto found = std::find(tasks.begin(), tasks.end(), title);

  if (found == tasks.end()) {
    throw NoCardException();
  }

  if (position > tasks.size()) {
    throw InvalidIndexException();
  }

  std::string card = *found;
  tasks.erase(found);
  tasks.insert(tasks.begin() + position - 1, card);
}


} // end namespace First