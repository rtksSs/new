#include "dialog.h"
#include "ui_dialog.h"

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

}

void Dialog::on_cancel_button_clicked()
{
    Dialog::close();
}

