#pragma once

#include <string>
#include <vector>

class Board {
public:
  void create(const std::string& title);
  bool empty() const;
  bool contains(const std::string& title) const;
  void remove(const std::string& title);
  void edit(const std::string& title, const std::string& new_title);
  void move(const std::string& title, const int position);
  std::vector<std::string> get_cards() const;

private:
  std::vector<std::string> cards;
};