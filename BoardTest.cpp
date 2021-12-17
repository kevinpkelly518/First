#include "doctest.h"

#include "Board.hpp"
#include "MealList.hpp"

#include <memory>


namespace {


class TaskListenerSpy : public First::TaskListener {
public:
  void notify(const First::TaskAddedEvent& t) override {
    task = t;
  }

  First::TaskAddedEvent task;
};

class MealListenerSpy : public First::MealListener {
public:
  void notify(const std::vector<std::vector<std::string>>& m) override {
    meals = m;
  }

  std::vector<std::vector<std::string>> meals;
};

class ExceptionListenerSpy : public First::ExceptionListener {
public:
  void notify(const std::string& k) override {
    key = k;
  }

  std::string key;
};

void check_task(First::TaskListener* listener, const First::TaskAddedEvent& expect) {
  CHECK(dynamic_cast<TaskListenerSpy*>(listener)->task == expect);
}

void check_meal(First::MealListener* listener, const std::vector<std::vector<std::string>>& expect) {
  CHECK(dynamic_cast<MealListenerSpy*>(listener)->meals == expect);
}

void check_exception(First::ExceptionListener* listener, const std::string& expect) {
  CHECK(dynamic_cast<ExceptionListenerSpy*>(listener)->key == expect);
}


} // end namespace


