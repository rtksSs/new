#include "task.h"

Task::Task(QWidget *parent, const QListWidgetItem* task)
    : QMainWindow(parent)
{
    parent = nullptr;

    if (task) {
        description = task->text();
        is_completed = task->checkState();
    }
}

Task::~Task()
{

}
