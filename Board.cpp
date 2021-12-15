#include "Board.hpp"

#include "Exception.hpp"


namespace First {


Board::Board(TaskListener* tl, MealListener* ml, ExceptionListener* el) :
    task_listener(tl), meal_listener(ml), exception_listener(el) {}

void Board::add_task(const std::string& task) {
  try {
    incompleted_task_list.add(task);
    notify_task_change();
  } catch (const ExistingTaskException& e) {
    exception_listener->notify("ExistingTask");
  }
}

void Board::erase_task(const std::string& task) {
  try {
    incompleted_task_list.erase(task);
    notify_task_change();
  } catch (const NoTaskException& e) {
    exception_listener->notify("NoTask");
  }
}

void Board::edit_task(const std::string& task, const std::string& new_task) {
  try {
    incompleted_task_list.edit(task, new_task);
    notify_task_change();
  } catch (const NoTaskException& e) {
    exception_listener->notify("NoTask");
  } catch (const ExistingTaskException& e) {
    exception_listener->notify("ExistingTask");
  }
}

void Board::move_task(const std::string& task, unsigned int position) {
  try {
    incompleted_task_list.move(task, position);
    notify_task_change();
  } catch (const NoTaskException& e) {
    exception_listener->notify("NoTask");
  } catch (const InvalidIndexException& e) {
    exception_listener->notify("InvalidIndex");
  }
}

void Board::complete_task(const std::string& task) {
  if (!incompleted_task_list.contains(task)) {
    exception_listener->notify("NoTask");
    return;
  }

  incompleted_task_list.erase(task);
  completed_task_list.add(task);

  notify_task_change();
}

void Board::incomplete_task(const std::string& task) {
  if (!completed_task_list.contains(task)) {
    exception_listener->notify("NoTask");
    return;
  }

  completed_task_list.erase(task);
  incompleted_task_list.add(task);

  notify_task_change();
}

void Board::clear_complete() {
  cleared_tasks = completed_task_list.to_string();
  completed_task_list.clear();
  notify_task_change();
}

void Board::undo_clear() {
  for (const auto& task : cleared_tasks) {
    completed_task_list.add(task);
  }

  notify_task_change();
}

void Board::add_meal(const Date& date, MealType type, const std::string& meal) {
  meal_list.add(date, type, meal);
  meal_listener->notify(meal_list.to_string());
}

void Board::erase_meal(const Date& date, MealType type) {
  try {
    meal_list.erase(date, type);
    meal_listener->notify(meal_list.to_string());
  } catch (const NoMealException& e) {
    exception_listener->notify("NoMeal");
  }
}

void Board::edit_meal(const Date& date, MealType type, const std::string& new_meal) {
  try {
    meal_list.edit(date, type, new_meal);
    meal_listener->notify(meal_list.to_string());
  } catch (const NoMealException& e) {
    exception_listener->notify("NoMeal");
  }
}

void Board::edit_meal(const Date& date, MealType type, const Date& new_date, MealType new_type) {
  try {
    meal_list.edit(date, type, new_date, new_type);
    meal_listener->notify(meal_list.to_string());
  } catch (const NoMealException& e) {
    exception_listener->notify("NoMeal");
  } catch (const ExistingMealException& e) {
    exception_listener->notify("ExistingMeal");
  }
}

void Board::notify_task_change() {
  std::vector<std::pair<std::string, std::string>> task_statuses;

  for (const auto& task : incompleted_task_list.to_string()) {
    task_statuses.push_back(std::make_pair(task, "Incomplete"));
  }

  for (const auto& task : completed_task_list.to_string()) {
    task_statuses.push_back(std::make_pair(task, "Complete"));
  }

  task_listener->notify(task_statuses);
}


} // end namespace First