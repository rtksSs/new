#ifndef TASK_H
#define TASK_H

#include <QDateTime>
#include <QListWidget>
#include <QStandardItem>

class Task : public QStandardItem
{
public:
    explicit Task(QString description);

    QString description() const;
    void setRemindTime(QDateTime& time);
    bool isCompleted() const;

private:
    QDateTime remind_time;

};

#endif // TASK_H
