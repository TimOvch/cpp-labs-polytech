#pragma once
#include <iostream>

// TODO: везде, где метод может быть const, сделать его const
// TODO: то же для friend-функций

class MyString
{
private:
    char* m_pStr;	//строка-член класса
    
    void concatStr(MyString const & plus);
    
    MyString concatedStr(MyString const & plus) const;
    
public:
    //конструкторы
    MyString();
    
    MyString(const char* str);
    
    //Конструктор копирования
    MyString(MyString const& a);
    
    //Конструктор перемещения
    MyString(MyString&& moved);
    
    //Деструктор
    ~MyString();
 
    //Метод возврата строки
    char* getString() const;
    
    //Оператор присваивания
    MyString & operator=(MyString const &a){
        if(this!=&a){
            SetNewString(a.m_pStr);
        }
        return *this;
    }
    
    MyString & operator=(const char* str){
        SetNewString(str);
        return *this;
    }
    
    //Оператор присваивания перемещения
    MyString & operator=(MyString&& a){
        if(this!=&a){
            if(m_pStr != nullptr) delete[] m_pStr;
            m_pStr = a.m_pStr;
            a.m_pStr = nullptr;
        }
        return *this;
    }
    
    //Оператор ==
    bool operator==(MyString str) const;
    
    //Метод новой строки
    void SetNewString(const char* str);
    
    //перегрузка операторов << >>
    friend std::ostream& operator<<(std::ostream& stream, MyString& str);
    
    friend std::istream& operator >> (std::istream& in, MyString& a);
    
    //Перегрузка операторов + и +=
    MyString operator+(MyString const &a) const;
    MyString & operator+=(MyString const &a);
};
