#include "todoapp.h"
#include "./ui_todoapp.h"
#include <QTableWidget>
#include <QDateTime>
#include <QColor>
#include <QDebug>
#include <QSettings>
#include <QButtonGroup>

toDoApp::toDoApp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::toDoApp)
{
    ui->setupUi(this);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QDate currentDate = QDate::currentDate();
    ui->deadlineDate->setDate(currentDate);
    ui->dateSortFilter->setDate(currentDate);

    QButtonGroup *progressStatusGroup = new QButtonGroup(this);
    progressStatusGroup->addButton(ui->inProgressTasksFilter);  // 2
    progressStatusGroup->addButton(ui->doneTasksFilter);        // 1
    progressStatusGroup->addButton(ui->allTasksFilter);         // 0

    ui->editButton->setEnabled(false);
    ui->deleteButton->setEnabled(false);
    ui->changeStatusButton->setEnabled(false);

    connect(ui->tableWidget, &QTableWidget::itemSelectionChanged, this, &toDoApp::handleRowSelectionChange);
    connect(&dialogForm, &editDialog::saveEditedTask, this, &toDoApp::getEditedTask);

    loadTasks();
    refreshTasks();
}

toDoApp::~toDoApp()
{
    saveTasks();
    delete ui;
}

void toDoApp::refreshTasks() {
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(taskList.size());

    for (int row = 0; row < taskList.size(); ++row) {
        Task& task = taskList[row];

        QTableWidgetItem *titleItem = new QTableWidgetItem(task.getTitle());
        QTableWidgetItem *descripItem = new QTableWidgetItem(task.getDescription());
        QTableWidgetItem *dateItem = new QTableWidgetItem(task.getDate().toString("dd.MM.yyyy"));

        QLabel *statusLabel = new QLabel();
        if (task.isCompleted()) {
            statusLabel->setText("Done");
            statusLabel->setStyleSheet("color: green;");
        } else {
            statusLabel->setText("In progress");
        }

        ui->tableWidget->setItem(row, 0, titleItem);
        ui->tableWidget->setItem(row, 1, descripItem);
        ui->tableWidget->setItem(row, 2, dateItem);
        ui->tableWidget->setCellWidget(row, 3, statusLabel);
    }
}

void toDoApp::on_addButton_clicked() {
    QString taskTitle = ui->addTaskLine->text();
    QString taskDescrip = ui->addDescripLine->text();
    QDate taskDeadline = ui->deadlineDate->date();

    if (!taskTitle.isEmpty()) {
        Task newTask;
        newTask.setTitle(taskTitle);
        newTask.setDescription(taskDescrip);
        newTask.setDate(taskDeadline);
        newTask.setCompleted(false);

        taskList.append(newTask);

        refreshTasks();

        ui->addTaskLine->clear();
        ui->addDescripLine->clear();
        ui->addTaskLine->setFocus();
    }
}

void toDoApp::on_deleteButton_clicked() {
    int selectedRow = ui->tableWidget->currentRow();

    if (selectedRow >= 0 && selectedRow < ui->tableWidget->rowCount()) {
        ui->tableWidget->removeRow(selectedRow);
        taskList.removeAt(selectedRow);
    }
}

void toDoApp::on_changeStatusButton_clicked() {
    int selectedRow = ui->tableWidget->currentRow();

    if (selectedRow >= 0 && selectedRow < ui->tableWidget->rowCount()) {
        Task &task = taskList[selectedRow];
        task.setCompleted(!task.isCompleted());

        refreshTasks();

        ui->editButton->setEnabled(false);
        ui->deleteButton->setEnabled(false);
        ui->changeStatusButton->setEnabled(false);
    }
}

void toDoApp::on_editButton_clicked() {

    int selectedRow = ui->tableWidget->currentRow();

    if (selectedRow >= 0 && selectedRow < ui->tableWidget->rowCount()) {
        Task &task = taskList[selectedRow];

        dialogForm.setTaskInfo(task, selectedRow);
        dialogForm.exec();

        ui->editButton->setEnabled(false);
        ui->deleteButton->setEnabled(false);
        ui->changeStatusButton->setEnabled(false);
    }
}

void toDoApp::getEditedTask(Task &editedTask, int selectedRow) {

    Task &task = taskList[selectedRow];
    task.setTitle(editedTask.getTitle());
    task.setDescription(editedTask.getDescription());
    task.setDate(editedTask.getDate());

    refreshTasks();
}

