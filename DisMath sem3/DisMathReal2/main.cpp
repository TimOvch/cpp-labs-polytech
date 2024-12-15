#include "mainwindow.h"
#include "bdd.h"
#include "nf.h"
#include "polynom.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    BDD bdd;

    QString bin;
    NormalForms nf;
    Polynom pol;

    for(int i = 0; i <16; i++){
        bin = QString::number(i,2);

        while(bin.length() < 4){
            bin.prepend('0');
        }

        bool res = bdd.getResult(bin);
        bool sdnf = nf.calulateBySDNF(bin);
        bool polynom = pol.getRes(bin);

        qDebug() <<bin <<": " <<res  << sdnf << polynom << '\n';
    }

    qDebug() << nf.getSDNF() << '\n' << nf.getSKNF();


    QApplication a(argc, argv);
    MainWindow mn;
    mn.show();
    return a.exec();
}
