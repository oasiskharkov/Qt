#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    MainWindow w(translator);
    a.installTranslator(&translator);
    w.show();
    return a.exec();
}
