#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.setWindowTitle(
        QApplication::translate("toplevel", "Recipe Planner"));
    return a.exec();
}
