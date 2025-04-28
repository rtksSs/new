#include "mainwindow.h"

#include <QApplication>
#include <QIcon>
#include <QFileInfo>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QIcon icon("icon.png");
    a.setWindowIcon(icon);

    a.setApplicationName("To-Do List");

    MainWindow w;
    w.show();
    return a.exec();
}
