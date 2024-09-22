
/*************************************************************
    Практическое занятие №5.
    "Старые" потоковые функции стандартной библиотеки
    Указатели на функции
    Структуры
*************************************************************/
//#include <tchar.h>
#include <iostream>
//#include <cstdio>
#include "other.hpp"
#include <cmath>
#include <string>

#define stop

BOOK globalBook;

int main()
{


    //Тема "Старые" потоковые функции стандартной библиотеки
    //Задание 1. С помощью функции scanf сформирйуте три коэффициента: A,B,C
    int A, B, C;
    line();
    printf("Enter A:");
    scanf("%d", &A);
    printf("Enter B:");
    scanf("%d", &B);
    printf("Enter C:");
    scanf("%d", &C);
    //Задание 2. Выведите (красиво!) таблицу значений y=A*x*x + B*x + C
    //при изменении x в диапазоне -2 до +2 с шагом 0.5
    
    printf("\tx\t|\ty\n-----------------\n");
    for(double x = -2; x <= 4; x+=0.5){
        double y = A*x*x + B*x + C;
        printf("%1.3lf\t|\t%.3lf\n",x,y);
    }
    line();
 
    
    //Тема Указатели на функции

    //Задание 1. Указатель на функцию. "Калькулятор".
    //Напишите функции:
    //1)Sum - принимает два значения double и возвращает сумму
    //этих значений
    //2)Sub- принимает два значения double и возвращает разность
    //этих значений
    //3)Mul - *
    //4)Div - /
    //5)а для возведения в степень можете использовать функцию стандартной библиотеки
    //        - pow(). Подсказка 1: прототип функции находится в <cmath>.
    //        Подсказка 2: стандартная библиотека предоставляет несколько перегруженных
    //        вариантов этой функции, а Вам потребуется сформировать указатель на
    //        double pow(double, double);

    //Предоставьте пользователю    следующую возможность:
    //пока пользователь хочет пользоваться услугами Вашего калькулятора,
    //он может вводить два значения и знак операции
    //а Вы выводите результат. Результат получаете посредством вызова
    //соответствующей Вашей функции по указателю.
    //Предусмотрите возможность ввода непредусмотренного знака операции

    //формирую указатели
    //double (*summa) (double a, double b); Можно таким образом, но проще с auto
    //summa = Sum;
    auto Summa = Sum;
    auto Substr = Sub;
    auto Multi = Mul;
    auto Diver = Div;
    double (*Step) (double a, double b);
    Step = pow;
    
    int go = 1;
    
    while(go){
        double a,b;
        char oper;
        line();
        printf("Enter a:");
        scanf("%lf",&a);
        printf("Enter b:");
        scanf("%lf",&b);
        line();
        printf("Operations:\n+ = Summation\n- = Substraction\n* = Multiplication\n/ = Diversion\n^ = Exponentation\nEnter operation:");
        fflush(stdin);//очищаю буфер
        scanf("%c", &oper);
        line();
        if(oper!='+' && oper!='-' && oper!='*' && oper!='/' && oper != '^'){
            while(oper!='+' && oper!='-' && oper!='*' && oper!='/' && oper != '^'){
                line();
                printf("Operations:\n+ = Summation\n- = Substraction\n* = Multiplication\n/ = Diversion\n^ = Exponentation\nWrong operator, enter again:");
                fflush(stdin);
                scanf("%c",&oper);
                line();
            }
        }
        switch (oper) {
            case '+':
                printf("Result: %.4lf\n",Summa(a,b));
                break;
            case '-':
                printf("Result: %.4lf\n",Substr(a,b));
                break;
            case '*':
                printf("Result: %.4lf\n",Multi(a,b));
                break;
            case '/':
                printf("Result: %.4lf\n",Diver(a,b));
                break;
            case '^':
                printf("Result: %.4lf\n",Step(a,b));
                break;
        }
        printf("Continue?\n0 if No, 1 if Yes\nEnter:");
        fflush(stdin);
        scanf("%d",&go);
    }
    stop

    //Задание 2. Указатель на функцию в качестве аргумента.
    //Дана заготовка функции сортировки любых объектов - Sort.
    //Функция принимает следующие параметры:
    //1) указатель на первый сортируемый элемент
    //2) количество сортируемых элементов
    //3) размер элемента в байтах
    //4) указатель на функцию перестановки элементов
    //5) указатель на функцию сравнения элементов

    //2a. Напишите функцию перестановки двух целых значений -
    // SwapInt, которая принимает два void указателя и
    //меняет значения местами
    //Напишите функцию сравнения двух целых значений -
    // CmpInt, которая принимает два void указателя и
    //возвращает int результат сравнения:
    // <0 - первый элемент меньше, чем второй
    // =0 - равны
    // >0 - первый элемент больше, чем второй
    
    int nAr[10]{4,2,1,5,3,6,7,8,9,0};   //массив для сортировки

    //Печать исходного массива
    line();
    printf("int Array before sorting:\n");
    printArray(nAr, 10);
    
    //Вызов сортировки
    int nTotal=10;          //количество элементов в массиве
    Sort(reinterpret_cast<char*>(&nAr[0]), nTotal, sizeof(int), SwapInt, CmpInt);
    
    //Печать результатов сортировки
    printf("int Array after sorting:\n");
    printArray(nAr, 10);
    line();


    //Задание 2б. По аналогии с 8а создайте вспомогательные
    //функции - SwapDouble и CmpDouble и вызовите функцию Sort
    //для сортировки массива вещественных значений.
    line();
    double nArd[10]{0.4,0.2,0.1,0.5,0.3,0.6,0.7,0.8,0.9,0};
    printf("double Array before sorting:\n");
    printArray(nArd, 10);
    Sort(reinterpret_cast<char*>(&nArd[0]), nTotal, sizeof(double), SwapDouble, CmpDouble);
    printf("double Array after sorting:\n");
    printArray(nArd, 10);
    line();
    //Задание 2в*. По аналогии с 8а создайте вспомогательные
    //функции - SwapStr и CmpStr и вызовите функцию Sort
    //для сортировки массива указателей на строки.
    nTotal = 4;
    char* arStr[] = {"QQQ", "SDF", "ABC", "FSW"};
    
    printf("string Array before sorting:\n");
    printArray(arStr, nTotal);
    Sort(reinterpret_cast<char*>(&arStr[0]), nTotal, sizeof(char*), SwapStr, CmpStr);
    printf("double Array after sorting:\n");
    printArray(arStr, 4);
    //Задание 3. Массивы указателей на функцию.
    //Напишите несколько функций вида
    //const char* GetString1();
    //const char* GetString2();
    //        ...., каждая из функций возвращает указатель на свою строку
    //(подумайте - какой адрес Вы имеете право возвращать из функции)
    

    //Объявите и проинициализируйте массив указателей на функции
    //GetString1,GetString2...

    const char* (*strFuncArray[])()={GetString1,GetString2,GetString3,GetString4};

    //Введите номер функции, которую Вы хотите вызвать:
    int n;
    line();
    printf("Enter number of function with string:");
    scanf("%d",&n);

    //Вызовите функцию

    const char * resStrFunc = strFuncArray[n-1]();
    
    //Распечатайте результат
    printf("%s", resStrFunc);
    line();

//////////////////////////////////////////////////////////////////////////////////////

    //Тема. Структуры С.
    //Задание 1. Объявите структуру BOOK, описывающую книгу
    //(автор, заглавие, год издания, цена, категория…).
    //Подумайте: какого типа могут быть поля структуры.
    //Подсказка: объявление структуры рекомендуется выносить
    //в заголовочный файл.
    //Задание 2. Создайте разными способами (глобальный, локальный, статический,
    //динамический) экземпляры (объекты) типа BOOK (без инициализации).
    //Определите - сколько памяти отводит компилятор под каждый
    //такой объект. Как инициализируются (или не инициализируются) поля
    //структуры. Подумайте: от чего зависит объем выделяемой памяти?
    BOOK localBook;
    
    static BOOK staticBook;
    
    BOOK* dynamicBook = new BOOK;
    
    BOOK masBooks[] = {localBook,staticBook,*dynamicBook, globalBook};
    
    line();
    printf("1 - local, 2 - dynamic, 3 - dynamic, 4 - global\n");
    for(int i = 0; i <4; i++){
        printf("Size of BOOK %d: %lu bytes;\n",i+1, sizeof(masBooks[i]));
    }
    line();
    //Задание 3. Заполните поля созданных объектов.
    //Замечание: если для хранения строки используется массив, необходимо
    //предусмотреть "защиту" от выхода за границы массива.
    
    localBook.EnterAuthor("author");
    localBook.EnterTitle("title");
    localBook.year = 2000;
    localBook.price = 9.99;
    localBook.category = drama;
    
    globalBook.EnterAuthor("author");
    globalBook.EnterTitle("title");
    globalBook.year = 2000;
    globalBook.price = 9.99;
    globalBook.category = drama;
    
    staticBook.EnterAuthor("author");
    staticBook.EnterTitle("title");
    staticBook.year = 2000;
    staticBook.price = 9.99;
    staticBook.category = drama;
    
    dynamicBook->EnterAuthor("author");
    dynamicBook->EnterTitle("title");
    dynamicBook->year = 2000;
    dynamicBook->price = 9.99;
    dynamicBook->category = drama;
    
    delete dynamicBook;
    //Задание 4. Напишите функцию, выводящую на экран реквизиты книги.
    //Подумайте: как эффективнее передавать экземпляр BOOK в функцию.
    //Для вывода на консоль используйте функцию стандартной библиотеки
    //printf

    printBook(&localBook);


    //Задание 5. Напишите функцию для формирования полей структуры.
    //Для ввода используйте функцию стандартной библиотеки scanf
    //Замечание: неплохо заложить в такую функцию возможность проверки
    //корректности введенного значения, например, год издания не может быть
    //меьше, чем... (год появления письменности), категорию ползователь
    //должен выбирать из существующих, цена не может быть отрицательной...
    
    initBook(&staticBook);
    
    return 0;
}//main

