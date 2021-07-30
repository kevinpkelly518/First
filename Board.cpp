#include "Board.hpp"

#include "Exception.hpp"

#include <algorithm>

void Board::create(const std::string& title) {
  const auto found = std::find(cards.begin(), cards.end(), title);

  if (found != cards.end()) {
    throw ExistingCardException();
  }

  cards.push_back(title);
}

bool Board::contains(const std::string& title) {
  return std::find(cards.begin(), cards.end(), title) != cards.end();
}

bool Board::empty() {
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

std::vector<std::string> Board::get_cards() const {
  return cards;
}
