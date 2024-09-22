#ifndef MyStringBase_hpp
#define MyStringBase_hpp

#include <iostream>

class MyStringBase{
public:
    virtual char* getString() = 0;
    virtual void SetNewString(const char* newStr) = 0;
    virtual void WhereAmI() = 0;
    virtual ~MyStringBase(){
        
    }
};

#endif /* MyStringBase_hpp */
