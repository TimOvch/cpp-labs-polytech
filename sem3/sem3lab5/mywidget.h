#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QtWidgets>

class MyWidget : public QWidget
{
    Q_OBJECT

    QLabel* lbl;
    QPushButton* exitB;
    QWidget* inner1;
    QWidget* inner2;
public:
    explicit MyWidget(QWidget *parent = nullptr);
};

#endif // MYWIDGET_H
