#include "TaskList.hpp"

#include "Exception.hpp"

#include <algorithm>
#include <iostream>


namespace First {


bool operator==(const TaskList& lhs, const std::vector<std::string>& rhs) {
  return lhs.tasks == rhs;
}

std::vector<std::string> TaskList::get() const {
  return tasks;
}

void TaskList::add(const std::string& title) {
  if (contains(title)) {
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
  const auto task = std::find(tasks.begin(), tasks.end(), title);

  if (task == tasks.end()) {
    throw NoCardException();
  }

  tasks.erase(task);
}

void TaskList::edit(const std::string& title, const std::string& new_title) {
  const auto task = std::find(tasks.begin(), tasks.end(), title);

  if (task == tasks.end()) {
    throw NoCardException();
  }

  if (contains(new_title)) {
    throw ExistingCardException();
  }

  *task = new_title;
}

void TaskList::move(const std::string& title, const unsigned int position) {
  const auto task = std::find(tasks.begin(), tasks.end(), title);

  if (task == tasks.end()) {
    throw NoCardException();
  }

  if (position > tasks.size()) {
    throw InvalidIndexException();
  }

  std::string card = *task;
  tasks.erase(task);
  tasks.insert(tasks.begin() + position - 1, card);
}


} // end namespace First