#ifndef TODOAPP_H
#define TODOAPP_H

#include <QMainWindow>
#include <QVector>
#include "task.h"
#include "editdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class toDoApp; }
QT_END_NAMESPACE

class toDoApp : public QMainWindow
{
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
//    void applyFilter();

public slots:
    void slotForm(Task &editedTask, int selectedRow);

private:
    Ui::toDoApp *ui;
    QVector<Task> taskList;
    editDialog dialogForm;
    QString filterTitle;
    QString filterDescription;
    QDate filterDate;
    bool filterCompleted;
};
#endif // TODOAPP_H
