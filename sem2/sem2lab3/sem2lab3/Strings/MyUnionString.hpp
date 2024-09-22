#ifndef MyUnionString_hpp
#define MyUnionString_hpp

#include <iostream>
#include "MyStringBase.hpp"


struct Big{
    char* ptr;
    unsigned int ifbig:1;
    size_t size:7;
};

struct Small{
    char mas[8];
    unsigned int ifbig:1;
    size_t size:7;
};

union Data{
    Big big;
    Small small;
};

class MyUnionString:public MyStringBase{
    
private:
    Data data;
    
public:
    //Конструкторы
    MyUnionString(){
        data.big.ifbig=1;
        data.big.ptr = nullptr;
        data.big.size = 0;
    }
    
    MyUnionString(const char* InStr){
        int size = 0;
        
        while(*(InStr+size) != '\0'){
            size++;
        }
        
        size+=1;
        
        if(size > 8){
            data.big.ifbig=1;
            data.big.ptr = new char[size];
            data.big.size = size;
            
            for(int i = 0; i < size; i++){
                data.big.ptr[i] = InStr[i];
            }
        } else{
            data.small.ifbig=0;
            data.small.size = size;
            
            for(int i = 0; i < size; i++){
                data.small.mas[i] = InStr[i];
            }
        }
    }
    
    //Конструктор копирования
    MyUnionString(MyUnionString const &a){
        if(a.data.big.ifbig){
            data.big.ifbig = 1;
            data.big.size = a.data.big.size;
            data.big.ptr = new char[data.big.size];
            
            for(int i = 0; i < data.big.size; i++){
                data.big.ptr[i] = a.data.big.ptr[i];
            }
            
        } else{
            data.small.ifbig = 0;
            data.small.size = a.data.small.size;
            
            for(int i = 0; i < data.small.size; i++){
                data.small.mas[i] = a.data.small.mas[i];
            }
            
        }
    }
    
    //Деструктор
    ~MyUnionString() override{
        if(data.big.ifbig) delete[] data.big.ptr;
    }
    
    //Метод возврата строки
    char* getString() override{
        if(data.big.ifbig){
            return data.big.ptr;
        } else{
            return data.small.mas;
        }
    }
    
    //Метод установки новой строки
    void SetNewString(const char* newStr) override{
        if(data.big.ifbig) delete [] data.big.ptr;
        
        int size = 0;
        
        while(*(newStr+size) != '\0'){
            size++;
        }
        
        size+=1;
        
        if(size > 8){
            data.big.ifbig=1;
            data.big.ptr = new char[size];
            data.big.size = size;
            
            for(int i = 0; i < size; i++){
                data.big.ptr[i] = newStr[i];
            }
            
        } else{
            data.small.ifbig=0;
            data.small.size = size;
            
            for(int i = 0; i < size; i++){
                data.small.mas[i] = newStr[i];
            }
            
        }
    }
    
    void WhereAmI() override{
        std::cout << "\nI am in MyUnionString\n";
    }
};

#endif /* MyUnionString_hpp */
