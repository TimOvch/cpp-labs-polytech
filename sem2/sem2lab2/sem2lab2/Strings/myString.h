#pragma once
class MyString
{
    char* m_pStr;	//строка-член класса
    int size;
    
    public:
    //конструкторы
    MyString();
    
    MyString(const char* str);
    
    //Конструктор копирования
    MyString(MyString const& a);
    
    //Деструктор
    ~MyString();
 
    //Метод возврата строки
    char* getString();
    
    //Оператор присваивания
    MyString & operator=(MyString const &a){
        if(this!=&a){
            delete m_pStr;
            size = a.size;
            m_pStr = new char[size];
            for(int i = 0; i < size; i++){
                m_pStr[i] = a.m_pStr[i];
            }
        }
        return *this;
    }
    
    //Метод новой строки
    void SetNewString(const char* str);
};


