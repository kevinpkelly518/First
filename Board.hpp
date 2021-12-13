#pragma once

#include "Date.hpp"
#include "MealList.hpp"
#include "TaskList.hpp"

#include <memory>
#include <string>


namespace First {


class TaskListener {
public:
  virtual ~TaskListener() = default;

  virtual void notify(const std::vector<std::string>& task_list) = 0;
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

  void add_task(const std::string& task);
  void erase_task(const std::string& task);
  void edit_task(const std::string& task, const std::string& new_task);
  void move_task(const std::string& task, unsigned int position);

  void add_meal(const Date& date, MealType type, const std::string& meal);
  void erase_meal(const Date& date, MealType type);
  void edit_meal(const Date& date, MealType type, const std::string& new_meal);
  void edit_meal(const Date& date, MealType type, const Date& new_date, MealType new_type);

private:
  TaskList task_list;
  MealList meal_list;
  TaskListener* task_listener;
  MealListener* meal_listener;
  ExceptionListener* exception_listener;
};


} // end namespace First