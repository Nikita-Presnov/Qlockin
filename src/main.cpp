#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    LockinAPP window;
    window.show();

    return app.exec();
}
