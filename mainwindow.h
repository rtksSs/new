#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "notification.h"

#include <QMainWindow>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    virtual void        closeEvent(QCloseEvent* event) override;
    int                 tasksCount() const;
    QString             getTaskDescription(int index);
    QStandardItemModel* getTasks() const;

private:
    Ui::MainWindow*     ui;

    Notification        notification;
    QStandardItemModel* tasks;
    bool                is_changed;

public slots:
    void                saveTasks();
    void                loadTasks();

private slots:
    void                addTask();
    void                showContextMenu(const QPoint& pos);

    void                on_save_action_triggered();
    void                on_delete_action_triggered();
};
#endif // MAINWINDOW_H
