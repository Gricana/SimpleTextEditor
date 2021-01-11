#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("TextEditor");
    a.setApplicationVersion(QString("%1.%2").arg(MAJ_VERSION).arg(MIN_VERSION));
    QTranslator translator;
    translator.load(QString(QString("%1/languages/QReader_ru").arg(QCoreApplication::applicationDirPath())));
    QCoreApplication::installTranslator(&translator);
    MainWindow w;
    w.show();
    return a.exec();
}
