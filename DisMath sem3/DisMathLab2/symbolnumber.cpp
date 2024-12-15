#include "symbolnumber.h"

#include <QVector>
#include <QHash>
#include <QChar>

QHash<QChar,int> rowCol = {{'a', 0},
                          {'b', 1},
                          {'c', 2},
                          {'d', 3},
                          {'e', 4},
                          {'f', 5},
                          {'g', 6},
                          {'h', 7}};

QHash<int,QChar> rowSymb = {{0, 'a'},
                            {1, 'b'},
                            {2, 'c'},
                            {3, 'd'},
                            {4, 'e'},
                            {5, 'f'},
                            {6, 'g'},
                            {7, 'h'}};

QHash<QChar,int> poradok = {{'a', 0},
                            {'b', 1},
                            {'e', 2},
                            {'c', 3},
                            {'g', 4},
                            {'f', 5},
                            {'h', 6},
                            {'d', 7}};


QVector<QVector<QChar>> SumTable = {{'a','b','c','d','e','f','g','h'},
                                  {'b','e','g','a','c','h','f','d'},
                                  {'c','g','h','e','f','a','d','b'},
                                  {'d','a','e','h','b','g','c','f'},
                                  {'e','c','f','b','g','d','h','a'},
                                  {'f','h','a','g','d','e','b','c'},
                                  {'g','f','d','c','h','b','a','e'},
                                  {'h','d','b','f','a','c','e','g'}};

QVector<QVector<QChar>> MulTable = {{'a','a','a','a','a','a','a','a'},
                                  {'a','b','c','d','e','f','g','h'},
                                  {'a','c','b','f','h','d','g','e'},
                                  {'a','d','f','b','h','c','g','e'},
                                  {'a','e','h','h','g','e','a','g'},
                                  {'a','f','d','c','e','b','g','h'},
                                  {'a','g','g','g','a','g','a','a'},
                                  {'a','h','e','e','g','h','a','g'}};

QVector<QVector<QChar>> SumSTable={{'a','a','a','a','a','a','a','a'},
                                  {'a','a','a','b','a','a','a','a'},
                                  {'a','a','a','b','a','b','a','b'},
                                  {'a','b','b','b','b','b','b','b'},
                                  {'a','a','a','b','a','a','a','b'},
                                  {'a','a','b','b','a','b','b','b'},
                                  {'a','a','a','b','a','b','b','b'},
                                  {'a','a','b','b','b','b','b','b'}};

QVector<QVector<QChar>> MulSTable = {{'a','a','a','a','a','a','a','a'},
                                   {'a','a','a','a','a','a','a','a'},
                                   {'a','a','b','e','a','b','b','e'},
                                   {'a','a','e','h','b','g','c','f'},
                                   {'a','a','a','b','a','b','b','b'},
                                   {'a','a','b','g','b','c','e','g'},
                                   {'a','a','b','c','b','e','e','c'},
                                   {'a','a','e','f','b','g','c','g'}};


QChar sumResult(const QChar& left, const QChar& right){
    return SumTable[rowCol[left]][rowCol[right]];
}

QChar sumSResult(const QChar& left, const QChar& right){
    return SumSTable[rowCol[left]][rowCol[right]];
}

bool checkLess(const QString& left, const QString& right){
    if (left.length() < right.length()) {
        return true;
    }
    if (left.length() > right.length()) {
        return false;
    }

    for (int i = 0; i < left.length(); i++) {
        if (poradok[left[i]] < poradok[right[i]]) {
            return true;
        } else if (poradok[left[i]] > poradok[right[i]]) {
            return false;
        }
    }

    return false;
}

QChar subResult(const QChar& left, const QChar& right){
    return rowSymb[SumTable[rowCol[right]].indexOf(left)];
}

QChar mulResult(const QChar& left, const QChar& right){
    return MulTable[rowCol[left]][rowCol[right]];
}

