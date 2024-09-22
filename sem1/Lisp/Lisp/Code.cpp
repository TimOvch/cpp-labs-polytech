//
//  Reader.cpp
//  Lisp
//
//  Created by Тимофей Овчинников on 03.03.2024.
//

#include "Code.hpp"
#include "myString.h"

void READ(MyString& string){
    size_t bufSizeNow = defaultBufSz;
    char* buf = new char[bufSizeNow];
    int i = 0;
    for(;;){
        char ch;
        scanf("%c", &ch);
        if(ch == stopSymbol){
            break;
        }
        buf[i] = ch;
        i++;
        if(bufSizeNow-1 == i){
            char* newBuf = new char[bufSizeNow+bufSzDelta+1];
            strcpy(newBuf, buf);
            delete[] buf;
            buf = newBuf;
            bufSizeNow+=bufSzDelta;
        }
    }
    
    buf[i] = '\0';
    string.SetNewString(buf);
    delete[]buf;
}
