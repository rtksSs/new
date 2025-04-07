#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "notification.h"

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include <QListWidget>
#include <QList>
#include <QMenu>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QCalendarWidget>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QStandardItemModel>
#include <QDialog>
#include <QMessageBox>

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

    virtual void closeEvent(QCloseEvent* event) override;

    QListWidgetItem getTask() const;

private:
    Ui::MainWindow* ui;

    Notification        notification;
    QStandardItemModel* tasks;

private slots:
    void addTask();
    void showContextMenu(const QPoint& pos);
    void setTaskReminder();

};
#endif // MAINWINDOW_H
