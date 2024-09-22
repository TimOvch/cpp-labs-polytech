#include "widgetcontainer.h"
#include "qstring.h"

WidgetContainer::WidgetContainer(QWidget *parent)
    : QWidget{parent}, layout(new QVBoxLayout(this))
{
    setLayout(layout);

}

void WidgetContainer::ConnectWidgets()
{
    int vecLen = widgets.length();

    for(int i = 0; i<vecLen; i++){
        for(int j = 0; j < vecLen; j++){
            QWidget *widget1 = widgets[i];
            QWidget *widget2 = widgets[j];

            const QMetaObject *meta1 = widget1->metaObject();
            const QMetaObject *meta2 = widget2->metaObject();

            if (QString(meta1->className()) == "QSlider" && QString(meta2->className()) == "QSpinBox") {
                connect(widget1, SIGNAL(valueChanged(int)), widget2, SLOT(setValue(int)));
            } else if (QString(meta1->className()) == "QSpinBox" && QString(meta2->className()) == "QSlider") {
                connect(widget1, SIGNAL(valueChanged(int)), widget2, SLOT(setValue(int)));
            } else if (QString(meta1->className()) == "QScrollBar" && QString(meta2->className()) == "QSlider") {
                connect(widget1, SIGNAL(valueChanged(int)), widget2, SLOT(setValue(int)));
            } else if (QString(meta1->className()) == "QSlider" && QString(meta2->className()) == "QScrollBar") {
                connect(widget1, SIGNAL(valueChanged(int)), widget2, SLOT(setValue(int)));
            } else if (QString(meta1->className()) == "QScrollBar" && QString(meta2->className()) == "QLabel") {
                connect(widget1, SIGNAL(valueChanged(int)), widget2, SLOT(setNum(int)));
            }



        }
    }
}

void WidgetContainer::AddWidget(QWidget *wid)
{
    widgets.append(wid);
    layout->addWidget(wid);
}
