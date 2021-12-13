#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#include "Board.hpp"
#include "Date.hpp"
#include "Exception.hpp"

#include <iostream>
#include <string>


namespace {


void print_action_header() {
  std::cout << std::endl;
  std::cout << "\t1. Add task" << std::endl;
  std::cout << "\t2. Edit task" << std::endl;
  std::cout << "\t3. Remove task" << std::endl;
  std::cout << "\t4. Move task" << std::endl;
  std::cout << std::endl;
  std::cout << "\t5. Add meal" << std::endl;
  std::cout << "\t6. Edit meal date" << std::endl;
  std::cout << "\t7. Edit meal" << std::endl;
  std::cout << "\t8. Remove meal" << std::endl;
}

template<typename T>
T get_input(const std::string& prompt) {
  std::cout << prompt;
  T input;
  std::cin >> input;

  return input;
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

class MainTaskListener : public First::TaskListener {
public:
  void notify(const std::vector<std::string>& tasks) override {
    std::cout << "Tasks:" << std::endl;

    for (const auto& task : tasks) {
      std::cout << "\t" << task << std::endl;
    }
  }
};

class MainMealListener : public First::MealListener {
public:
  void notify(const std::vector<std::vector<std::string>>& meal_list) override {
    std::cout << "Meals:" << std::endl;

    for (const auto& meal : meal_list) {
      std::cout << "\t" << meal[0] << " " << meal[1] << " " << meal[2] << std::endl;
    }
  }
};

class MainExceptionListener : public First::ExceptionListener {
public:
  void notify(const std::string& k) override {
    std::cout << "ERROR: " << k << std::endl;
  }
};

void first_main() {
  const auto task_listener = std::make_unique<MainTaskListener>();
  const auto meal_listener = std::make_unique<MainMealListener>();
  const auto exception_listener = std::make_unique<MainExceptionListener>();

  First::Board board(task_listener.get(), meal_listener.get(), exception_listener.get());

  while (true) {
    print_action_header();
    const int action = get_input<int>("Select action: ");

    switch (action) {
    case 1:
      board.add_task(get_input<std::string>("Enter task: "));

      break;
    case 2: {
      const std::string task = get_input<std::string>("Enter task: ");
      const std::string new_task = get_input<std::string>("Enter new task: ");
      board.edit_task(task, new_task);

      break;
    }
    case 3:
      board.erase_task(get_input<std::string>("Enter task: "));

      break;
    case 4: {
      const std::string task = get_input<std::string>("Enter task: ");
      const int position = get_input<int>("Enter position: ");
      board.move_task(task, position);

      break;
    }
    case 5: {
      const unsigned int year = get_input<unsigned int>("Enter year: ");
      const unsigned int month = get_input<unsigned int>("Enter month: ");
      const unsigned int day = get_input<unsigned int>("Enter day: ");
      const std::string type = get_input<std::string>("Enter meal type (breakfast/lunch/dinner): ");
      const std::string meal = get_input<std::string>("Enter meal: ");

      board.add_meal({year, month, day}, get_type(type), meal);

      break;
    }
    case 6: {
      const unsigned int current_year = get_input<unsigned int>("Enter year of meal to change: ");
      const unsigned int current_month = get_input<unsigned int>("Enter month of meal to change: ");
      const unsigned int current_day = get_input<unsigned int>("Enter day of meal to change: ");
      const std::string current_type = get_input<std::string>("Enter meal type of meal to change (breakfast/lunch/dinner): ");

      const unsigned int new_year = get_input<unsigned int>("Enter new year: ");
      const unsigned int new_month = get_input<unsigned int>("Enter new month: ");
      const unsigned int new_day = get_input<unsigned int>("Enter new day: ");
      const std::string new_type = get_input<std::string>("Enter new meal type (breakfast/lunch/dinner): ");

      board.edit_meal({current_year, current_month, current_day}, get_type(current_type), {new_year, new_month, new_day}, get_type(new_type));

      break;
    }
    case 7: {
      const unsigned int current_year = get_input<unsigned int>("Enter year of meal to change: ");
      const unsigned int current_month = get_input<unsigned int>("Enter month of meal to change: ");
      const unsigned int current_day = get_input<unsigned int>("Enter day of meal to change: ");
      const std::string current_type = get_input<std::string>("Enter meal type of meal to change (breakfast/lunch/dinner): ");

      const std::string new_meal = get_input<std::string>("Enter new meal: ");

      board.edit_meal({current_year, current_month, current_day}, get_type(current_type), new_meal);

      break;
    }
    case 8: {
      const unsigned int year = get_input<int>("Enter year: ");
      const unsigned int month = get_input<int>("Enter month: ");
      const unsigned int day = get_input<int>("Enter day: ");
      const std::string type = get_input<std::string>("Enter meal type (breakfast/lunch/dinner): ");

      board.erase_meal({year, month, day}, get_type(type));
      break;
    }
    default:
      std::cout << "Error: input must be between 1 and 8" << std::endl;
    }
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

  first_main();

  return test_result;
}