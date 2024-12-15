#ifndef POLYNOM_H
#define POLYNOM_H

#include <QVector>
#include <QString>
#include <QStringList>

class Polynom
{
    QString pol;
    QString koefs;

    void countPol();

public:
    Polynom();

    bool getRes(const QString& num);

    QString getPol();
};

#endif // POLYNOM_H
