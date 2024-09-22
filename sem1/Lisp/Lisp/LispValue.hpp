//
//  Types.hpp
//  Lisp
//
//  Created by Тимофей Овчинников on 01.03.2024.
//

#ifndef Types_hpp
#define Types_hpp

#include <stdio.h>
#include "myString.h"

class LispValue;

enum DataTypes{
    Int,
    String,
    List,
    Function
};

struct LispInt{
    int number;
};

struct LispString{
    MyString string;
};

struct LispList{
    LispList* next;
    LispValue* val;
    unsigned int refCount;
};

struct LispFunc{
    //SomeType* additionData;
    //Функция для освобождения служебных данных
    LispValue* (*function)(const LispValue* mas, size_t sz, void* additionData);
};

class LispValue{
private:
    DataTypes type;
    union {
        LispInt lspInt;
        LispString lspString;
        LispList lspList;
        LispFunc lspFunc;
    } Data;
    unsigned int refCount;
    
public:
    LispValue(LispInt const & a);
    LispValue(LispString const & a);
    LispValue(MyString const & a);
};

#endif /* Types_hpp */
