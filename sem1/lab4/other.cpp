//Задание 2. Отличия при передаче параметров а) по значению,
    // б) по ссылке, в) по указателю
    //Объявите и определите три функции , которые увеличивают заданное
    //с помощью параметра значение на 1 ( а) - IncByValue(),
    // б) - IncByPointer(), в) - IncByReference() ).
//Прототипы используемых в данном задании функций:
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
