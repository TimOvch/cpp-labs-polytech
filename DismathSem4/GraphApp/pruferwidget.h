#ifndef PRUFERWIDGET_H
#define PRUFERWIDGET_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <graphview.h>
#include <QString>
#include <QStringList>
#include <QRegularExpression>
#include <QVector>
#include <QMessageBox>

bool isValidPruferCodeVector(const QVector<int> &code);

class PruferWidget : public QDialog {
    Q_OBJECT

    GraphView *graphView;
    QLineEdit *pruferCodeLine;
    QLineEdit *pruferWeightsLine;

public:
    PruferWidget(QWidget *parent = nullptr) : QDialog(parent) {
        graphView = new GraphView(this);
        graphView->setMinimumSize(600,500);

        pruferCodeLine = new QLineEdit;
        pruferWeightsLine = new QLineEdit;
        QPushButton *button = new QPushButton("Отобразить");
        connect(button, &QPushButton::pressed, this, &PruferWidget::redrawTree);

        QVBoxLayout *rightLayout = new QVBoxLayout;
        rightLayout->addWidget(pruferCodeLine);
        rightLayout->addWidget(pruferWeightsLine);
        rightLayout->addWidget(button);

        QHBoxLayout *mainLayout = new QHBoxLayout(this);
        mainLayout->addWidget(graphView);
        mainLayout->addLayout(rightLayout);

        setLayout(mainLayout);
        setWindowTitle("Генерация дерева по коду Прюфера");
        resize(900, 500);
    }

public slots:

    void redrawTree(){
        QString prufStr = pruferCodeLine->text();
        QString weightsStr = pruferWeightsLine->text();

        QStringList weightsElems = weightsStr.split(',', Qt::SkipEmptyParts);
        QStringList prufElems = prufStr.split(',', Qt::SkipEmptyParts);

        QVector<int> prufersCode(0),weights(0);

        for(const QString& elem : prufElems){
            bool ok = 1;
            prufersCode.append(elem.toInt(&ok));
            if(!ok){
                QMessageBox::warning(this, "Ошибка", "Вы ввели символ отличный от числа!");
                return;
            }
        }

        for(const QString& elem : weightsElems){
            bool ok = 1;
            weights.append(elem.toInt(&ok));
            if(!ok){
                QMessageBox::warning(this, "Ошибка", "Вы ввели символ отличный от числа!");
                return;
            }
        }


        if(!isValidPruferCodeVector(prufersCode)){
            QMessageBox::warning(this, "Ошибка", "Код Прюфера недействителен!");
            return;
        }

        if(prufersCode.size() != weights.size()){
            QMessageBox::warning(this, "Ошибка", "Размер кода Прюфера не соответствует размеру весов!");
            return;
        }

        graphView->setTreeFromPrufer(prufersCode,weights);
        update();
    }
};

#endif // PRUFERWIDGET_H
