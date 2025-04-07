#include "notification.h"
//#include "mainwindow.h"

Notification::Notification()
    : icon_img(32, 32)
{
    // Заполнение изображения иконки цветом
    icon_img.fill(Qt::red);

    // Установка изображение на иконку
    icon.addPixmap(icon_img);

    // Инициализация иконки трея
    tray_icon = new QSystemTrayIcon(icon, this);
    tray_icon->setVisible(true);

    // Инициализация контекстного меню
    //context_menu = new QMenu();
    //context_menu->addAction("Show", this, &MainWindow::show);
    //context_menu->addAction("Exit", this, &Notification::exitApplication);

    // Установка и подключение контекстного меню
    //tray_icon->setContextMenu(context_menu);
    //connect(tray_icon, &QSystemTrayIcon::activated, this, &Notification::showContextMenu);

    // Инициализация таймера
    timer = new QTimer{this};
    // Подключение таймера (вывод уведомления по истечении времени таймера)
    //connect(timer, &QTimer::timeout, this, &Notification::showNotification);

    // Запуск таймера
    timer->start(10000);
}

Notification::~Notification()
{
}

bool Notification::isTrayIconVisible() const
{
    if (tray_icon->isVisible()) {
        return true;
    }

    return false;
}


void Notification::showContextMenu(QSystemTrayIcon::ActivationReason reason) const
{
    if (reason == QSystemTrayIcon::ActivationReason::DoubleClick) {
        context_menu->show();
    }
}

void Notification::showNotification() const
{
    tray_icon->showMessage("aaa", "aaa", QSystemTrayIcon::Information, 1000);
}

void Notification::exitApplication() const
{
    QApplication::exit();
}
