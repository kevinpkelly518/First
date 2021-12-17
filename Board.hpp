#pragma once

#include "Date.hpp"
#include "List.hpp"
#include "MealList.hpp"

#include <memory>
#include <string>


namespace First {


// TODO is item needed?
struct TaskAddedEvent {
  unsigned int id;
  Item item;
};

bool operator==(const TaskAddedEvent& left, const TaskAddedEvent& right);

class TaskListener {
public:
  virtual ~TaskListener() = default;

  virtual void notify(const TaskAddedEvent& task_list) = 0;
};

class MealListener {
public:
  virtual ~MealListener() = default;

  virtual void notify(const std::vector<std::vector<std::string>>& meal_list) = 0;
};

class ExceptionListener {
public:
  virtual ~ExceptionListener() = default;

  virtual void notify(const std::string& key) = 0;
};

class Board {
public:
  Board(TaskListener*, MealListener*, ExceptionListener*);

  void add_task();
  void add_task(const Date& date);
  // void erase_task(const std::string& task);
  // void edit_task(const std::string& task, const std::string& new_task);
  // void move_task(const std::string& task, unsigned int position);
  // void complete_task(const std::string& task);
  // void incomplete_task(const std::string& task);
  // void clear_complete();
  // void undo_clear();

  void add_meal(const Date& date, MealType type, const std::string& meal);
  void erase_meal(const Date& date, MealType type);
  void edit_meal(const Date& date, MealType type, const std::string& new_meal);
  void edit_meal(const Date& date, MealType type, const Date& new_date, MealType new_type);

private:
  void notify_task_change();

  // TaskList incompleted_task_list;
  // TaskList completed_task_list;
  // std::vector<std::string> cleared_tasks;
  List task_list;

  MealList meal_list;

  TaskListener* task_listener;
  MealListener* meal_listener;
  ExceptionListener* exception_listener;

  static unsigned int current_id;
};


} // end namespace First