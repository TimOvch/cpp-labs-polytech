#include <QApplication>
#include "mywidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MyWidget wd;
    wd.show();

    return a.exec();
}
