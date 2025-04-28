#include "notification.h"
#include "mainwindow.h"
#include "task.h"

Notification::Notification(MainWindow* window)
    : main_window(window)
    , icon_img(32, 32)
{
    // Загрузка изображения
    icon_img.load("icon.png");

    // Установка изображение на иконку
    icon.addPixmap(icon_img);

    // Инициализация иконки трея
    tray_icon = new QSystemTrayIcon(icon, this);
    tray_icon->setVisible(true);

    // Инициализация контекстного меню
    context_menu = new QMenu();
    context_menu->addAction("Открыть", this, [window]
                                        {
                                        window->show();
                                        });
    context_menu->addAction("Выйти", this, &Notification::exitApplication);

    // Установка и подключение контекстного меню
    tray_icon->setContextMenu(context_menu);
    connect(tray_icon, &QSystemTrayIcon::activated, this, &Notification::showContextMenu);

    // Инициализация таймера
    timer = new QTimer{this};

    // Подключение таймера (проверка всех задач раз в 1 сек.)
    connect(timer, &QTimer::timeout, this, &Notification::checkReminders);

    // Запуск таймера
    timer->start(1000);
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

void Notification::checkReminders()
{
    for (int index = 0; index < main_window->tasksCount(); index++)
    {
        auto* task = dynamic_cast<Task*>(main_window->getTasks()->item(index));

        if (!task)
            continue;

        if (!task->dateTime().isValid())
            continue;

        if (task->dateTime() <= QDateTime::currentDateTime() && !task->isNotified()) {
            showNotification(index);
            task->setNotified(true);
        }
    }
}


void Notification::showContextMenu(QSystemTrayIcon::ActivationReason reason) const
{
    if (reason == QSystemTrayIcon::ActivationReason::DoubleClick) {
        context_menu->show();
    }

    else if (reason == QSystemTrayIcon::ActivationReason::Context) {
        context_menu->show();
    }
}

void Notification::showNotification(int index) const
{

    tray_icon->showMessage("Напоминание", main_window->getTaskDescription(index), QSystemTrayIcon::Information, 5000);

    connect(tray_icon, &QSystemTrayIcon::messageClicked, this, [this]()
                                                            {
                                                                main_window->show();
                                                            }, Qt::SingleShotConnection);
}

void Notification::exitApplication() const
{
    QApplication::exit();
}

