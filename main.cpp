#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLocale>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("TextEditor");
    a.setApplicationVersion(QString("%1.%2").arg(MAJ_VERSION).arg(MIN_VERSION));
    QTranslator translator;
    translator.load(QString("%1/languages/QReader_%2").arg(QCoreApplication::applicationDirPath()).arg(QLocale::system().name()));
    a.installTranslator(&translator);
    MainWindow w;
    w.setWindowModified(false);
    w.show();
    return a.exec();
}
