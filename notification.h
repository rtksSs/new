#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QMainWindow>
#include <QTimer>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QIcon>
#include <QPixmap>
#include <QApplication>

class MainWindow;

class Notification : public QObject
{
    Q_OBJECT

public:
    explicit Notification(MainWindow* window);
    ~Notification();

    bool isTrayIconVisible() const;

private:
    MainWindow*      main_window;
    QTimer*          timer;
    QSystemTrayIcon* tray_icon;
    QMenu*           context_menu;
    QIcon            icon;
    QPixmap          icon_img;

    void checkReminders();

private slots:
    void showContextMenu(QSystemTrayIcon::ActivationReason iReason) const;
    void showNotification(int index) const;
    void exitApplication() const;

};

#endif // NOTIFICATION_H
