#ifndef BD_hpp
#define BD_hpp
#include "Employee.hpp"
#include <iostream>

#define BDDelta 10

class iterator_bd;

class BD {
    
private:
    Employee** employees;
    size_t quantity;
    size_t capacity;
    
    void AddEmployee(MyString& Surname);
    
    void copyBD(BD const& bd);
    
public:
    //Конструктор
    BD();
    
    //Конструктор копирования
    BD(BD const & bd);
    
    //Коструктор перемещения
    BD(BD&& moved);
    
    //Оператор присваивания
    BD& operator=(BD const & bd);
    
    //Оператор присваивания перемещения
    BD& operator=(BD&& bd);
    
    //Деструктор
    ~BD();
    
    //оператор [] добавления/нахождения
    Employee& operator[](const char* index);
    
    //оператор - удаления
    BD& operator-=(Employee& deleting);
    
    // TODO: подумайте о том, как предоставить доступ на чтение к вашей БД (итератор)
    iterator_bd begin();
    iterator_bd end();
    
    friend class iterator_bd;
};

class iterator_bd{
private:
    Employee** it;
public:
    iterator_bd();
    iterator_bd(Employee** ptr);
    Employee* operator*();
    Employee** operator->();
    iterator_bd operator+(int n);
    iterator_bd operator-(int n);
    const long operator-(iterator_bd const & iter) const;
    iterator_bd& operator++();
    iterator_bd& operator--();
    iterator_bd operator++(int);
    iterator_bd operator--(int);
    iterator_bd& operator+=(int n);
    iterator_bd& operator-=(int n);
    bool operator==(iterator_bd const &other) const;
    bool operator!=(iterator_bd const &other) const;
};

std::ostream& operator<<(std::ostream& stream, BD& bd);
#endif
