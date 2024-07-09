#include "lockinapplite.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    LockinAPPlite window;
    window.show();

    return app.exec();
}
