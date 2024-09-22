#ifndef Employee_hpp
#define Employee_hpp

#include <stdio.h>
#include "myString.h"

enum Gender{
    MALE,
    FEMALE,
    NotMentioned
};

enum Position{
    CEO,
    CTO,
    ProductDirector,
    ProjectManager,
    TeamLead,
    Programmer,
    Tester,
    Сleaner,
    Guard,
    NoName
};

struct Data{
    MyString name;
    unsigned int age;
    unsigned int salary;
    Gender gender;
    Position position;
    
    Data(MyString Name, unsigned int Age, unsigned int Salary, Gender gend, Position pos);
    
    Data();
};

extern const char* PositionString[];
extern const char* GenderString[];

class Employee{
private:
    MyString surname;
    Data data;
public:
    //Конструкторы
    Employee();
    
    Employee(MyString Surname);
    
    Employee(MyString& Surname, MyString& Name, unsigned int Age, unsigned int Salary, Gender gend, Position pos);

    //сеттер реквизитов
    void SetInfo(MyString& Name, unsigned int Age, unsigned int Salary, Gender gend, Position pos);
    
    //геттер фамилии
    MyString getSurname();
    
    //оператор присваивания
    Employee& operator=(Employee& emp);
    
    //оператор = для удобной передачи данных
    Employee& operator=(Data right);
    
    friend Employee Data(const char* Name, const unsigned int Age, const unsigned int salary , const Gender gend , const Position pos);
    friend std::ostream& operator<<(std::ostream& stream, Employee& emp);
};

Data DataSet(const char* Name, const unsigned int Age, const unsigned int Salary, const Gender gend, const Position pos);

#endif /* Employee_hpp */
