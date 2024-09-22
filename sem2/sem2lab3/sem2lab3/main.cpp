// Темы:
// Перегрузка операторов.
// Встроенные объекты
#include <iostream>
#include "myString.h"
#include "Point.hpp"
#include "BD.hpp"
#include "BoolArray.hpp"

#define	stop

int main()
{
//////////////////////////////////////////////////////////////////////



	//Задание 1.Перегрузка операторов.

	//Подключите к проекту файлы MyString.cpp и MyString.h
	//класса MyString, разработанного Вами на предыдущем занятии
	//9a. Перегрузите оператор присваивания для класса MyString
	//Проверьте корректность работы перегруженного оператора

	{
		MyString s1("AAA"), s2;
		s2=s1;
		s1="CCC";
		s2= MyString("tmp");
		s1=s1;
		stop
	}




	//2.Создайте класс Point, который будет содержать координаты
	//"точки". Объявите конструктор (конструкторы) класса   

	//2b. "Перегрузите" оператор += так, чтобы при выполнении
	//операции типа pt2+=pt1; складывались
	//одноименные переменные объектов pt1 и pt2, а сумма
	//присваивалась соответствующим переменным объекта pt2 или
	// в случае  pt2+=1; обе переменные объекта pt2 увеличивались на
	// указанное значение
	//a) с помощью метода класса (оператор +=)
	//б) с помощью глобальной функции (оператор -=)
	//Проверьте корректность работы перегруженного оператора
    {
        Point pt1(1,1);
        Point pt2(2,2);
        pt2+=pt1;
        pt2+=1;
        Point pt3(3,3);
        pt2+=pt1+=pt3;
        stop
    }

	//Задание 2c. Перегрузите оператор +/- 
	//a)с помощью методов класса (оператор +)
	//б) с помощью  глобальных функций (оператор -)
	//так, чтобы любая из закомментированных строк
	//кода выполнялась корректно
    {
        Point pt1(1,1);
        Point pt2(2,2);
        Point pt3;
        
        pt3 = pt1 + 5;
        pt3 = 2 + pt1;
        pt3 = pt1 + pt2;
    
        pt3 = pt1 - 5;
        pt3 = pt1 - pt2;
        stop
        
        //Задание 1d. Перегрузите унарный оператор +/- 
        pt3 = -pt1;
        pt3 = +pt1;
        
    }


	//Задание 2d. Перегрузите оператор << (вывода в поток) для
	//класса MyString таким образом, чтобы при выполнении приведенной строки
	//на экран было выведено:
	//contents:  "QWERTY"

	MyString s("QWERTY");
    std::cout << s << std::endl;

	stop
    //Задание 2e*. Перегрузите операторы + и += для класса MyString таким образом,
    //чтобы происходила конкатенация строк
    
    {
        MyString s1("QWERTY"), s2("AAA"), s3, s4("BBB");
        
        s3 = s1+s2; 
        s4 += s1;
        stop
    }
    
	//Задание 3. Разработать "базу данных" о сотрудниках посредством ассоциативного
	//массива. Ключом является фамилия (ключ в задании уникален, поэтому нескольких Ивановых
	//в базе быть не может), а данными: пол, возраст, должность, зарплата...
	//Реализуйте:
	//добавление сотрудников в базу
	//исключение
	//вывод информации о конкретном сотруднике
	//вывод всей (или интересующей) информации о всех сотрудниках
	//Например:

    BD bd;	//создание пустой базы
    bd["Ivanov"] = DataSet("Ivan", 33, 400000, MALE, Programmer); //если Ivanov-а в базе еще нет, то добавление, если уже есть, то замена его реквизитов
    std::cout<<bd;
    bd["Ivanov"] = DataSet("Prokhor", 35, 300000, MALE, TeamLead);
    std::cout<<bd;
    auto x = new Employee();
    bd["Orlova"] = DataSet("Evgenia", 29, 200000, FEMALE, Tester);
    std::cout<<bd;	//вывод информации обо всех сотрудниках
    
    bd -= bd["Orlova"];
    std::cout<<bd;
    bd -= bd["Ivanov"];
    std::cout<<bd;
    delete x;
   //А также:
   BD bdnew = bd;
   
   bdnew = bd;

   //А также семантику перемещения:
   BD bdmove;
   bdmove = std::move(bdnew);



    //Задание 4.а) Реализуйте класс BoolArray, представляющий динамический массив
    //логических значений (тип bool). Каждая переменная типа bool занимает 1
    //байт, то есть 8 бит, в то время как она могла бы занимать 1 бит.
    //
    //Реализуйте этот класс таким образом, чтобы каждое значение значений действительно
    //занимало 1 бит (точнее сказать, чтобы n значений занимали не более ceil(n / 8),
    //где ceil - целая часть числа с округлением вверх).
    //
    //Класс должен поддерживать следующее поведение:

    {
        // Создается массив из 10 значений false
        BoolArray ar1(10);

        // Создается массив из 5 значений true
        BoolArray ar2(5, true);

        // Создается независимая копия `ar2`
        BoolArray ar3(ar2);

        // 4 и 6 элементу (нумерация с 0) устанавливаются заданное значение
        ar1[4] = ar1[6] = true;
        
        // Над полученными значениями выполняем логические операции
        ar1[2] = (!ar1[6] && ar1[8] || (ar1[0] != true));

        // Выведем массив на печать
        std::cout << "[";
        for (int i = 0; i < ar1.size(); ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << ar1[i];
        }
        std::cout << "]\n";

        // Выведем массив на печать по-другому
        std::cout << "[";
        for (int i = 0, printed = 0; i < ar1.size(); ++i) {
            if (ar1[i]) {
                if (printed++ > 0) std::cout << ", ";
                std::cout << i;
            }
        }
        std::cout << "]\n";

        // Метод `resize` изменяет размер массива.
        // Если новый размер больше, то новые значения дополняются заданным
        // значением (по умолчанию false). Если новый размер меньше, то конец
        // массива отбрасывается.

        ar1.resize(15, true);
        // выведите массив на печать
        std::cout << "[";
        for (int i = 0; i < ar1.size(); ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << ar1[i];
        }
        std::cout << "]\n";
        //...

        ar1.resize(9, true);
        // выведите массив на печать снова
        std::cout << "[";
        for (int i = 0; i < ar1.size(); ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << ar1[i];
        }
        std::cout << "]\n";
        //...

    }
	return 0;
}//endmain