QChar mulSResult(const QChar& left, const QChar& right){
    return MulSTable[rowCol[left]][rowCol[right]];
}

bool chetnoe(const QString& l){
    int last = l.length()-1;
    return (l[last] == 'a') || (l[last] == 'e') || (l[last] == 'g') || (l[last] == 'h');
}

QString SymbolNumber::sum(const QString& l, const QString& r)
{
    QString result;
    QChar ostatok = 'a';

    int lenTh = l.length(), lenAn = r.length();

    while(lenTh-1 >= 0 || lenAn-1 >= 0){
        QChar leftOperand = (lenTh > 0) ? l[lenTh-1] : 'a';
        QChar rightOperand = (lenAn > 0) ? r[lenAn-1] : 'a';

        QChar bezOstatka = sumResult(leftOperand, rightOperand);

        result.prepend(sumResult(ostatok, bezOstatka));

        ostatok = sumSResult(ostatok, bezOstatka);
        ostatok = sumResult(ostatok,  sumSResult(leftOperand, rightOperand));

        lenAn--;
        lenTh--;
    }

    if(ostatok!='a') result.prepend(ostatok);

    while(result[0] == 'a' && result.length() > 1){
        result.removeFirst();
    }

    return result;
}

QString SymbolNumber::sub(const QString& l, const QString& r)
{
    QString result;
    QString left = l;
    QString right = r;

    bool zaim = 0, otric = 0;

    int lenTh = left.length(), lenAn = right.length();

    if(lenTh < lenAn || (lenTh==lenAn && checkLess(l, r))){
        otric = 1;
        left = r;
        right = l;
        lenTh = lenAn;
        lenAn = l.length();
    }

    while(lenTh-1 >= 0 || lenAn-1 >= 0){
        QChar leftOperand = (lenTh > 0) ? left[lenTh-1] : 'a';
        QChar rightOperand = (lenAn > 0) ? right[lenAn-1] : 'a';
        QChar newOperand;

        if(zaim){
            newOperand = subResult(leftOperand, 'b');
        } else{
            newOperand = leftOperand;
        }

        if(checkLess(leftOperand, rightOperand)){
            zaim = 1;
        } else {
            zaim = 0;
        }

        result.prepend(subResult(newOperand, rightOperand));

        lenAn--;
        lenTh--;
    }

    while(result[0] == 'a'&& result.length() > 1){
        result.removeFirst();
    }

    if(otric) result.prepend('-');

    return result;
}

QString SymbolNumber::mul(const QString &l, const QString &r)
{
    QString result = "a";

    int lenTh = l.length(), lenAn = r.length();

    for (int i = lenAn-1; i >= 0; i--){
        QString temp;
        QChar ost = 'a', leftOperand = r[i], bezOst, rightOperand;
        for(int j = lenTh-1; j >= 0; j--){
            rightOperand = l[j];
            bezOst = mulResult(leftOperand, rightOperand);

            temp.prepend(sumResult(bezOst, ost));

            ost = sumSResult(bezOst, ost);
            ost = sumResult(ost, mulSResult(leftOperand, rightOperand));
        }
        if(ost!='a') temp.prepend(ost);
        temp.append(QString((lenAn-i-1),'a'));
        result = sum(result, temp);
    }

    return result;
}

QString SymbolNumber::divPoloj(const QString &l, const QString &r)
{
    if(l == "a") return "a";

    QString mnojitel = "a";

    QString resUmnoj = r;

    while(checkLess(resUmnoj, l)){
        mnojitel = sum(mnojitel, "b");
        resUmnoj = sum(resUmnoj, r);
    }

    if(resUmnoj == l) mnojitel = sum(mnojitel, "b");

    return mnojitel;
}

