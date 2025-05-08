#include "mainwindow.h"
#include "dictionary.h"
#include "redblacktree.h"
#include <QDebug>
#include <QApplication>
#include "hashtable.h"
#include <QTest>
#include "encoding.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.resize(600, 400);
    window.show();

    return app.exec();
}
