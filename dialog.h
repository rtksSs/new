#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_apply_button_clicked();
    void on_cancel_button_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
