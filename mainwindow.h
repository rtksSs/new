#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "notification.h"

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
#include <QSystemTrayIcon>
#include <QCloseEvent>

class Notification;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Notification notification;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    virtual void closeEvent(QCloseEvent *event) override;

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