QString SymbolNumber::divOtric(const QString &l, const QString &r)
{
    if(l == "a") return "a";

    QString mnojitel = "a";

    QString resUmnoj = r;

    while(checkLess(resUmnoj, l)){
        mnojitel = sum(mnojitel, "b");
        resUmnoj = sum(resUmnoj, r);
    }

    mnojitel = sum(mnojitel, "b");

    if(checkLess(resUmnoj, l)) mnojitel = sum(mnojitel, "b");

    return mnojitel;
}

SymbolNumber::SymbolNumber() {
    number = QString("a");
}

SymbolNumber::SymbolNumber(const QString &num)
{
    number = num;

    if(number.length() == 0) number = "a";

    if(num[0] == '-'){
        while(number.length() > 2 && number[1] == 'a'){
            number.remove(1,1);
        }
    } else {
        while(number.length() > 1 && number[0] == 'a'){
            number.removeFirst();
        }
    }

    if(number == "-a") number = "a";
}

const QString SymbolNumber::getNum() const
{
    return number;
}

SymbolNumber SymbolNumber::pow(const SymbolNumber &another)
{
    QString l = number, r = another.number;

    if(another.getNum()[0] == '-'){
        return QString("a");
    }

    if(r == "a"){
        return QString("b");
    } else if (r == "b"){
        return l;
    }

    QString stepen = "e";

    QString resStepen = mul(l,l);

    while(checkLess(stepen, r)){
        stepen = sum(stepen, "b");
        resStepen = mul(resStepen, l);

        if(resStepen.length() > 9) break;
    }

    if((l[0] == '-') && !chetnoe(r)) resStepen.prepend('-');

    return resStepen;
}

SymbolNumber SymbolNumber::rem(SymbolNumber &another)
{
    SymbolNumber temp (*this/another);
    QString result;

    result = (*this - (another*temp)).getNum();

    return result;
}

SymbolNumber SymbolNumber::operator+(const SymbolNumber &another)
{
    QString left = number, right = another.number;

    if(left[0] == '-' && right[0] == '-'){
        left.removeFirst();
        right.removeFirst();
        return sum(left,right).prepend('-');
    } else if(left[0] == '-'){
        left.removeFirst();
        return sub(right, left);
    } else if(right[0] == '-'){
        right.removeFirst();
        return sub(left, right);
    }

    return sum(left,right);
}

SymbolNumber SymbolNumber::operator-(const SymbolNumber &another)
{
    QString left = number, right = another.number;

    if(left[0] == '-' && right[0] == '-'){
        left.removeFirst();
        right.removeFirst();
        return sub(right,left);
    } else if(left[0] == '-'){
        left.removeFirst();
        return sum(left,right).prepend('-');
    } else if(right[0] == '-'){
        right.removeFirst();
        return sum(left, right);
    }

    return sub(left, right);
}

SymbolNumber SymbolNumber::operator*(const SymbolNumber &another)
{
    QString left = number, right = another.number;

    if(left[0] == '-' && right[0] == '-'){
        left.removeFirst();
        right.removeFirst();
        return mul(left,right);
    } else if(left[0] == '-'){
        left.removeFirst();
        return mul(right, left).prepend('-');
    } else if(right[0] == '-'){
        right.removeFirst();
        return mul(left, right).prepend('-');
    }

    return mul(number, another.number);
}

SymbolNumber SymbolNumber::operator/(const SymbolNumber &another)
{

    QString left = number, right = another.number;

    if(left == "a" && right == "a"){
        return SymbolNumber("[-dddddddd; dddddddd]");
    } else if(right == "a"){
        return SymbolNumber("∅");
    }

    if(left[0] == '-' && right[0] == '-'){
        left.removeFirst();
        right.removeFirst();
        return divPoloj(left,right);
    } else if(left[0] == '-'){
        left.removeFirst();
        return divOtric(left, right).prepend('-');
    } else if(right[0] == '-'){
        right.removeFirst();
        return divOtric(left, right).prepend('-');
    }
    return divPoloj(left, right);
}
