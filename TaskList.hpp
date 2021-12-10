#pragma once

#include <string>
#include <vector>


namespace First {


class TaskList {
public:
  std::vector<std::string> get() const;

  void add(const std::string& title);
  bool empty() const;
  bool contains(const std::string& title) const;
  void erase(const std::string& title);
  void edit(const std::string& title, const std::string& new_title);
  void move(const std::string& title, const unsigned int position);

  friend bool operator==(const TaskList& left, const std::vector<std::string>& right);

  inline std::vector<std::string>::iterator begin() noexcept { return tasks.begin(); }
  inline std::vector<std::string>::const_iterator cbegin() const noexcept { return tasks.cbegin(); }
  inline std::vector<std::string>::iterator end() noexcept { return tasks.end(); }
  inline std::vector<std::string>::const_iterator cend() const noexcept { return tasks.cend(); }

private:
  std::vector<std::string> tasks;
};


} // end namespace First