// активация клавиш изменения состояния только при выделении строки с таском
void toDoApp::handleRowSelectionChange() {
    int selectedRow = ui->tableWidget->currentRow();
    if (selectedRow >= 0 && selectedRow < ui->tableWidget->rowCount()) {
        ui->editButton->setEnabled(true);
        ui->deleteButton->setEnabled(true);
        ui->changeStatusButton->setEnabled(true);
    } else {
        ui->editButton->setEnabled(false);
        ui->deleteButton->setEnabled(false);
        ui->changeStatusButton->setEnabled(false);
    }
}

// сохранение и загрузка с использованием QSettings
void toDoApp::saveTasks() {
    QSettings settings("RS", "toDoList");
    settings.beginWriteArray("tasks");

    for (int i = 0; i < taskList.size(); ++i) {
        settings.setArrayIndex(i);
        const Task& task = taskList.at(i);
        settings.setValue("title", task.getTitle());
        settings.setValue("description", task.getDescription());
        settings.setValue("date", task.getDate().toString("dd.MM.yyyy"));
        settings.setValue("completed", task.isCompleted());
    }

    settings.endArray();
}

void toDoApp::loadTasks() {
    QSettings settings("RS", "toDoList");
    int size = settings.beginReadArray("tasks");

    taskList.clear();

    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        Task task;
        task.setTitle(settings.value("title").toString());
        task.setDescription(settings.value("description").toString());
        task.setDate(QDate::fromString(settings.value("date").toString(), "dd.MM.yyyy"));
        task.setCompleted(settings.value("completed").toBool());
        taskList.append(task);
    }

    settings.endArray();
}

void toDoApp::applyFilter() {
    QList<Task> filteredTasks;

    for (Task &task : taskList) {
        bool passFilter = true;

        if (!filterTitle.isEmpty() && !task.getTitle().contains(filterTitle)) {
            passFilter = false;
        }

        if (!filterDescription.isEmpty() && !task.getDescription().contains(filterDescription)) {
            passFilter = false;
        }

        if (filterDate.isValid() && task.getDate() > filterDate) {
            passFilter = false;
        }

        if (filterCompleted == 1 && !task.isCompleted()) {
            passFilter = false;
        }

        if (filterCompleted == 2 && task.isCompleted()) {
            passFilter = false;
        }

        if (passFilter) {
            filteredTasks.append(task);
        }

        updateTaskTable(filteredTasks);
    }
}

void toDoApp::updateTaskTable(QList<Task> filteredTasks) {
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(filteredTasks.size());

    for (int row = 0; row < filteredTasks.size(); ++row) {
        Task& task = filteredTasks[row];

        QTableWidgetItem *titleItem = new QTableWidgetItem(task.getTitle());
        QTableWidgetItem *descripItem = new QTableWidgetItem(task.getDescription());
        QTableWidgetItem *dateItem = new QTableWidgetItem(task.getDate().toString("dd.MM.yyyy"));

        QLabel *statusLabel = new QLabel();
        if (task.isCompleted()) {
            statusLabel->setText("Done");
            statusLabel->setStyleSheet("color: green;");
        } else {
            statusLabel->setText("In progress");
        }

        ui->tableWidget->setItem(row, 0, titleItem);
        ui->tableWidget->setItem(row, 1, descripItem);
        ui->tableWidget->setItem(row, 2, dateItem);
        ui->tableWidget->setCellWidget(row, 3, statusLabel);
    }
}

void toDoApp::on_applyFilterButton_clicked() {
    filterTitle = ui->filterTitleLine->text();
    filterDescription = ui->filterDescriptionLine->text();
    filterDate = ui->dateSortFilter->date();

    if (ui->inProgressTasksFilter->isChecked()) {
        filterCompleted = 2;
    } else if (ui->doneTasksFilter->isChecked()) {
        filterCompleted = 1;
    } else {
        filterCompleted = 0;
    }

    applyFilter();
}


void toDoApp::on_resetFilterButton_clicked()
{
    refreshTasks();
    ui->allTasksFilter->setChecked(true);
    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
}


void toDoApp::on_tabWidget_currentChanged(int index)
{
    if (index == 1) {
        ui->editButton->setEnabled(false);
        ui->deleteButton->setEnabled(false);
        ui->changeStatusButton->setEnabled(false);
        ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);

    } else {
        ui->editButton->setEnabled(true);
        ui->deleteButton->setEnabled(true);
        ui->changeStatusButton->setEnabled(true);
        ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    }
}

