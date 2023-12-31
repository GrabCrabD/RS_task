#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDate>
#include <QDialog>

#include "task.h"

namespace Ui {
class editDialog;
}

class editDialog : public QDialog {
  Q_OBJECT

 public:
  explicit editDialog(QWidget *parent = nullptr);
  ~editDialog();

  void setTaskInfo(const Task &task, int selectedRow);

 signals:
  void saveEditedTask(Task &, int);

 private slots:
  void on_editSaveButton_clicked();
  void on_editCancelButton_clicked();

 private:
  Ui::editDialog *ui;
  Task editedTask;
};

#endif  // EDITDIALOG_H
