#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "task.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Добавление задач
    connect(ui->add_button, &QPushButton::clicked, this, &MainWindow::addTask);
    connect(ui->task_input, &QLineEdit::returnPressed, this, &MainWindow::addTask);

    // Контеккстное меню при нажатии ПКМ на задачу
    ui->tasks_list->setContextMenuPolicy(Qt::CustomContextMenu);
    // connect(ui->tasks_list, &QListWidget::customContextMenuRequested, this, &MainWindow::showContextMenu);
    connect(ui->tasks_list, &QListView::doubleClicked, this, &MainWindow::showContextMenu);

    // Установка модели для отображения в списке
    ui->tasks_list->setModel(&tasks);
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
        auto* item = new Task(task_description);

        item->setCheckable(true);
        item->setCheckState(Qt::Unchecked);

        tasks.appendRow(item);

        ui->task_input->clear();
    }
}

void MainWindow::showContextMenu(const QModelIndex& index)
{
    Task* task = dynamic_cast<Task*>(tasks.item(index.row()));

    QMessageBox::about(this, "gavno", task->description());

    // QStandardItem* item = ui->tasks_list->currentItem();
    // if(!item) return;

    // QMenu context_menu;

    // QAction* remind_action = context_menu.addAction("Напоминание");
    // connect(remind_action, &QAction::triggered, this, &MainWindow::setTaskReminder);
}

void MainWindow::setTaskReminder()
{
//     QListWidgetItem* item = ui->tasks_list->currentItem();
//     if(!item) return;

//     QDialog dialog(this);
//     dialog.setWindowTitle("Установить напоминание");
//     dialog.setFixedSize(400, 350);

//     // Стиль для спинбоксов с маленькими кнопками
//     QString spinBoxStyle = R"(
//         QSpinBox {
//             font-size: 24px;
//             min-width: 60px;
//             max-width: 60px;
//             min-height: 50px;
//             max-height: 50px;
//             padding: 0;
//             text-align: center;
//         }
//         QSpinBox::up-button, QSpinBox::down-button {
//             width: 20px;
//             height: 24px;
//         }
//         QSpinBox::up-button {
//             subcontrol-position: top right;
//         }
//         QSpinBox::down-button {
//             subcontrol-position: bottom right;
//         }
//     )";

//     // Основной контейнер
//     QWidget* timeContainer = new QWidget(&dialog);
//     QHBoxLayout* timeLayout = new QHBoxLayout(timeContainer);
//     timeLayout->setSpacing(5);
//     timeLayout->setContentsMargins(20, 10, 20, 10);

//     // Часы
//     QSpinBox* hoursSpin = new QSpinBox(timeContainer);
//     hoursSpin->setStyleSheet(spinBoxStyle);
//     hoursSpin->setRange(0, 23);
//     hoursSpin->setValue(QTime::currentTime().hour());
//     hoursSpin->setAlignment(Qt::AlignCenter);

//     // Двоеточие
//     QLabel* colon = new QLabel(":", timeContainer);
//     colon->setStyleSheet("font-size: 24px;");
//     colon->setAlignment(Qt::AlignCenter);

//     // Минуты
//     QSpinBox* minsSpin = new QSpinBox(timeContainer);
//     minsSpin->setStyleSheet(spinBoxStyle);
//     minsSpin->setRange(0, 59);
//     minsSpin->setValue(QTime::currentTime().minute());
//     minsSpin->setAlignment(Qt::AlignCenter);

//     // Добавляем элементы
//     timeLayout->addStretch();
//     timeLayout->addWidget(hoursSpin);
//     timeLayout->addWidget(colon);
//     timeLayout->addWidget(minsSpin);
//     timeLayout->addStretch();

//     // Календарь
//     QCalendarWidget* calendar = new QCalendarWidget(&dialog);

//     calendar->setStyleSheet(R"(
//     QCalendarWidget QComboBox {
//         font-size: 18px;
//         font-weight: bold;
//         min-width: 120px;
//         height: 30px;
//     }

//     QCalendarWidget QAbstractItemView {
//         font-size: 14px;
//     }

//     QCalendarWidget QToolButton {
//         font-size: 16px;
//         min-width: 40px;
//         min-height: 40px;
//     }
// )");

//     calendar->setGridVisible(true);
//     calendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
//     calendar->setHorizontalHeaderFormat(QCalendarWidget::ShortDayNames);
//     calendar->setFirstDayOfWeek(Qt::Monday);
//     calendar->setMinimumDate(QDate::currentDate());

//     // Подсветка выходных
//     QTextCharFormat weekendFormat;
//     weekendFormat.setForeground(Qt::red);
//     calendar->setWeekdayTextFormat(Qt::Saturday, weekendFormat);
//     calendar->setWeekdayTextFormat(Qt::Sunday, weekendFormat);

//     // Кнопки управления
//     QDialogButtonBox* buttonBox = new QDialogButtonBox(
//         QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
//         Qt::Horizontal,
//         &dialog
//         );

//     // Главный layout
//     QVBoxLayout* mainLayout = new QVBoxLayout(&dialog);
//     mainLayout->addWidget(new QLabel("Выберите время:", &dialog));
//     mainLayout->addWidget(timeContainer);
//     mainLayout->addWidget(calendar);
//     mainLayout->addWidget(buttonBox);

//     connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
//     connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
}
