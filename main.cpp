#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#include "Date.hpp"
#include "Exception.hpp"
#include "MealList.hpp"
#include "TaskList.hpp"

#include <iostream>
#include <string>


namespace {


First::TaskList task_list;
First::MealList meal_list;

void print_task_list() {
  std::cout << "Cards in task list:" << std::endl;

  for (const auto& card : task_list) {
    std::cout << "\t" << card << std::endl;
  }
}

void print_meal_list() {
  std::cout << "Meals in meal list:" << std::endl;

  for (const auto& meal : meal_list) {
    std::string type;
    switch (meal.first.second) {
    case First::MealType::Breakfast:
      type = "Breakfast";
      break;
    case First::MealType::Lunch:
      type = "Lunch";
      break;
    case First::MealType::Dinner:
      type = "Dinner";
      break;
    }

    std::cout << "\t" << meal.first.first.year << " " << First::mtoi(meal.first.first.month.get()) <<
        " " << meal.first.first.day << "\t" << type << "\t" << meal.second << std::endl;
  }
}

void print_action_header() {
  std::cout << std::endl << "Select action:" << std::endl;
  std::cout << "\t1. Add card" << std::endl;
  std::cout << "\t2. Edit card" << std::endl;
  std::cout << "\t3. Remove card" << std::endl;
  std::cout << "\t4. Move card" << std::endl;
  std::cout << "\t5. Add meal" << std::endl;
  std::cout << "\t6. Edit meal" << std::endl;
  std::cout << "\t7. Remove meal" << std::endl;
}

int get_action() {
  int action;
  std::cin >> action;

  return action;
}

std::string get_string_input(const std::string& prompt) {
  std::cout << prompt;
  std::string input;
  std::cin >> input;
  std::cout << std::endl;

  return input;
}

unsigned int get_value_input(const std::string& prompt) {
  std::cout << prompt;
  unsigned int input;
  std::cin >> input;
  std::cout << std::endl;

  return input;
}

void create_card(const std::string& title) {
  try {
    task_list.add(title);
  } catch (const ExistingCardException& exception) {
    std::cout << "Error: card already exists" << std::endl;
  }
}

void edit_card(const std::string& title, const std::string& new_title) {
  try {
    task_list.edit(title, new_title);
  } catch (const NoCardException& exception) {
    std::cout << "Error: selected card does not exist" << std::endl;
  }
}

void remove_card(const std::string& title) {
  try {
    task_list.erase(title);
  } catch (const NoCardException& exception) {
    std::cout << "Error: selected card does not exist" << std::endl;
  }
}

void move_card(const std::string& title, int position) {
  try {
    task_list.move(title, position);
  } catch (const NoCardException& exception) {
    std::cout << "Error: selected card does not exist" << std::endl;
  } catch (const InvalidIndexException& exception) {
    std::cout << "Error: index exceeds number of cards" << std::endl;
  }
}

First::MealType get_type(const std::string& type) {
  First::MealType meal_type;

  if (type == "breakfast") {
    meal_type = First::MealType::Breakfast;
  } else if (type == "lunch") {
    meal_type = First::MealType::Lunch;
  } else if (type == "dinner") {
    meal_type = First::MealType::Dinner;
  } else {
    std::cout << "Error: type \"" << type << "\" unrecognized. Enter \"breakfast\", \"lunch\", or \"dinner\"" << std::endl;
  }

  return meal_type;
}

void create_meal(const First::Date& date, const std::string& type, const std::string& meal) {
  meal_list.add(date, get_type(type), meal);
}

void edit_meal(const First::Date& date, const std::string& type, const First::Date& new_date, const std::string& new_type, const std::string& new_meal) {
  try {
    meal_list.edit(date, get_type(type), new_meal);
    meal_list.edit(date, get_type(type), new_date);
    meal_list.edit(new_date, get_type(type), get_type(new_type));
  } catch (const NoMealException& e) {
    std::cout << "Error: meal to edit does not exist" << std::endl;
  } catch (const ExistingMealException& e) {
    std::cout << "Error: new meal already exists" << std::endl;
  }
}

void remove_meal(const First::Date& date, const std::string& type) {
  try {
    meal_list.erase(date, get_type(type));
  } catch (const NoMealException& e) {
    std::cout << "Error: meal does not exist" << std::endl;
  }
}


} // end namespace


int main(int argc, char** argv) {
  doctest::Context context;

  context.applyCommandLine(argc, argv);

  int test_result = context.run();

  if (context.shouldExit()) {
    return test_result;
  }

  int client_result = 0;

  std::cout << "First Board" << std::endl;

  while (true) {
    print_action_header();
    const int action = get_action();

    switch (action) {
    case 1: {
      const std::string title = get_string_input("Enter card title: ");
      create_card(title);
    } break;
    case 2: {
      const std::string title = get_string_input("Enter card title: ");
      const std::string new_title = get_string_input("Enter new card title: ");
      edit_card(title, new_title);
    } break;
    case 3: {
      const std::string title = get_string_input("Enter card title: ");
      remove_card(title);
    } break;
    case 4: {
      const std::string title = get_string_input("Enter card title: ");
      std::cout << "Enter position: " << std::endl;
      int position;
      std::cin >> position;
      move_card(title, position);
    } break;
    case 5: {
      const unsigned int month = get_value_input("Enter month: ");
      const unsigned int day = get_value_input("Enter day: ");
      const std::string type = get_string_input("Enter meal type (breakfast/lunch/dinner): ");
      const std::string meal = get_string_input("Enter meal: ");

      try {
        create_meal({2021, month, day}, type, meal);
      } catch (const InvalidDateException& e) {
        std::cout << "Error: date does not exist" << std::endl;
      }
    } break;
    case 6: {
      const unsigned int current_month = get_value_input("Enter month of meal to change: ");
      const unsigned int current_day = get_value_input("Enter day of meal to change: ");
      const std::string current_type = get_string_input("Enter meal type of meal to change (breakfast/lunch/dinner): ");

      const unsigned int new_month = get_value_input("Enter new month: ");
      const unsigned int new_day = get_value_input("Enter new day: ");
      const std::string new_type = get_string_input("Enter new meal type (breakfast/lunch/dinner): ");
      const std::string new_meal = get_string_input("Enter new meal: ");

      try {
        edit_meal({2021, current_month, current_day}, current_type, {2021, new_month, new_day}, new_type, new_meal);
      } catch (const InvalidDateException& e) {
        std::cout << "Error: date does not exist" << std::endl;
      }
    } break;
    case 7: {
      const unsigned int current_month = get_value_input("Enter current month: ");
      const unsigned int current_day = get_value_input("Enter current day: ");
      const std::string current_type = get_string_input("Enter current meal type (breakfast/lunch/dinner): ");

      remove_meal({2021, current_month, current_day}, current_type);
    } break;
    default:
      std::cout << "Error: input must be between 1 and 7" << std::endl;
    }

    print_task_list();
    print_meal_list();
  }

  return test_result + client_result;
}