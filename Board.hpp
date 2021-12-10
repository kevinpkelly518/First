#pragma once

#include "TaskList.hpp"

#include <memory>
#include <string>


namespace First {


class ExceptionListener {
public:
  virtual ~ExceptionListener() = default;

  virtual void notify(const std::string& key) = 0;
};

class BoardChangeListener {
public:
  virtual ~BoardChangeListener() = default;

  virtual void notify(const std::vector<std::string>& task_list) = 0;
};

class Board {
public:
  void register_board_change_listener(BoardChangeListener* listener);
  void register_exception_listener(ExceptionListener* listener);

  void add_task(const std::string& task);
  void erase_task(const std::string& task);
  void edit_task(const std::string& task, const std::string& new_task);
  void move_task(const std::string& task, unsigned int position);

private:
  TaskList task_list;
  BoardChangeListener* board_change_listener;
  ExceptionListener* exception_listener;
};


} // end namespace First