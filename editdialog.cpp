#include "editdialog.h"
#include "ui_editdialog.h"

editDialog::editDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editDialog)
{
    ui->setupUi(this);
    ui->selectedTaskLabel->setVisible(false);
}

editDialog::~editDialog()
{
    delete ui;
}

void editDialog::setTaskInfo(const Task &task, int selectedRow)
{
    ui->titleLineEdit->setText(task.getTitle());
    ui->descriptionLineEdit->setText(task.getDescription());
    ui->dateEdit->setDate(task.getDate());
    ui->selectedTaskLabel->setText(QString::number(selectedRow));

    qDebug() << "SetTaskInfo in editDialog";
}

void editDialog::on_editSaveButton_clicked()
{
    QString title = ui->titleLineEdit->text();
    QString description = ui->descriptionLineEdit->text();
    QDate date = ui->dateEdit->date();
    int selectedRow = ui->selectedTaskLabel->text().toInt();

    editedTask.setTitle(title);
    editedTask.setDescription(description);
    editedTask.setDate(date);

    emit saveTask(editedTask, selectedRow);
    qDebug() << "Save button clicked in editDialog";

    accept();
}

void editDialog::on_editCancelButton_clicked()
{
    reject();
}