TEST_CASE("Board Tasks") {
  const auto task_listener = std::make_unique<TaskListenerSpy>();
  const auto meal_listener = std::make_unique<MealListenerSpy>();
  const auto exception_listener = std::make_unique<ExceptionListenerSpy>();

  First::Board board(task_listener.get(), meal_listener.get(), exception_listener.get());

  SUBCASE("Add Tasks") {
    board.add_task();
    check_task(task_listener.get(), {1, {{}, "New"}});

    board.add_task();
    check_task(task_listener.get(), {2, {{}, "New"}});

    board.add_task({2021, 12, 16});
    check_task(task_listener.get(), {3, {First::Date{2021, 12, 16}, "New"}});
  }

  // SUBCASE("Erase Tasks") {
  //   board.add_task();

  //   unsigned int id = task_listener->task.id;
  //   board.erase_task(id);

  //   check_task(task_listener.get(), {});
  // }

    // SUBCASE("Erase") {
    //   board.erase_task("Task");

    //   check_tasks(task_listener.get(), {});
    // }

    // SUBCASE("Edit") {
    //   board.edit_task("Task", "Edit");

    //   check_tasks(task_listener.get(), {std::make_pair("Edit", "Incomplete")});
    // }

    // SUBCASE("Move") {
    //   board.add_task("Task2");
    //   board.move_task("Task", 2);

    //   check_tasks(task_listener.get(), {std::make_pair("Task2", "Incomplete"), std::make_pair("Task", "Incomplete")});
    // }

    // SUBCASE("Complete") {
    //   board.complete_task("Task");

    //   check_tasks(task_listener.get(), {std::make_pair("Task", "Complete")});
    // }

    // SUBCASE("Incomplete") {
    //   board.complete_task("Task");
    //   board.incomplete_task("Task");

    //   check_tasks(task_listener.get(), {std::make_pair("Task", "Incomplete")});
    // }

    // SUBCASE("Clear Complete") {
    //   board.complete_task("Task");
    //   board.clear_complete();

    //   check_tasks(task_listener.get(), {});
    // }

    // SUBCASE("Undo Clear") {
    //   board.complete_task("Task");
    //   board.clear_complete();
    //   board.undo_clear();

    //   check_tasks(task_listener.get(), {std::make_pair("Task", "Complete")});
    // }
  // }

  SUBCASE("Meals") {
    board.add_meal({2021, 12, 16}, First::MealType::Breakfast, "Meal");

    check_meal(meal_listener.get(), {{"2021 12 16", "Breakfast", "Meal"}});

    SUBCASE("Erase") {
      board.erase_meal({2021, 12, 16}, First::MealType::Breakfast);

      check_meal(meal_listener.get(), {});
    }

    SUBCASE("Edit Meal") {
      board.edit_meal({2021, 12, 16}, First::MealType::Breakfast, "Cake");

      check_meal(meal_listener.get(), {{"2021 12 16", "Breakfast", "Cake"}});
    }

    SUBCASE("Edit Key") {
      board.edit_meal({2021, 12, 16}, First::MealType::Breakfast, {2021, 12, 17}, First::MealType::Lunch);

      check_meal(meal_listener.get(), {{"2021 12 17", "Lunch", "Meal"}});
    }
  }

  SUBCASE("Exceptions") {
    // SUBCASE("Add Task") {
    //   board.add_task("Task");
    //   board.add_task("Task");

    //   check_exception(exception_listener.get(), "ExistingTask");
    // }

    // SUBCASE("Erase Task") {
    //   board.erase_task("Task");

    //   check_exception(exception_listener.get(), "NoTask");
    // }

    // SUBCASE("Edit Nonexistent Task") {
    //   board.edit_task("Task", "Edit");

    //   check_exception(exception_listener.get(), "NoTask");
    // }

    // SUBCASE("Edit To Existing Task") {
    //   board.add_task("Task1");
    //   board.add_task("Task2");

    //   board.edit_task("Task1", "Task2");

    //   check_exception(exception_listener.get(), "ExistingTask");
    // }

    // SUBCASE("Move Nonexistent Task") {
    //   board.move_task("Task", 1);

    //   check_exception(exception_listener.get(), "NoTask");
    // }

    // SUBCASE("Move Task To Invalid Index") {
    //   board.add_task("Task");

    //   board.move_task("Task", 2);

    //   check_exception(exception_listener.get(), "InvalidIndex");
    // }

    // SUBCASE("Complete Task") {
    //   board.complete_task("Task");

    //   check_exception(exception_listener.get(), "NoTask");
    // }

    // SUBCASE("Incomplete Task") {
    //   board.incomplete_task("Task");

    //   check_exception(exception_listener.get(), "NoTask");
    // }

    SUBCASE("Erase Meal") {
      board.erase_meal({2021, 12, 16}, First::MealType::Breakfast);

      check_exception(exception_listener.get(), "NoMeal");
    }

    SUBCASE("Edit Meal") {
      board.edit_meal({2021, 12, 16}, First::MealType::Breakfast, "Meal");

      check_exception(exception_listener.get(), "NoMeal");
    }

    SUBCASE("Edit Meal Key") {
      board.edit_meal({2021, 12, 16}, First::MealType::Breakfast, {2021, 12, 16}, First::MealType::Lunch);

      check_exception(exception_listener.get(), "NoMeal");
    }

    SUBCASE("Edit To Existing Meal Type") {
      board.add_meal({2021, 12, 16}, First::MealType::Breakfast, "Meal1");
      board.add_meal({2021, 12, 16}, First::MealType::Lunch, "Meal2");

      board.edit_meal({2021, 12, 16}, First::MealType::Breakfast, {2021, 12, 16}, First::MealType::Lunch);

      check_exception(exception_listener.get(), "ExistingMeal");
    }

    SUBCASE("Edit Nonexistent Meal Date") {
      board.edit_meal({2021, 12, 16}, First::MealType::Breakfast, {2021, 12, 17}, First::MealType::Breakfast);

      check_exception(exception_listener.get(), "NoMeal");
    }

    SUBCASE("Edit To Existing Meal Date") {
      board.add_meal({2021, 12, 16}, First::MealType::Breakfast, "Meal1");
      board.add_meal({2021, 12, 17}, First::MealType::Breakfast, "Meal2");

      board.edit_meal({2021, 12, 16}, First::MealType::Breakfast, {2021, 12, 17}, First::MealType::Breakfast);

      check_exception(exception_listener.get(), "ExistingMeal");
    }
  }
}
