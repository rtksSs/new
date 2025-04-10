#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QMainWindow>
#include <QTimer>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QIcon>
#include <QPixmap>
#include <QApplication>

class Notification : public QObject
{
    Q_OBJECT

public:
    explicit Notification();
    ~Notification();

    bool isTrayIconVisible() const;

private:
    QTimer*          timer;
    QSystemTrayIcon* tray_icon;
    QMenu*           context_menu;
    QIcon            icon;
    QPixmap          icon_img;

private slots:
    void showContextMenu(QSystemTrayIcon::ActivationReason iReason) const;
    void showNotification() const;
    void exitApplication() const;

signals:
    void requestShow();
    void requestExit();
};

#endif // NOTIFICATION_H
