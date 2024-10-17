#include <QApplication>
#include <iostream>
#include "widgetcontainer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    WidgetContainer collection;

    QSlider *slider = new QSlider(Qt::Horizontal);
    QSpinBox *spinBox = new QSpinBox();
    QScrollBar *scrollBar = new QScrollBar(Qt::Horizontal);
    QLabel *label = new QLabel("Dynamic Widgets");

    collection.AddWidget(scrollBar);
    collection.AddWidget(slider);
    collection.AddWidget(label);
    collection.AddWidget(slider);
    collection.AddWidget(spinBox);

    collection.ConnectWidgets();

    collection.setWindowTitle("Dynamic Widget Collection");
    collection.resize(400, 300);
    collection.show();

    return a.exec();
}
