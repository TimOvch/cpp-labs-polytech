#include <string>
#include "myString.h"
using namespace std;

//конструкторы
MyString::MyString(){
    m_pStr = nullptr;
    size = 0;
}

MyString::MyString(const char* str){
    size = 0;
    
    while(*(str+size) != '\0'){
        size++;
    }
    
    size+=1;
    
    m_pStr = new char[size];
    
    for(int i = 0; i < size; i++){
        m_pStr[i] = str[i];
    }
    
}

//Конструктор копирования
MyString::MyString(MyString const& a){
    size = a.size;
    m_pStr = new char[size];
    for(int i = 0; i < size; i++){
        m_pStr[i] = a.m_pStr[i];
    }
}

//Деструктор
MyString::~MyString(){
    delete [] m_pStr;
}


//Метод возврата строки
char* MyString::getString(){
    return m_pStr;
}

//Метод новой строки
void MyString::SetNewString(const char* str){
    delete m_pStr;
    size = 0;
    
    while(*(str+size) != '\0'){
        size++;
    }
    
    size+=1;
    
    m_pStr = new char[size];
    
    for(int i = 0; i < size; i++){
        m_pStr[i] = str[i];
    }
}


