#include "editdialog.h"
#include "ui_editdialog.h"

editDialog::editDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editDialog)
{
    this->setModal(true);
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

    emit saveEditedTask(editedTask, selectedRow);

    close();
}

void editDialog::on_editCancelButton_clicked()
{
    close();
}
