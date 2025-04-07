#include "dialog.h"
#include "ui_dialog.h"
#include "task.h"

#include <QMessageBox>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    // Часы
    ui->hours_spin_box->setRange(0, 23);
    ui->hours_spin_box->setValue(QTime::currentTime().hour());
    ui->hours_spin_box->setAlignment(Qt::AlignCenter);

    // Минуты
    ui->minutes_spin_box->setRange(0, 59);
    ui->minutes_spin_box->setValue(QTime::currentTime().minute());
    ui->minutes_spin_box->setAlignment(Qt::AlignCenter);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_apply_button_clicked()
{
    QDateTime remind_time(
        ui->calendar->selectedDate(), QTime(ui->hours_spin_box->value(), ui->minutes_spin_box->value()));

    if (remind_time < QDateTime::currentDateTime()) {
        QMessageBox::warning(this, "Ошибка", "Установите корректное время");
        return;
    }


}

void Dialog::on_cancel_button_clicked()
{
    Dialog::close();
}

