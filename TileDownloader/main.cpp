﻿#include <QApplication>
#include <QtDebug>
#include <QMainWindow>
#include <QPushButton>

#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qApp->setOrganizationName("atos");
    qApp->setApplicationName("MapGraphics TileDownloader");

    MainWindow w;
    w.show();

    return a.exec();
}
