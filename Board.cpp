#include "Board.hpp"

#include "Exception.hpp"


namespace First {


void Board::register_board_change_listener(BoardChangeListener* listener) {
  board_change_listener = listener;
}

void Board::register_exception_listener(ExceptionListener* listener) {
  exception_listener = listener;
}

void Board::add_task(const std::string& task) {
  try {
    task_list.add(task);
    board_change_listener->notify(task_list.get());
  } catch (const ExistingCardException& e) {
    exception_listener->notify("ExistingCard");
  }
}

void Board::erase_task(const std::string& task) {
  try {
    task_list.erase(task);
    board_change_listener->notify(task_list.get());
  } catch (const NoCardException& e) {
    exception_listener->notify("NoCard");
  }
}

void Board::edit_task(const std::string& task, const std::string& new_task) {
  try {
    task_list.edit(task, new_task);
    board_change_listener->notify(task_list.get());
  } catch (const NoCardException& e) {
    exception_listener->notify("NoCard");
  } catch (const ExistingCardException& e) {
    exception_listener->notify("ExistingCard");
  }
}

void Board::move_task(const std::string& task, unsigned int position) {
  try {
    task_list.move(task, position);
    board_change_listener->notify(task_list.get());
  } catch (const NoCardException& e) {
    exception_listener->notify("NoCard");
  } catch (const InvalidIndexException& e) {
    exception_listener->notify("InvalidIndex");
  }
}


} // end namespace First