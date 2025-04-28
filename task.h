#ifndef TASK_H
#define TASK_H

#include <QDateTime>
#include <QListWidget>
#include <QStandardItem>

class Task : public QStandardItem
{
public:
    explicit Task(QString description);

    QString   description() const;
    QDateTime dateTime() const;
    void      setRemindTime(QDateTime& time);
    bool      isCompleted() const;
    bool      isNotified() const;
    void      setNotified(bool notif, bool save_to_file = true);

private:
    QDateTime remind_time;
    bool      is_notified;

};

#endif // TASK_H
