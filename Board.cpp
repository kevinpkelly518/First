#include "Board.hpp"

#include "Exception.hpp"

#include <algorithm>
#include <iostream>

bool operator==(const Board& lhs, const std::vector<std::string>& rhs) {
  return lhs.cards == rhs;
}

void Board::create(const std::string& title) {
  const auto found = std::find(cards.begin(), cards.end(), title);

  if (found != cards.end()) {
    throw ExistingCardException();
  }

  cards.push_back(title);
}

bool Board::contains(const std::string& title) const {
  return std::find(cards.begin(), cards.end(), title) != cards.end();
}

bool Board::empty() const {
  return cards.empty();
}

void Board::remove(const std::string& title) {
  const auto found = std::find(cards.begin(), cards.end(), title);

  if (found == cards.end()) {
    throw NoCardException();
  }

  cards.erase(found);
}

void Board::edit(const std::string& title, const std::string& new_title) {
  const auto found = std::find(cards.begin(), cards.end(), title);

  if (found == cards.end()) {
    throw NoCardException();
  }

  *found = new_title;
}

void Board::move(const std::string& title, const int position) {
  const auto found = std::find(cards.begin(), cards.end(), title);

  if (found == cards.end()) {
    throw NoCardException();
  }

  if (position > cards.size()) {
    throw InvalidIndexException();
  }

  std::string card = *found;
  cards.erase(found);
  cards.insert(cards.begin() + position - 1, card);
}