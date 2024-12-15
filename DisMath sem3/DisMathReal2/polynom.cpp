#include "polynom.h"

const QString f = "1111110111101001";
const QString x = "0000000011111111";
const QString y = "0000111100001111";
const QString z = "0011001100110011";
const QString k = "0101010101010101";

const QString NOT = "!";
const QString AND = "^";
const QString OR = "v";


Polynom::Polynom(){
    koefs.append(f[0]);

    QString tmp1 = f;
    QString tmp2;

    for(int i = 1; i <f.length(); i++){
        for(int j = 0; j < tmp1.length()-1; j++){
            bool first = 0;
            bool second = 0;

            if(tmp1[j] == '1') first = 1;
            if(tmp1[j+1] == '1') second = 1;

            tmp2.append(QString::number((first+second)%2));
        }

        koefs.append(tmp2[0]);
        tmp1 = tmp2;
        tmp2.clear();
    }

    countPol();
}

bool Polynom::getRes(const QString &num){
    bool res = 0;

    QStringList terms = pol.split('+');

    for(QString term:terms){
        bool termRes = 1;

        QStringList lits = term.split(AND);

        for(QString lit:lits){
            if(lit == "1"){
                termRes = 1;
                break;
            }

            if(lit == "x"){
                termRes = termRes&& (num[0]=='1');
            }

            if(lit == "y"){
                termRes = termRes&& (num[1]=='1');
            }

            if(lit == "z"){
                termRes = termRes&& (num[2]=='1');
            }

            if(lit == "k"){
                termRes = termRes&& (num[3]=='1');
            }
        }
        res = (res+termRes)%2;
    }

    return res;
}

QString Polynom::getPol(){
    return pol;
}

void Polynom::countPol(){
    if(koefs[0] == '1'){
        pol.append("1");
    }

    for(int i = 1; i <koefs.length(); i++){
        if(koefs[i] == '1'){
            QString temp;
            if(koefs.length()>0) pol.append('+');
            if(x[i] == '1'){
                temp.append("x");
            }

            if(y[i] == '1'){
                if(temp.length() >0) temp.append(AND);
                temp.append("y");
            }

            if(z[i] == '1'){
                if(temp.length() >0) temp.append(AND);
                temp.append("z");
            }

            if(k[i] == '1'){
                if(temp.length() >0) temp.append(AND);
                temp.append("k");
            }

            pol.append(temp);
        }
    }
}
