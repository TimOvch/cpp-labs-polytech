#include "widgetcontainer.h"
#include "qstring.h"

WidgetContainer::WidgetContainer(QWidget *parent)
    : QWidget{parent}, layout(new QVBoxLayout(this))
{
    setLayout(layout);

}

void WidgetContainer::ConnectWidgets()
{
    int widLen = widgets.length();

    for(int i = 0; i<widLen-1; i++){
        QWidget *widget1 = widgets[i];
        QWidget *widget2 = widgets[i+1];

        connect(widget1, SIGNAL(valueChanged(int)), widget2, SLOT(setValue(int)));
        connect(widget2, SIGNAL(valueChanged(int)), widget1, SLOT(setValue(int)));

    }

    if(widLen!= 0){
        int labLen = labels.length();

        for(int i = 0; i< labLen; i++){
            QWidget *label = labels[i];
            connect(widgets[0], SIGNAL(valueChanged(int)), label, SLOT(setNum(int)));
        }
    }

}

void WidgetContainer::AddWidget(QWidget *wid)
{
    const QMetaObject *meta = wid->metaObject();
    if(QString(meta->className()) == QString("QLabel")){
        labels.append(wid);
    } else {
        widgets.append(wid);
    }
    widgets.append(wid);
    layout->addWidget(wid);
}

