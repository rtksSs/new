#include "task.h"

Task::Task(QString description)
    : QStandardItem(description)
{
}

QString Task::description() const
{
    return data(Qt::DisplayRole).toString();
}

void Task::setRemindTime(QDateTime &time)
{

}

bool Task::isCompleted() const
{
    return checkState() == Qt::Checked;
}
