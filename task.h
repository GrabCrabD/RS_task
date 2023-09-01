#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QDate>

class Task
{
public:
    Task();

    QString getTitle() const;
    void setTitle(const QString &title);

    QString getDescription() const;
    void setDescription(const QString &description);

    QDate getDate() const;
    void setDate(const QDate &date);

    bool isCompleted() const;
    void setCompleted(bool completed);

private:
    QString m_title;
    QString m_description;
    QDate m_date;
    bool m_isCompleted;
};

#endif // TASK_H
