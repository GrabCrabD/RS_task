#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>
#include <QDate>
#include "task.h"

namespace Ui {
class editDialog;
}

class editDialog : public QDialog
{
    Q_OBJECT

public:
    explicit editDialog(QWidget *parent = nullptr);
    ~editDialog();

    void setTaskInfo(const Task &task);

signals:
    void saveTask(const Task &);
    void sig(QString);

private slots:
    void on_editSaveButton_clicked();
    void on_editCancelButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::editDialog *ui;
};

#endif // EDITDIALOG_H
