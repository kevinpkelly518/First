#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#include "Board.hpp"
#include "Date.hpp"
#include "Exception.hpp"

#include <iostream>
#include <map>
#include <string>


namespace {


void print_action_header() {
  std::cout << "\t1. Tasks" << std::endl;
  std::cout << "\t2. Meals" << std::endl;
  std::cout << "\t3. Print Tasks" << std::endl;
}

void print_task_header() {
  std::cout << "\t1. Add task" << std::endl;
  // std::cout << "\t2. Edit task" << std::endl;
  // std::cout << "\t3. Remove task" << std::endl;
  // std::cout << "\t4. Move task" << std::endl;
  // std::cout << "\t5. Complete task" << std::endl;
  // std::cout << "\t6. Incomplete task" << std::endl;
  // std::cout << "\t7. Clear completed tasks" << std::endl;
  // std::cout << "\t8. Undo clear" << std::endl;
}

void print_meal_header() {
  std::cout << "\t1. Add meal" << std::endl;
  std::cout << "\t2. Edit meal date" << std::endl;
  std::cout << "\t3. Edit meal" << std::endl;
  std::cout << "\t4. Remove meal" << std::endl;
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
    std::cout << "ERROR: type \"" << type << "\" unrecognized. Enter \"breakfast\", \"lunch\", or \"dinner\"" << std::endl;
  }

  return meal_type;
}

class MainTaskListener : public First::TaskListener {
public:
  void notify(const First::TaskAddedEvent& task) override {
    std::cout << "Task Added" << std::endl;
    received_id = task.id;
  }

  unsigned int received_id = 0;
};

class MainMealListener : public First::MealListener {
public:
  void notify(const std::vector<std::vector<std::string>>& meal_list) override {
    std::cout << std::endl << "Meals:" << std::endl;

    for (const auto& meal : meal_list) {
      std::cout << "\t" << meal[0] << " " << meal[1] << " " << meal[2] << std::endl;
    }

    std::cout << std::endl;
  }
};

class MainExceptionListener : public First::ExceptionListener {
public:
  void notify(const std::string& k) override {
    std::cout << std::endl << "ERROR: " << k << std::endl << std::endl;
  }
};

void manage_tasks(First::Board& board, First::TaskListener* task_listener, std::map<std::string, unsigned int>& tasks) {
  print_task_header();
  const int action = get_input<int>("Select action: ");

  switch (action) {
  case 1: {
    const auto task = get_input<std::string>("Enter task: ");
    board.add_task();
    tasks[task] = dynamic_cast<MainTaskListener*>(task_listener)->received_id;

    break;
  }
  // case 2: {
  //   const std::string task = get_input<std::string>("Enter task: ");
  //   const std::string new_task = get_input<std::string>("Enter new task: ");
  //   board.edit_task(task, new_task);

  //   break;
  // }
  // case 3:
  //   board.erase_task(get_input<std::string>("Enter task: "));

  //   break;
  // case 4: {
  //   const std::string task = get_input<std::string>("Enter task: ");
  //   const int position = get_input<int>("Enter position: ");
  //   board.move_task(task, position);

  //   break;
  // }
  // case 5:
  //   board.complete_task(get_input<std::string>("Enter task: "));
  //   break;
  // case 6:
  //   board.incomplete_task(get_input<std::string>("Enter task: "));
  //   break;
  // case 7:
  //   board.clear_complete();
  //   break;
  // case 8:
  //   board.undo_clear();
  //   break;
  default:
    std::cout << "ERROR: input must be 1" << std::endl;
    break;
  }
}

void manage_meals(First::Board& board) {
  print_meal_header();
  const int action = get_input<int>("Select action: ");

  switch (action) {
  case 1: {
    const unsigned int year = get_input<unsigned int>("Enter year: ");
    const unsigned int month = get_input<unsigned int>("Enter month: ");
    const unsigned int day = get_input<unsigned int>("Enter day: ");
    const std::string type = get_input<std::string>("Enter meal type (breakfast/lunch/dinner): ");
    const std::string meal = get_input<std::string>("Enter meal: ");

    board.add_meal({year, month, day}, get_type(type), meal);

    break;
  }
  case 2: {
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
  case 3: {
    const unsigned int current_year = get_input<unsigned int>("Enter year of meal to change: ");
    const unsigned int current_month = get_input<unsigned int>("Enter month of meal to change: ");
    const unsigned int current_day = get_input<unsigned int>("Enter day of meal to change: ");
    const std::string current_type = get_input<std::string>("Enter meal type of meal to change (breakfast/lunch/dinner): ");

    const std::string new_meal = get_input<std::string>("Enter new meal: ");

    board.edit_meal({current_year, current_month, current_day}, get_type(current_type), new_meal);

    break;
  }
  case 4: {
    const unsigned int year = get_input<int>("Enter year: ");
    const unsigned int month = get_input<int>("Enter month: ");
    const unsigned int day = get_input<int>("Enter day: ");
    const std::string type = get_input<std::string>("Enter meal type (breakfast/lunch/dinner): ");

    board.erase_meal({year, month, day}, get_type(type));
    break;
  }
  default:
    std::cout << "Error: input must be between 1 and 4" << std::endl;
  }
}

void first_main() {
  std::cout << std::endl << "Welcome to First" << std::endl;

  const auto task_listener = std::make_unique<MainTaskListener>();
  const auto meal_listener = std::make_unique<MainMealListener>();
  const auto exception_listener = std::make_unique<MainExceptionListener>();

  First::Board board(task_listener.get(), meal_listener.get(), exception_listener.get());

  std::map<std::string, unsigned int> tasks;

  while (true) {
    print_action_header();
    const int action = get_input<int>("Select action: ");

    switch (action) {
    case 1:
      manage_tasks(board, task_listener.get(), tasks);
      break;
    case 2:
      manage_meals(board);
      break;
    case 3:
      std::cout << std::endl << "Tasks:" << std::endl;

      for (const auto& [key, value] : tasks) {
        std::cout << "\t" << key << std::endl;
      }

      std::cout << std::endl;

      break;
    default:
      std::cout << "ERROR: input must be 1 or 2" << std::endl;
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