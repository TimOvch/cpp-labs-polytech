#include "telephonebook.h"

#include <QApplication>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>
#include <QWidget>
#include <QHeaderView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setAttribute(Qt::AA_DontUseNativeMenuBar);

    TelephoneBook window;
    window.show();

    return a.exec();
}
