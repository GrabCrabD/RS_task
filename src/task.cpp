#include "task.h"

Task::Task() : m_isCompleted(false) {}

QString Task::getTitle() const { return m_title; }

void Task::setTitle(const QString &title) { m_title = title; }

QString Task::getDescription() const { return m_description; }

void Task::setDescription(const QString &description) {
  m_description = description;
}

QDate Task::getDate() const { return m_date; }

void Task::setDate(const QDate &date) { m_date = date; }

bool Task::isCompleted() const { return m_isCompleted; }

void Task::setCompleted(bool completed) { m_isCompleted = completed; }
