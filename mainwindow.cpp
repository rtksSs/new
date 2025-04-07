#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "task.h"
#include "dialog.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QApplication::setStyle("Fusion");

    // Инициализация полей
    ui->setupUi(this);
    tasks = new QStandardItemModel{this};
    ui->tasks_list->setModel(tasks);

    // Добавление задач
    connect(ui->add_button, &QPushButton::clicked, this, &MainWindow::addTask);
    connect(ui->task_input, &QLineEdit::returnPressed, this, &MainWindow::addTask);

    // Контеккстное меню при нажатии ПКМ на задачу
    ui->tasks_list->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tasks_list, &QWidget::customContextMenuRequested, this, &MainWindow::showContextMenu);

    // Установка модели для отображения в списке
    ui->tasks_list->setModel(tasks);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (notification.isTrayIconVisible())
    {
        event->ignore();
        hide();
    }
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
                                        });

    context_menu->addAction("Напоминание", this, &MainWindow::setTaskReminder);

    context_menu->popup(ui->tasks_list->mapToGlobal(pos));
}

void MainWindow::setTaskReminder()
{
    Dialog dialog;
    dialog.exec();
}
