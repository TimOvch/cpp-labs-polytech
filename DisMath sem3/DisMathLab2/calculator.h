#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QObject>
#include <QWidget>

#include <QLineEdit>
#include <QComboBox>
#include <QString>
#include <QMap>
#include <QLabel>
#include <QChar>

class Calculator : public QWidget
{
    Q_OBJECT

    QLineEdit *input1;
    QLineEdit *input2;
    QComboBox *operationCombo;
    QLabel *resultLabel;

public slots:
    void checkInput();

    void calculate();

public:
    explicit Calculator(QWidget *parent = nullptr);
};

#endif
