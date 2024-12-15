#ifndef SYMBOLNUMBER_H
#define SYMBOLNUMBER_H

#include <QString>

class SymbolNumber
{
    QString number;

    QString sum(const QString& l, const QString& r) ;
    QString sub(const QString& l, const QString& r) ;
    QString mul(const QString& l, const QString& r) ;
    QString divPoloj(const QString& l, const QString& r) ;
    QString divOtric(const QString& l, const QString& r) ;
public:
    SymbolNumber();
    SymbolNumber(const QString& num);

    const QString getNum() const;
    SymbolNumber pow(const SymbolNumber& another) ;
    SymbolNumber rem(SymbolNumber& another) ;

    SymbolNumber operator+(const SymbolNumber& another) ;
    SymbolNumber operator-(const SymbolNumber& another) ;
    SymbolNumber operator*(const SymbolNumber& another) ;
    SymbolNumber operator/(const SymbolNumber& another) ;

};

#endif // SYMBOLNUMBER_H
