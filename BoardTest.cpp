#include "doctest.h"

#include "Board.hpp"

#include <memory>


namespace {


class ExceptionListenerSpy : public First::ExceptionListener {
public:
  void notify(const std::string& k) override {
    key = k;
  }

  std::string key;
};

class BoardChangeListenerSpy : public First::BoardChangeListener {
public:
  void notify(const std::vector<std::string>& b) override {
    board = b;
  }

  std::vector<std::string> board;
};

void check_board(First::BoardChangeListener* listener, const std::vector<std::string>& expect) {
  CHECK(dynamic_cast<BoardChangeListenerSpy*>(listener)->board == expect);
}

void check_exception(First::ExceptionListener* listener, const std::string& expect) {
  CHECK(dynamic_cast<ExceptionListenerSpy*>(listener)->key == expect);
}


} // end namespace


TEST_CASE("Board") {
  First::Board board;

  const auto board_change_listener = std::make_unique<BoardChangeListenerSpy>();
  board.register_board_change_listener(board_change_listener.get());

  const auto exception_listener = std::make_unique<ExceptionListenerSpy>();
  board.register_exception_listener(exception_listener.get());

  SUBCASE("Add") {
    board.add_task("Task");

    check_board(board_change_listener.get(), {"Task"});

    SUBCASE("Erase") {
      board.erase_task("Task");

      check_board(board_change_listener.get(), {});
    }

    SUBCASE("Edit") {
      board.edit_task("Task", "Edit");

      check_board(board_change_listener.get(), {"Edit"});
    }

    SUBCASE("Move") {
      board.add_task("Task2");
      board.move_task("Task", 2);

      check_board(board_change_listener.get(), {"Task2", "Task"});
    }
  }

  SUBCASE("Exceptions") {
    SUBCASE("Add") {
      board.add_task("Task");
      board.add_task("Task");

      check_exception(exception_listener.get(), "ExistingCard");
    }

    SUBCASE("Erase") {
      board.erase_task("Task");

      check_exception(exception_listener.get(), "NoCard");
    }

    SUBCASE("Edit") {
      board.edit_task("Task", "Edit");

      check_exception(exception_listener.get(), "NoCard");
    }

    SUBCASE("Edit") {
      board.add_task("Task1");
      board.add_task("Task2");

      board.edit_task("Task1", "Task2");

      check_exception(exception_listener.get(), "ExistingCard");
    }

    SUBCASE("Move") {
      board.move_task("Task", 1);

      check_exception(exception_listener.get(), "NoCard");
    }

    SUBCASE("Move") {
      board.add_task("Task");

      board.move_task("Task", 2);

      check_exception(exception_listener.get(), "InvalidIndex");
    }
  }
}
