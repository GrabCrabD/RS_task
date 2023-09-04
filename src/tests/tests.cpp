#include "../task.h"
#include "../todoapp.h"
#include "gtest/gtest.h"

TEST(TaskListTest, AddTask) {
  QVector<Task> taskList;
  Task task;
  task.setTitle("Test Task");
  taskList.push_back(task);
  ASSERT_EQ(taskList.size(), 1);
  ASSERT_EQ(taskList[0].getTitle(), "Test Task");
}

TEST(TaskListTest, RemoveTask) {
  QVector<Task> taskList;
  Task task;
  task.setTitle("Test Task");
  taskList.push_back(task);
  taskList.remove(0);
  ASSERT_EQ(taskList.size(), 0);
}
