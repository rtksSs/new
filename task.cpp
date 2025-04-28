#include "task.h"

Task::Task(QString description)
    : QStandardItem(description)
    , remind_time(QDateTime())
{
    is_notified = false;
    setCheckable(true);

}

QString Task::description() const
{
    return data(Qt::DisplayRole).toString();
}

QDateTime Task::dateTime() const
{
    if (remind_time.isValid()) {
        return remind_time;
    }

    return QDateTime();
}

void Task::setRemindTime(QDateTime &time)
{
    remind_time = time;
}

bool Task::isCompleted() const
{
    return checkState() == Qt::Checked;
}

bool Task::isNotified() const
{
    return is_notified;
}

void Task::setNotified(bool notif, bool save_to_file)
{
    this->is_notified = notif;
    if (save_to_file) {
        emit emitDataChanged();
    }
}

