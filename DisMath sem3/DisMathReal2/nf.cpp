#include "nf.h"

const QString func = "1111110111101001";
const QString x =    "0000000011111111";
const QString y =    "0000111100001111";
const QString z =    "0011001100110011";
const QString k =    "0101010101010101";

const QString NOT = "!";
const QString AND = "^";
const QString OR = "v";


void NormalForms::calculateForms(){
    for(int i = 0; i < func.length(); i++){
        if(func[i] == '1'){
            addSDNFTerm(i);
        } else{
            addSKNFTerm(i);
        }
    }
}

void NormalForms::addSKNFTerm(const int &ind){
    QString term;
    if(SKNF.length() > 0){
        SKNF.append(AND);
    }

    term.append("(");

    if (x[ind] == '0'){
        term.append("x");
    } else{
        term.append( NOT +"x");
    }

    if (y[ind] == '0'){
        term.append(OR + "y");
    } else{
        term.append(OR + NOT +"y");
    }

    if (z[ind] == '0'){
        term.append(OR + "z");
    } else{
        term.append(OR + NOT +"z");
    }

    if (k[ind] == '0'){
        term.append(OR + "k");
    } else{
        term.append(OR + NOT +"k");
    }
    term.append(")");
    SKNF.append(term);
}

void NormalForms::addSDNFTerm(const int &ind){
    QString term;
    if(SDNF.length() > 0){
        SDNF.append(OR);
    }

    if (x[ind] == '1'){
        term.append("x");
    } else{
        term.append( NOT +"x");
    }

    if (y[ind] == '1'){
        term.append(AND + "y");
    } else{
        term.append(AND + NOT +"y");
    }

    if (z[ind] == '1'){
        term.append(AND + "z");
    } else{
        term.append(AND + NOT +"z");
    }

    if (k[ind] == '1'){
        term.append(AND + "k");
    } else{
        term.append(AND + NOT +"k");
    }
    SDNF.append(term);
}

NormalForms::NormalForms(){
    calculateForms();
}

QString NormalForms::getSKNF(){
    return SKNF;
}

QString NormalForms::getSDNF(){
    return SDNF;
}

bool NormalForms::calulateBySDNF(const QString &num){
    QStringList terms = SDNF.split(OR);
    for (const QString& term : terms) {
        bool termValue = true;

        QStringList literals = term.split(AND);
        for (int i = 0; i < 4; i++) {
            bool numi;

            if(num[i] == '1'){
                numi = 1;
            } else {
                numi = 0;
            }

            if(literals[i][0] == '!'){
                numi = !numi;
            }
            termValue = termValue&&numi;
        }

        if(termValue) return true;
    }
    return false;
}
