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
  void move(const std::string& title, const unsigned int position);

  friend bool operator==(const Board& lhs, const std::vector<std::string>& rhs);

  using container = std::vector<std::string>;
  using iterator = typename container::iterator;
  using const_iterator = typename container::const_iterator;

  inline iterator begin() noexcept { return cards.begin(); }
  inline const_iterator cbegin() const noexcept { return cards.cbegin(); }
  inline iterator end() noexcept { return cards.end(); }
  inline const_iterator cend() const noexcept { return cards.cend(); }

private:
  container cards;
};