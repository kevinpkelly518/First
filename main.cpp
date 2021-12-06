#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#include "TaskList.hpp"
#include "Exception.hpp"

#include <iostream>
#include <string>

void print_task_list(First::TaskList task_list) {
  std::cout << "Cards in task_list:" << std::endl;

  for (const auto& card : task_list) {
    std::cout << "\t" << card << std::endl;
  }
}

void print_action_header() {
  std::cout << std::endl << "Select action:" << std::endl;
  std::cout << "\t1. Create card" << std::endl;
  std::cout << "\t2. Edit card" << std::endl;
  std::cout << "\t3. Remove card" << std::endl;
  std::cout << "\t4. Move card" << std::endl;
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

void create_card(First::TaskList& task_list, const std::string& title) {
  try {
    task_list.add(title);
  } catch (const ExistingCardException& exception) {
    std::cout << "Error: card already exists" << std::endl;
  }
}

void edit_card(First::TaskList& task_list, const std::string& title, const std::string& new_title) {
  try {
    task_list.edit(title, new_title);
  } catch (const NoCardException& exception) {
    std::cout << "Error: selected card does not exist" << std::endl;
  }
}

void remove_card(First::TaskList& task_list, const std::string& title) {
  try {
    task_list.erase(title);
  } catch (const NoCardException& exception) {
    std::cout << "Error: selected card does not exist" << std::endl;
  }
}

void move_card(First::TaskList& task_list, const std::string& title, int position) {
  try {
    task_list.move(title, position);
  } catch (const NoCardException& exception) {
    std::cout << "Error: selected card does not exist" << std::endl;
  } catch (const InvalidIndexException& exception) {
    std::cout << "Error: index exceeds number of cards" << std::endl;
  }
}

int main(int argc, char** argv) {
  doctest::Context context;

  context.applyCommandLine(argc, argv);

  int test_result = context.run();

  if (context.shouldExit()) {
    return test_result;
  }

  int client_result = 0;

  std::cout << "First Board" << std::endl;
  
  First::TaskList task_list;

  while (true) {
    print_action_header();
    const int action = get_action();

    switch (action) {
    case 1: {
      const std::string title = get_input("Enter card title: ");
      create_card(task_list, title);
    } break;
    case 2: {
      const std::string title = get_input("Enter card title: ");
      const std::string new_title = get_input("Enter new card title: ");
      edit_card(task_list, title, new_title);
    } break;
    case 3: {
      const std::string title = get_input("Enter card title: ");
      remove_card(task_list, title);
    } break;
    case 4: {
      const std::string title = get_input("Enter card title: ");
      std::cout << "Enter position: " << std::endl;
      int position;
      std::cin >> position;
      move_card(task_list, title, position);
      break;
    }
    default:
      std::cout << "Error: input must be 1, 2, or 3" << std::endl;
    }

    print_task_list(task_list);
  }

  return test_result + client_result;
}