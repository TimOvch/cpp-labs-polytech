#ifndef NF_H
#define NF_H
#include <QString>
#include <QStringList>

class NormalForms{
    QString SDNF;
    QString SKNF;

    void calculateForms();

    void addSKNFTerm(const int& ind);

    void addSDNFTerm(const int& ind);

public:
    NormalForms();

    QString getSKNF();

    QString getSDNF();

    bool calulateBySDNF(const QString& num);
};

#endif // NF_H
