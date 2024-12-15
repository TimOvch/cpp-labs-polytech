#include "calculator.h"
#include "symbolnumber.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QChar>
#include <QFrame>

Calculator::Calculator(QWidget *parent)
    : QWidget{parent}
{
    setWindowTitle("Калькулятор большой конечной арифметики");

    input1 = new QLineEdit(this);
    input1->setPlaceholderText("a");
    input2 = new QLineEdit(this);
    input2->setPlaceholderText("a");
    operationCombo = new QComboBox(this);
    QPushButton *calculateButton = new QPushButton("Рассчитать", this);
    resultLabel = new QLabel("Результат: ", this);
    QLabel* mapText = new QLabel("Порядок символов (для проверки):\na:0 , b:1 , e:2 , c:3 , g:4 , f:5 , h:6 , d:7");
    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    operationCombo->addItem("+");
    operationCombo->addItem("-");
    operationCombo->addItem("*");
    operationCombo->addItem("/");
    operationCombo->addItem("^");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *inputLayout = new QHBoxLayout();
    inputLayout->addWidget(input1);
    inputLayout->addWidget(operationCombo);
    inputLayout->addWidget(input2);

    mainLayout->addLayout(inputLayout);
    mainLayout->addWidget(calculateButton);
    mainLayout->addWidget(resultLabel);
    mainLayout->addWidget(line);
    mainLayout->addWidget(mapText);

    connect(calculateButton, &QPushButton::clicked, this, &Calculator::calculate);
    connect(input1, &QLineEdit::textChanged, this, &Calculator::checkInput);
    connect(input2, &QLineEdit::textChanged, this, &Calculator::checkInput);
}

void Calculator::checkInput()
{
    QString numbers = "abcdefhg";

    QString in1 = input1->text().remove(' ');
    input1->setText(in1);
    QString in2 = input2->text().remove(' ');
    input2->setText(in2);

    if(in1.length() > 0){
        if((in1[0]!='-'&&in1.length() > 8) || (in1[0]=='-'&&in1.length() > 9)){
            QMessageBox::warning(this, "Ошибка", "Левый операнд выходит за границы допустимых значений:\n [-dddddddd; dddddddd]");
            in1.removeLast();
            input1->setText(in1);
            return;
        }
    }

    if(in2.length()>0){
        if((in2[0]!='-'&&in2.length() > 8) || (in2[0]=='-'&&in2.length() > 9)){
            QMessageBox::warning(this, "Ошибка", "Правый операнд выходит за границы допустимых значений:\n [-dddddddd; dddddddd]");
            in2.removeLast();
            input2->setText(in2);
            return;
        }
    }
    for(int i = 0; i < in1.length(); i++){
        if(!numbers.contains(in1[i])){
            if(i==0&&in1[i]==QChar('-')) continue;
            QString errorText("Недопустимый символ {");
            errorText.append(in1[i]);
            errorText.append("} в левом операнде.\nСписок допустимых: a,b,c,d,e,h,g,f,- (если в начале).");
            QMessageBox::warning(this, "Ошибка", errorText);
            input1->setText(in1.remove(i,1));
        }
    }

    for(int i = 0; i < in2.length(); i++){
        if(!numbers.contains(in2[i])){
            if(i==0&&in2[i]==QChar('-')) continue;
            QString errorText("Недопустимый символ {");
            errorText.append(in2[i]);
            errorText.append("} в правом операнде.\nСписок допустимых: a,b,c,d,e,h,g,f,- (если в начале).");
            QMessageBox::warning(this, "Ошибка", errorText);
            input2->setText(in2.remove(i,1));
        }
    }
}

void Calculator::calculate()
{
    QString left = input1->text();
    QString right = input2->text();

    SymbolNumber symbNum1(left);
    SymbolNumber symbNum2(right);

    SymbolNumber symbRes;
    SymbolNumber remainder;

    QString operation = operationCombo->currentText();

    if (operation == "+") {
        symbRes = symbNum1+symbNum2;
    } else if (operation == "-") {
        symbRes = symbNum1-symbNum2;
    } else if (operation == "*") {
        symbRes = symbNum1*symbNum2;
    } else if (operation == "/") {
        symbRes = symbNum1 / symbNum2;
        remainder = symbNum1.rem(symbNum2);
        if(symbRes.getNum() != "∅" && symbRes.getNum() != "[-dddddddd; dddddddd]"){
            resultLabel->setText("Результат: " + symbRes.getNum() + '\n' + "Остаток: " + remainder.getNum());
        } else {
            resultLabel->setText("Результат: " + symbRes.getNum());
        }
        return;
    } else if (operation == "^") {
        symbRes = symbNum1.pow(symbNum2);
    } else {
        QMessageBox::warning(this, "Ошибка", "Выберите операцию!");
        return;
    }

    if((symbRes.getNum()[0]!='-'&&symbRes.getNum().length() > 8)
        || (symbRes.getNum()[0]=='-'&&symbRes.getNum().length() > 9)){
        QMessageBox::warning(this, "Ошибка", "Результат операции выходит за границы допустимых значений:\n [-dddddddd; dddddddd]");
        return;
    }


    resultLabel->setText("Результат: " + symbRes.getNum());
}
