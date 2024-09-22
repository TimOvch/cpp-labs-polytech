#include "BD.hpp"

#include <stdlib.h>

void BD::AddEmployee(MyString& Surname){
    // TODO: придумайте более умную стратегию выделения памяти
    // или обобщите логику и передайте ее внутрь класса
    if(employees == nullptr){
        capacity = BDDelta;
        employees = new Employee*[capacity];
        employees[quantity] = new Employee{Surname};
        quantity++;
    } else{
        if(capacity>quantity){
            employees[quantity] = new Employee{Surname};
            quantity++;
        }
        else{
            Employee** NewEmployees = new Employee*[capacity+BDDelta];
            for(int i = 0; i < quantity; i++){
                NewEmployees[i] = employees[i];
            }

            delete[] employees;
            employees = NewEmployees;
            NewEmployees[quantity] = new Employee{Surname};
            quantity++;
            capacity += BDDelta;
        }
    }
}

void BD::copyBD(BD const& bd){
    if(employees != nullptr){
        for(int i = 0; i < quantity; i++){
            delete employees[i];
        }
        delete[] employees;
    }
    
    quantity = bd.quantity;
    
    employees = new Employee*[quantity];
    
    for(int i = 0; i < quantity; i++){
        employees[i] = new Employee;
        *employees[i] = *bd.employees[i];
    }
    
}


//конструктор
BD::BD(){
    quantity = 0;
    employees = nullptr;
    capacity = 0;
}

//Конструктор копирования
BD::BD(BD const & bd)
: BD()
{
    if(bd.employees == nullptr) return;
    
    copyBD(bd);
}

//Коструктор перемещения
BD::BD(BD&& moved){
    quantity = moved.quantity;
    capacity = moved.capacity;
    employees = moved.employees;
    moved.employees = nullptr;
    moved.quantity = 0;
}

//Оператор присваивания
BD& BD::operator=(BD const & bd){
    copyBD(bd);
    
    return *this;
}

//Оператор присваивания перемещения
BD& BD::operator=(BD&& bd){
    quantity = bd.quantity;
    employees = bd.employees;
    capacity = bd.capacity;
    bd.quantity = 0;
    bd.employees = nullptr;
    return *this;
}

//Деструктор
BD::~BD(){
    if(employees!= nullptr){
        for(int i = 0; i < capacity; i++){
            delete employees[i];
        }
        delete[] employees;
    }
}

//оператор []
Employee& BD::operator[](const char* index){
    MyString InSurname{index};
    if(quantity == 0){
        AddEmployee(InSurname);
        return *employees[0];
    } else {
        for(int i = 0; i < quantity; i++){
            if(employees[i]->getSurname() == InSurname) return *employees[i];
        }
        AddEmployee(InSurname);
        return *employees[quantity-1];
    }
}

//оператор - удаления
BD& BD::operator-=(Employee& deleting){
    int index = -1;
    for(int i = 0; i < quantity; i++){
        if(employees[i]->getSurname() == deleting.getSurname()){
            index = i;
        }
    }
    if(index!=-1){
        delete employees[index];
        for(int i = index; i < quantity-1; i++){
            employees[i] = employees[i+1];
        }
        
        Employee** nemployees = new Employee*[capacity];
        for(int i = 0; i < quantity-1; i++){
            nemployees[i] = employees[i];
        }
        quantity--;
        delete[] employees;
        employees = nemployees;
    }
    return *this;
}

iterator_bd BD::begin(){
    return iterator_bd{employees};
}

iterator_bd BD::end(){
    return iterator_bd{employees+quantity};
}

std::ostream& operator<<(std::ostream& stream, BD& bd){
    auto iter = bd.begin();
    auto end = bd.end();
    stream << "----[Employees Data Base]----\n";
    
    if(iter == end){
        stream << "-------[Base is empty]-------\n\n";
        return stream;
    }
    int i = 1;
    

    while(iter != end){
        stream << '['<<  i <<  "]-----------------\n" << **iter << "\n";
        i++;
        iter++;
    }
    
    stream << "\n\n";
    return stream;
}


iterator_bd::iterator_bd(){
    it = nullptr;
}

iterator_bd::iterator_bd(Employee** ptr){
    it = ptr;
}

Employee* iterator_bd::operator*(){
    return *it;
}

Employee** iterator_bd::operator->(){
    return it;
}

iterator_bd iterator_bd::operator+(int n){
    return iterator_bd{it + n};
}

iterator_bd iterator_bd::operator-(int n){
    return iterator_bd{it - n};
}

const long iterator_bd::operator-(iterator_bd const & iter) const{
    return it - iter.it;
}

iterator_bd& iterator_bd::operator++(){
    it++;
    return *this;
}

iterator_bd& iterator_bd::operator--(){
    it--;
    return *this;
}
iterator_bd iterator_bd::operator++(int){
    iterator_bd old = *this;
    ++*this;
    return old;
}

iterator_bd iterator_bd::operator--(int){
    iterator_bd old = *this;
    --*this;
    return old;
}

iterator_bd& iterator_bd::operator+=(int n){
    it+=n;
    return *this;
}

iterator_bd& iterator_bd::operator-=(int n){
    it-=n;
    return *this;
}

bool iterator_bd::operator==(iterator_bd const &other) const{
    return it == other.it;
}

bool iterator_bd::operator!=(iterator_bd const &other) const{
    return it != other.it;
}
