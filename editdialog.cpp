#include "editdialog.h"
#include "ui_editdialog.h"

editDialog::editDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editDialog)
{
    ui->setupUi(this);
}

editDialog::~editDialog()
{
    delete ui;
}

void editDialog::setTaskInfo(const Task &task)
{
    ui->titleLineEdit->setText(task.getTitle());
    ui->descriptionLineEdit->setText(task.getDescription());
    ui->dateEdit->setDate(task.getDate());
}

void editDialog::on_editSaveButton_clicked()
{
    QString title = ui->titleLineEdit->text();
    QString description = ui->descriptionLineEdit->text();
    QDate date = ui->dateEdit->date();

    Task editedTask;
    editedTask.setTitle(title);
    editedTask.setDescription(description);
    editedTask.setDate(date);

    emit saveTask(editedTask);

    accept();
}

void editDialog::on_editCancelButton_clicked()
{
    reject();
}

void editDialog::on_pushButton_clicked()
{
    emit sig("sss");
}

