#ifndef TASK_H
#define TASK_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QDateTime>
#include <QListWidget>

class MainWindow;

class Task : public QMainWindow
{
    Q_OBJECT
public:
    explicit Task(QWidget *parent, const QListWidgetItem* task);
    ~Task();

    void setReminders(Task task);

private:
    QString   description;
    bool      is_completed;
    QDateTime remind_time;

signals:
};

#endif // TASK_H
