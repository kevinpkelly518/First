#include "Board.hpp"
#include "Exception.hpp"

#include <iostream>
#include <string>

void print_board(Board board) {
  std::cout << "Cards in board:" << std::endl;

  for (const auto& card : board.get_cards()) {
    std::cout << "\t" << card << std::endl;
  }
}

void print_action_header() {
  std::cout << std::endl << "Select action:" << std::endl;
  std::cout << "\t1. Create card" << std::endl;
  std::cout << "\t2. Edit card" << std::endl;
  std::cout << "\t3. Remove card" << std::endl;
}

int get_action() {
  int action;
  std::cin >> action;

  return action;
}

std::string get_input(const std::string& prompt) {
  std::cout << prompt;
  std::string input;
  std::cin >> input;
  std::cout << std::endl;

  return input;
}

void create_card(Board& board, const std::string& title) {
  try {
    board.create(title);
  } catch (const ExistingCardException& exception) {
    std::cout << "Error: card already exists" << std::endl;
  }
}

void edit_card(Board& board, const std::string& title, const std::string& new_title) {
  try {
    board.edit(title, new_title);
  } catch (const NoCardException& exception) {
    std::cout << "Error: selected card does not exist" << std::endl;
  }
}

void remove_card(Board& board, const std::string& title) {
  try {
    board.remove(title);
  } catch (const NoCardException& exception) {
    std::cout << "Error: selected card does not exist" << std::endl;
  }
}

int main() {
  std::cout << "First Board" << std::endl;
  
  Board board;

  while (true) {
    print_action_header();
    const int action = get_action();

    switch (action) {
    case 1: {
      const std::string title = get_input("Enter card title: ");
      create_card(board, title);
    } break;
    case 2: {
      const std::string title = get_input("Enter card title: ");
      const std::string new_title = get_input("Enter new card title: ");
      edit_card(board, title, new_title);
    } break;
    case 3: {
      const std::string title = get_input("Enter card title: ");
      remove_card(board, title);
    } break;
    default:
      std::cout << "Error: input must be 1, 2, or 3" << std::endl;
    }

    print_board(board);
  }
}