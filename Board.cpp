#include "Board.hpp"

#include "Exception.hpp"


namespace First {


Board::Board(TaskListener* tl, MealListener* ml, ExceptionListener* el) :
    task_listener(tl), meal_listener(ml), exception_listener(el) {}

void Board::add_task(const std::string& task) {
  try {
    task_list.add(task);
    task_listener->notify(task_list.get());
  } catch (const ExistingCardException& e) {
    exception_listener->notify("ExistingCard");
  }
}

void Board::erase_task(const std::string& task) {
  try {
    task_list.erase(task);
    task_listener->notify(task_list.get());
  } catch (const NoCardException& e) {
    exception_listener->notify("NoCard");
  }
}

void Board::edit_task(const std::string& task, const std::string& new_task) {
  try {
    task_list.edit(task, new_task);
    task_listener->notify(task_list.get());
  } catch (const NoCardException& e) {
    exception_listener->notify("NoCard");
  } catch (const ExistingCardException& e) {
    exception_listener->notify("ExistingCard");
  }
}

void Board::move_task(const std::string& task, unsigned int position) {
  try {
    task_list.move(task, position);
    task_listener->notify(task_list.get());
  } catch (const NoCardException& e) {
    exception_listener->notify("NoCard");
  } catch (const InvalidIndexException& e) {
    exception_listener->notify("InvalidIndex");
  }
}

void Board::add_meal(const Date& date, MealType type, const std::string& meal) {
  meal_list.add(date, type, meal);
  meal_listener->notify(meal_list.get());
}

void Board::erase_meal(const Date& date, MealType type) {
  try {
    meal_list.erase(date, type);
    meal_listener->notify(meal_list.get());
  } catch (const NoMealException& e) {
    exception_listener->notify("NoMeal");
  }
}

void Board::edit_meal(const Date& date, MealType type, const std::string& new_meal) {
  try {
    meal_list.edit(date, type, new_meal);
    meal_listener->notify(meal_list.get());
  } catch (const NoMealException& e) {
    exception_listener->notify("NoMeal");
  }
}

void Board::edit_meal(const Date& date, MealType type, const Date& new_date, MealType new_type) {
  try {
    meal_list.edit(date, type, new_date, new_type);
    meal_listener->notify(meal_list.get());
  } catch (const NoMealException& e) {
    exception_listener->notify("NoMeal");
  } catch (const ExistingMealException& e) {
    exception_listener->notify("ExistingMeal");
  }
}


} // end namespace First