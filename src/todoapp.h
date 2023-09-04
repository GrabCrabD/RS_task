#ifndef TODOAPP_H
#define TODOAPP_H

#include <QMainWindow>
#include <QVector>

#include "editdialog.h"
#include "task.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class toDoApp;
}
QT_END_NAMESPACE

class toDoApp : public QMainWindow {
  Q_OBJECT

 public:
  toDoApp(QWidget *parent = nullptr);
  ~toDoApp();

 private slots:
  void on_addButton_clicked();

  void on_deleteButton_clicked();

  void on_changeStatusButton_clicked();

  void on_editButton_clicked();

  void handleRowSelectionChange();

  void refreshTasks();
  void saveTasks();
  void loadTasks();
  void applyFilter();
  void updateTaskTable(QList<Task> filteredTasks);

  void on_applyFilterButton_clicked();

  void on_resetFilterButton_clicked();

  void on_tabWidget_currentChanged(int index);

 public slots:
  void getEditedTask(Task &editedTask, int selectedRow);

 private:
  Ui::toDoApp *ui;
  QVector<Task> taskList;
  editDialog dialogForm;

  QString filterTitle;
  QString filterDescription;
  QDate filterDate;
  int filterCompleted;
};
#endif  // TODOAPP_H
