#include "dialog.h"
#include "ui_dialog.h"

#include <QMessageBox>
#include <QStyleFactory>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    ui->calendar->setStyleSheet(
        "QTableView { selection-background-color: transparent; }"
        "QTableView::item:hover { background: transparent; border: none; }"
        "QTableView::item:selected { background: transparent; }"
        );

    // Часы
    ui->hours_spin_box->setRange(0, 23);
    ui->hours_spin_box->setValue(QTime::currentTime().hour());
    ui->hours_spin_box->setAlignment(Qt::AlignCenter);

    // Минуты
    ui->minutes_spin_box->setRange(0, 59);
    ui->minutes_spin_box->setValue(QTime::currentTime().minute());
    ui->minutes_spin_box->setAlignment(Qt::AlignCenter);

    connect(ui->button_box, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->button_box, &QDialogButtonBox::rejected, this, &QDialog::reject);


}

Dialog::~Dialog()
{
    delete ui;
}

QDateTime Dialog::getRemindTime() const
{
    QDateTime remind_time(
        ui->calendar->selectedDate(), QTime(ui->hours_spin_box->value(), ui->minutes_spin_box->value()));

    return remind_time;
}

