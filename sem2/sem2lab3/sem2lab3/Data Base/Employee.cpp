#include "Employee.hpp"

const char* GenderString[] = {"Male", "Female", "Not mentioned"};

const char* PositionString[] = {"Chief Executive Officer", "Chief Technical Officer","ProductDirector","ProjectManager","TeamLead","Programmer","Tester","Сleaner","Guard","Not mentioned"};

//конструкторы вспомогательной структуры Data
Data::Data(MyString Name, unsigned int Age, unsigned int Salary, Gender gend, Position pos)
: name(Name), age(Age), salary(Salary), gender(gend), position(pos)
{}

Data::Data()
: name("No name"), age(0), salary(0), gender(NotMentioned), position(NoName)
{}

//метод сбора новых данных
Data DataSet(const char* Name, const unsigned int Age, const unsigned int Salary, const Gender gend, const Position pos){
    Data NE{MyString{Name}, Age, Salary, gend, pos};
    return NE;
}

//конструкторы
Employee::Employee()
: Employee(MyString{"No surname"})
{}

Employee::Employee(MyString Surname){
    surname = Surname;
}

Employee::Employee(MyString& Surname, MyString& Name, unsigned int Age, unsigned int Salary, Gender gend, Position pos)
:surname(Surname), data(Name, Age, Salary, gend, pos)
{}

//Сеттер
void Employee::SetInfo(MyString& Name, unsigned int Age, unsigned int Salary, Gender gend, Position pos){
    data.name = Name;
    data.age = Age;
    data.salary = Salary;
    data.gender = gend;
    data.position = pos;
}

//геттер фамилии
MyString Employee::getSurname(){
    return surname;
}

//оператор присваивания
Employee& Employee::operator=(Employee& emp){
    surname = emp.surname;
    SetInfo(emp.data.name, emp.data.age, emp.data.salary, emp.data.gender, emp.data.position);
    return *this;
}

//оператор = для удобной передачи данных
Employee& Employee::operator=(Data right){
    this->data = right;
    return *this;
}

//Оператор <<
std::ostream& operator<<(std::ostream& stream, Employee& emp){
    stream << "Surname: " << emp.surname << '\n';
    stream << "Name: " << emp.data.name << '\n';
    stream << "Age: " << emp.data.age << '\n';
    stream << "Gender: " << GenderString[emp.data.gender] << '\n';
    stream << "Position: " << PositionString[emp.data.position] << '\n';
    stream << "Salary: " << emp.data.salary << " rub." << '\n';
    
    return stream;
}
