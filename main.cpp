#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("TextEditor");
    a.setApplicationVersion(QString("%1.%2").arg(MAJ_VERSION).arg(MIN_VERSION));
    MainWindow w;
    w.show();
    return a.exec();
}
