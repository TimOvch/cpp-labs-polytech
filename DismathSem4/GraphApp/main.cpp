#include "matrix.h"
#include "QDebug"
#include <QApplication>
#include "graphapp.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    GraphApp window;
    window.show();
    return app.exec();
}
