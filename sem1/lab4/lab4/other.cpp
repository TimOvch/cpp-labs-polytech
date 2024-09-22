#include <iostream>
//#include <tchar.h>
//#include <cstdio>
#include <cstdarg>
#include <ctime>

#include "other.hpp"

int forRef = 5;
int& ref = forRef;

int global_var = 5;

int IncByValue(int x){
    x+=1;
    return x;
}

void IncByPointer(int* ukx){
    *ukx+=1;
}

void IncByReference(int& ssx){
    ssx+=1;
}

//функция для вывода массива
void printArray(const int* arr, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << '\n';
}

//замена по указателям
void swapUk(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

//замена по ссылкам
void swapS(int& a, int& b){
    int temp = a;
    a = b;
    b = temp;
}

int minAr(const int *nMas, const int size) {
    int min = nMas[0];
    for(int j = 1; j < size; j++){
        if(*(nMas+j) < min){
            min = *(nMas+j);
        }
    }
    return min;
}

//нахождение минимального значения для встроенного двумерного массива
int minAr(int* nMas, const int rows, const int cols){
    int min = minAr(nMas, rows*cols);
    return min;
}

//нахождение минимального значения для динамического двумерного массива
int minAr(int** nMas, int lenmas, int lenvmas){
    int min = minAr(nMas[0], lenvmas);
    //ищем минимальное значение
    for(int i = 1; i < lenmas; i++){
        int newMin = minAr(nMas[i],lenvmas);
        if(newMin < min){
            min = newMin;
        }
    }
    //возвращаем
    return min;
}

//моя функция для лексикографического сравнения строк
int MyStrCmp(const char*a,const char*b){
    //создаём флаг на случай равенства строк
    bool equal = 1;

    //создаем такой флаг, что в случае если a > b он будет равен 1, если нет 0
    bool aBolb = 0;
    
    //проходимся по значениям каждой строки и сравниваем
    int i = 0;
    while(true){
        if(a[i]==b[i]){ //случай равности
            if(a[i]=='\0'){//выход из цикла для равности
                break;
            }
            i++;
            continue;
        } else if((int(a[i]) > int(b[i])) || (b[i] == '\0')){ //случай a>b
            aBolb = 1;
            equal = 0;
            break;
        } else if((int(a[i]) < int(b[i])) || (a[i] == '\0')){ //случай b>a
            equal = 0;
            break;
        }
        i++;
    }

    //проверяем по флагам и возвращаем нужное значение
    if(equal){
        return 0;
    } else if(aBolb){
        return 1;
    } else{
        return -1;
    }
}

int nDayTab[2][12]={
    {31,28,31,30,31,30,31,31,30,31,30,31}, //невисокосный год
    {31,29,31,30,31,30,31,31,30,31,30,31}  //високосный год
    };


//функция подсчета дня с начала года из месяца и числа
int DayOfYear(int day, int month, int year){
    //создаем переменную для подсчета для с начала года
    int numOfDay = day;
    //проверка на високосность
    bool isLeapYear = (year%400==0) || ((year%4 == 0) && (year%100!=0));

    //прибавляем значения целых прошедших месяцов в зависимоси от високосности
    for(int i = 0; i < month-1; i++){
        numOfDay+=nDayTab[isLeapYear][i];
    }

    //возвращаем значение
    return numOfDay;
}

//функция для подсчета месяца и числа из дня с начала года
void DayOfMonth(int numOfDay, int year, int* day, int* month){
    *day = 0; //первое значение для даты
    *month = 1; //второе значение для месяца

    //проверка года на високосность
    bool isLeapYear = (year%400==0) || ((year%4 == 0) && (year%100!=0));

    //вводим счетчик для даты и с помощью него будем проверять количество месяцев
    int kDays = nDayTab[isLeapYear][0];

    //проверка на случай если месяц 0, то есть январь
    if(numOfDay > kDays){
        //пока переменная с днем с начала года по счету - переменная с суммой дней прошедших месяцов положительна делаем следующее:
        while(numOfDay - kDays > 0){
            //меняем дату
            *day=numOfDay-kDays;
            
            //прибавляем количество дней прошедшего месяца в счетчик для даты
            kDays+=nDayTab[isLeapYear][*month];

            //прибавляем месяц
            *month+=1;
        }
    } else{
        //в случае если количество дней с начала года < количество дней в первом месяце, значит кол-во дней с начала года = дата в месяце
        //а месяц в таком случае первый, какой у нас и стоит изначально
        *day = numOfDay;
    }
}

//функция для добавления в массив значения в случае уникальности
void uniquepush_back(int*& arr, int& size, int newVal){
    //Проверка на уникальность
    for(int i = 0; i < size; i++){
        if(arr[i]==newVal){
            return;
        }
    }

    //создаём новый массив на +1 элемент
    int newSize = size + 1;
    int *newArr = new int[newSize];

    //копируем значения из старого массива
    for(int i = 0; i < size; i++){
        newArr[i] = arr[i];
    }

    //добавляем новое значение
    newArr[size] = newVal;

    //освобождаем память, занятую старым массивом
    delete[] arr;

    //Обновляем указатель и размерность
    arr = newArr;
    size = newSize;
}

//создаю функцию для вычисление суммы первых n натуральных чисел
int sumNatNums(int n){
    //создаём дно рекурсии
    if(n==1){
        return 1;
    }

    //считаем сумму для прошлого числа
    int prevSumNum = sumNatNums(n-1);

    //возвращаем сумму прошлого + настоящее
    return n + prevSumNum;
}


//функция для вывода в консоль переменного кол-ва параметров
void VarArgs (int start, ...){
    //все элементы в памяти расположенны за обязательным аргументом, поэтому выводим все, пока не встретим 0
    int* currentArg = &start;
    int totalargs = 1;
    while (*currentArg != 0)
    {
        std::cout<<"Argument: " << *currentArg << "\n";
        currentArg++;
        totalargs++;
    }
    std::cout << "Total arguments: " << totalargs;
    std::cout << '\n';
}

//версия функции с использованием макросов va
void VarArgs2(int count, ...){
    va_list list;
    va_start(list, count);
    for(int i = 0; i < count; i++){
        std::cout<<"Argument: " << va_arg(list, int) << "\n";
    }
    va_end(list);
    std::cout << "Total arguments: " << count << '\n';
}

//функция MyMin, которая возвращает адрес минимального числа
int* MyMin(int* arr, int size){
    int min = arr[0];
    int* res = arr;
    for(int i = 1; i < size; i++){
        if(arr[i] < min){
            min = arr[i];
            res = &arr[i];
        }
    }
    return res;
}
