#include "Helping.h"
//Вспомогательные функции
void strCopy(char*& from, char*& to){
    int i = 0;
    
    while(from[i]!='\0'){
        to[i] = from[i];
        i++;
    }
    
    to[i]='\0';
}

void strCut(char* str){
    int len = 0;
    while(str[len]!='\0'){
        len++;
    }
    char* cutStr = new char[len+1];
    strCopy(str, cutStr);
    delete[] str;
    str = cutStr;
}

int MyStrCmp(const char*a,const char*b){
    //создаём флаг на случай равенства строк
    bool equal = 1;

    //создаем такой флаг, что в случае если a > b он будет равен 1, если нет 0
    bool aBolb = 0;
    
    //проходимся по значениям каждой строки и сравниваем
    int i = 0;
    while(true){
        if(a[i]==b[i]){ //случай равности
            if(a[i]=='\0'){//выход из цикла для равности
                break;
            }
            i++;
            continue;
        } else if((int(a[i]) > int(b[i])) || (b[i] == '\0')){ //случай a>b
            aBolb = 1;
            equal = 0;
            break;
        } else if((int(a[i]) < int(b[i])) || (a[i] == '\0')){ //случай b>a
            equal = 0;
            break;
        }
        i++;
    }

    //проверяем по флагам и возвращаем нужное значение
    if(equal){
        return 0;
    } else if(aBolb){
        return 1;
    } else{
        return -1;
    }
}
