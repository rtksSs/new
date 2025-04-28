#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "task.h"
#include "dialog.h"

#include <QMessageBox>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QJsonDocument>
#include <QInputDialog>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , notification(this)
    , is_changed(false)
{
    QApplication::setStyle("Fusion");

    // Инициализация полей
    ui->setupUi(this);
    tasks = new QStandardItemModel{this};
    ui->tasks_list->setModel(tasks);

    // Добавление задач
    connect(ui->add_button, &QPushButton::clicked, this, &MainWindow::addTask);
    connect(ui->task_input, &QLineEdit::returnPressed, this, &MainWindow::addTask);

    // Контекстное меню при нажатии ПКМ на задачу
    ui->tasks_list->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tasks_list, &QWidget::customContextMenuRequested, this, &MainWindow::showContextMenu);

    // Установка модели для отображения в списке
    ui->tasks_list->setModel(tasks);

    // Подключение сигнала изменения данных в модели
    connect(tasks, &QStandardItemModel::itemChanged, this, [this](QStandardItem* item) {
        if (item && dynamic_cast<Task*>(item)) {
            is_changed = true;
        }
    });

    // Загрузка задач при запуске
    loadTasks();

    // Заголовок окна
    setWindowTitle("To-Do List");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox reply;
    reply.setWindowTitle("Сохранить?");
    reply.setText("Сохранить задачи перед закрытием?");
    reply.setIcon(QMessageBox::Question);

    QPushButton* yes_button = reply.addButton("Да", QMessageBox::YesRole);
    QPushButton* no_button = reply.addButton("Нет", QMessageBox::NoRole);
    QPushButton* reject_button = reply.addButton("Отмена", QMessageBox::RejectRole);

    if (notification.isTrayIconVisible() && is_changed)
    {
        reply.exec();

        if (reply.clickedButton() == yes_button) {
            saveTasks();
            hide();
            event->ignore();
        }
        else if (reply.clickedButton() == no_button) {
            hide();
            event->ignore();
        }
        else if (reply.clickedButton() == reject_button) {
            event->ignore();
        }
    }
}

int MainWindow::tasksCount() const
{
    return tasks->rowCount();
}

QString MainWindow::getTaskDescription(int index)
{
    auto* task = dynamic_cast<Task*>(tasks->item(index));
    return task->description();
}

QStandardItemModel *MainWindow::getTasks() const
{
    return tasks;
}

void MainWindow::saveTasks()
{
    QJsonArray tasks_array;
    for (int index = 0; index < tasks->rowCount(); index++)
    {
        auto* task = dynamic_cast<Task*>(tasks->item(index));

        if (!task)
            continue;

        QJsonObject task_obj;

        task_obj["description"] = task->description();
        task_obj["is_completed"] = task->isCompleted();
        task_obj["remind_time"] = task->dateTime().toString(Qt::ISODate);
        task_obj["is_notified"] = task->isNotified();

        tasks_array.append(task_obj);
    }

    QFile file("tasks.json");
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Не удалось открыть файл для записи";
        return;
    }

    file.write(QJsonDocument(tasks_array).toJson());
    file.close();

    is_changed = false;
}

void MainWindow::loadTasks()
{
    QFile file("tasks.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Файл не найден или не может быть открыт";
        return;
    }

    QByteArray data = file.readAll();
    QJsonDocument document = QJsonDocument::fromJson(data);
    QJsonArray tasks_array = document.array();

    for (const QJsonValue& value : tasks_array) {
        QJsonObject task_obj = value.toObject();

        Task* task = new Task(task_obj["description"].toString());
        task->setCheckState(task_obj["is_completed"].toBool() ? Qt::Checked : Qt::Unchecked);

        QDateTime remind_time = QDateTime::fromString(task_obj["remind_time"].toString(), Qt::ISODate);
        if (remind_time.isValid()) {
            task->setRemindTime(remind_time);
        }

        task->setNotified(task_obj["is_notified"].toBool(), false);

        tasks->appendRow(task);
    }

    file.close();

    is_changed = false;
}

void MainWindow::addTask()
{
    QString task_description = ui->task_input->text();

    if (!task_description.isEmpty()) {
        Task* item = new Task(task_description);

        item->setCheckable(true);
        item->setCheckState(Qt::Unchecked);

        tasks->appendRow(item);

        ui->task_input->clear();
    }
    is_changed = true;
}

void MainWindow::showContextMenu(const QPoint& pos)
{
    QPersistentModelIndex index = ui->tasks_list->indexAt(pos);

    if (!index.isValid())
        return;

    QMenu* context_menu = new QMenu{this};

    context_menu->addAction("Удалить", this, [this, index]
                                        {
                                        tasks->removeRow(index.row());
                                        is_changed = true;
                                        });

    context_menu->addAction("Напоминание", this, [this, index]
                                        {
                                        Dialog dialog;

                                        if (dialog.exec() == QDialog::Accepted) {
                                            QDateTime remind_time = dialog.getRemindTime();

                                            if (remind_time < QDateTime::currentDateTime())
                                            {
                                                QMessageBox::warning(this, "Ошибка", "Нельзя установить напоминание в прошлом!");
                                                return;
                                            }

                                            auto* task = dynamic_cast<Task*>(tasks->item(index.row()));
                                            task->setRemindTime(remind_time);
                                            }

                                            dialog.close();
                                            is_changed = true;
                                        });

    context_menu->popup(ui->tasks_list->mapToGlobal(pos));
}

void MainWindow::on_save_action_triggered()
{
    saveTasks();
}


void MainWindow::on_delete_action_triggered()
{
    QMessageBox warning;

    warning.setWindowTitle("Внимание");
    warning.setText("Вы точно хотите удалить весь список задач?");
    warning.setIcon(QMessageBox::Question);

    QPushButton* yes_button = warning.addButton("Да", QMessageBox::YesRole);
    QPushButton* reject_button = warning.addButton("Отмена", QMessageBox::RejectRole);

    warning.exec();

    if (warning.clickedButton() == yes_button) {
        tasks->clear();
    }
    if (warning.clickedButton() == reject_button) {
        warning.close();
    }
}
