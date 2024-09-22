#ifndef WIDGETCONTAINER_H
#define WIDGETCONTAINER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QVector>
#include <QLabel>
#include <QSlider>
#include <QScrollBar>
#include <QSpinBox>
#include <QDebug>

class WidgetContainer : public QWidget
{
    Q_OBJECT

private:

    QVBoxLayout *layout;
    QVector<QWidget*> widgets;

public:
    WidgetContainer(QWidget *parent = nullptr);
    void ConnectWidgets();
    void AddWidget(QWidget* wid);

signals:
};

#endif // WIDGETCONTAINER_H
