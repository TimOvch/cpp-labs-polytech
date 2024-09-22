#include <string>
#include <ostream>
#include "myString.h"
using namespace std;

char* concatChars(char* str1, char* str2) {
    size_t totalLength = strlen(str1) + strlen(str2);
    
    char* result = new char[totalLength + 1];
    int index = 0;

    strcpy(result + index, str1);
    index += strlen(str1);
    strcpy(result + index, str2);
    index += strlen(str2);

    return result;
}

void MyString::concatStr(MyString const & plus){
    if(m_pStr != nullptr){
        size_t totalLength = strlen(m_pStr) + strlen(plus.m_pStr);
        
        char* result = new char[totalLength + 1];
        int index = 0;

        strcpy(result + index, m_pStr);
        index += strlen(m_pStr);
        strcpy(result + index, plus.m_pStr);
        index += strlen(m_pStr);
        
        delete m_pStr;
        m_pStr = result;
    } else{
        SetNewString(plus.m_pStr);
    }
}

MyString MyString::concatedStr(MyString const & plus) const{
    if(m_pStr != nullptr){
        size_t totalLength = strlen(m_pStr) + strlen(plus.m_pStr);
        
        char* result = new char[totalLength + 1];
        int index = 0;

        strcpy(result + index, m_pStr);
        index += strlen(m_pStr);
        strcpy(result + index, plus.m_pStr);
        index += strlen(m_pStr);
        
        MyString temp(result);
        delete[] result;
        
        return temp;
    } else{
        return MyString{plus};
    }
}

//конструкторы
MyString::MyString(){
    m_pStr = nullptr;
}

MyString::MyString(const char* str)
    : MyString()
{
    SetNewString(str);
}

//Конструктор копирования
MyString::MyString(MyString const& a)
: MyString()
{
    SetNewString(a.m_pStr);
}

//Конструктор перемещения
MyString::MyString(MyString&& moved){
    m_pStr = moved.m_pStr;
    moved.m_pStr = nullptr;
}

//Деструктор
MyString::~MyString(){
    if(m_pStr != nullptr) delete[] m_pStr;
}


//Метод возврата строки
const char* MyString::getString()const{
    if(m_pStr != nullptr){
        return m_pStr;
    } else{
        return "No line!";
    }
}

//оператор ==
bool MyString::operator==(MyString str)const{
    if(m_pStr != nullptr && str.m_pStr != nullptr){
        return 0==strcmp(m_pStr, str.m_pStr);
    } else if((m_pStr == nullptr && str.m_pStr != nullptr)||(m_pStr != nullptr && str.m_pStr == nullptr)){
        return 0;
    } else {
        return 1;
    }
}

//Метод новой строки
void MyString::SetNewString(const char* str){
    if(m_pStr != nullptr) delete[] m_pStr;
    
    if (str == nullptr){
        m_pStr = nullptr;
        return;
    }
    
    size_t size = strlen(str)+1;
    
    m_pStr = new char[size];
    
    m_pStr = strcpy(m_pStr, str);
}


// Перегрузка оператора <<
std::ostream& operator<<(std::ostream& stream, MyString& str)
{
    if(str.m_pStr != nullptr){
        stream << str.m_pStr;
    } else{
        stream<<"Null pointer!";
    }
    return stream;
}

//Перегрузка операторов + и +=
MyString MyString::operator+(MyString const &a)const{
    return concatedStr(a);
}


MyString& MyString::operator+=(MyString const &a){
    concatStr(a);
    return *this;
}
