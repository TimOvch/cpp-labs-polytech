//=======================================================================
//	Лабораторная №3. Шаблоны функций. Шаблоны классов. Стандартные шаблоны С++.
//				Обработка исключений.
//=======================================================================
//Используйте недостающие файлы из лабораторной 2
#include "MyVector.h"
#include "MyString.h"
#include "MyStack.h"
#include "stdafx.h"
#include "vector"
#include "list"
#include "algorithm"
#include "string"


//============= Шаблон функции для вывода с помощью итератора
template <class T> void pr(T& v, string s)
{
	cout<<"\n\n\t"<<s<<"  # Sequence:\n";
	
	// Итератор любого контейнера
	typename T::iterator p;
	int i;

	for (p = v.begin(), i=0;  p != v.end();  p++, i++)
		cout << endl << i+1 <<". "<< *p;
	cout << '\n';
}

template <class T> void Swap(T& el1, T& el2){
    T temp;
    temp = el1;
    el1 = el2;
    el2 = temp;
}

void printVec(Vector& i) {  // function:
    i.Out();
    cout <<'\n';
}

bool vecPred(Vector& v){
    return v > Vector(1,0);
}

bool strPred(string& s){
    return s[0] == 'F';
}

bool strPred2(string& s){
    return s == string("Five");
}

int main()
{
    srand(time(0));
	//===========================================================
	// Шаблоны функций
	//===========================================================
	// Создайте шаблон функции перестановки двух параметров - Swap().
	// Проверьте работоспособность созданного шаблона с помощью
	// приведенного ниже фрагмента.
	{
		int i = 1, j = -1;
		Swap (i, j);

		double a = 0.5, b = -5.5;
		Swap (a, b);

		Vector u(1,2), w(-3,-4);
		Swap(u, w);

		// Если вы достаточно развили класс MyString в предыдущей работе,
		// то следующий фрагмент тоже должен работать корректно.
		
		MyString s1 ("Your fault"), s2 ("My forgiveness");
		Swap(s1, s2);
	}
	//===========================================================
	// Шаблоны классов
	//===========================================================
	// Создайте шаблон класса MyStack для хранения элементов любого типа T.
	// В качестве основы для стека может быть выбран массив.
	// Для задания максимального размера стека может быть использован
	// параметр-константа шаблона
	// Обязательными операциями со стеком являются "Push" и "Pop","GetSize" и "Capacity"
	// Необязательной - может быть выбор по индексу (operator[]).
	// Для того, чтобы гарантировать корректное выполнение этих операций 
	// следует генерировать исключительные ситуации.
	
	// С помощью шаблона MyStack создайте стек переменных типа int, затем
	// стек переменных типа double и, наконец, стек из переменных типа Vector 
	// Если вы подготовите три класса для обработки исключений,
	// то следующий фрагмент должен работать
    try
	{
		cout << "\tTest MyStack\n";
		MyStack<int> stack;

		cout << "\nInteger Stack capacity: " << stack.Capacity();

		stack.Push(1);
		stack.Push(2);

		stack.Push(3);
		
		cout << "\nInteger Stack has: " << stack.GetSize() << " elements";

//		stack.Push(4);	// Здесь должно быть "выброшено" исключение

		cout << "\nInteger Stack pops: " << stack.Pop();
		cout << "\nInteger Stack pops: " << stack.Pop();
		
		cout << "\nInteger Stack has: " << stack.GetSize() << " elements";
		stack.Pop();
		// stack.Pop();		// Здесь должно быть "выброшено" исключение
		stack.Push(2);
		
		// int i = stack[3];	// Здесь должно быть "выброшено" исключение

        MyStack<Vector> ptStack;

        cout << "\nVector Stack capacity: " << ptStack.Capacity();

        ptStack.Push(Vector(1,1));
        ptStack.Push(Vector(2,2));

        cout << "\nVector Stack pops: ";
        // Используйте метод класса Vector для вывода элемента
        ptStack.Pop().Out();

        cout << "\nVector Stack has: " << ptStack.GetSize() << " elements";

    }
    catch (StackOverflow)
    {
        cout << "\nStack overflow";
    }
    catch (StackUnderflow)
    {
        cout << "\nStack underflow";
    }

    stop;

    //=======================================================================
    // Контейнеры стандартной библиотеки. Последовательности типа vector
    //=======================================================================

    // Создайте пустой вектор целых чисел. Узнайте его размер с помощью метода size(),
    // С помощью метода push_back() заполните вектор какими-либо значениями.
    // Получите новый размер вектора и выведите значения его элементов.
    // В процессе работы с вектором вы можете кроме количества реально заполненных
    // элементов (size()) узнать максимально возможное количество элементов (max_size()),
    // а также зарезервированную память (capacity()).

    vector<int> v;
    int n = v.size();
    v.push_back(-1);
    v.push_back(-2);
    n = v.size();
    n = v.capacity();
    n = v.max_size();

    // Так как мы часто будем выводить последовательности, то целесообразно
    // создать шаблон функции для вывода любого контейнера.
    // Проанализируйте коды такого шабдлона (pr), который приведен выше
    // Используйте его для вывода вашего вектора

    pr (v, "Vector of ints");

    // Используем другой конструктор для создания вектора вещественных
    // с начальным размером в 2 элемента и заполнением (222.).
    // Проверим параметры вектора. Затем изменим размер вектора и его заполнение
    // (метод - resize()) и вновь проверим параметры.

    vector<double> vd(2,222.);
    pr (vd, "Vector of doubles");
    n = vd.size();
    n = vd.capacity();
    n = vd.max_size();

    vd.resize(10,5.);

    pr (vd, "After resize");
    n = vd.size();
    n = vd.capacity();
    n = vd.max_size();

    // Используя метод at(), а также операцию выбора [], измените значения
    // некоторых элементов вектора и проверьте результат.
    vd.at(1) = 9.;
    vd[0] = 3.;
    pr (vd, "After at");

    vector<double> wd(vd.size());
    std::copy(vd.begin(), vd.end(), wd.begin());

    // Создайте вектор вещественных, который является копией существующего.
    pr (wd, "Copy");

    // Создайте вектор, который копирует часть существующей последовательности
    vector<double> ud;
    ud.insert(ud.begin(), vd.begin(), vd.end()-=3);

    pr (ud, "Copy part");

    // Создайте вектор вещественных, который является копией части обычного массива.
    double ar[] = { 0., 1., 2., 3., 4., 5. };

    vector<double> va(ar, ar+5);
    pr (va, "Copy part of array");

    // Создайте вектор символов, который является копией части обычной строки
    char s[] = "Array is a succession of chars";

    vector<char> vc(s, s+6);
    pr (vc, "Copy part of c-style string");

    // Создайте вектор элементов типа Vector и инициализируйте
    // его вектором с координатами (1,1).
    vector<Vector> vv(2,Vector(1,1));

    cout << "\n\nvector of Vectors\n";
    for (int i=0;  i < vv.size();  i++)
        vv[i].Out();

    // Создайте вектор указателей на Vector и инициализируйте его адресами
    // объектов класса Vector

    vector<Vector*> vp = {&vv[0],&vv[1]}, vp2 = {&vv[1], &vv[0]};

    cout << "\n\nvector of pointers to Vector\n";

    for (int i=0;  i < vp.size();  i++)
        vp[i]->Out();

    // Научитесь пользоваться методом assign и операцией
    // присваивания = для контейнеров типа vector.
    Vector test1(2,2);
    vp.assign(2,&test1);


    cout << "\n\nAfter assign\n";
    for (int i=0;  i < vp.size();  i++)
        vp[i]->Out();

    vp2 = vp;

    // Декларируйте новый вектор указателей на Vector и инициализируйте его
    // с помощью второй версии assign
    vector<Vector*> vpNew;

    vpNew.assign(vp.begin(),vp.end());

    cout << "\n\nNew vector after assign\n";
    for (int i=0;  i < vpNew.size();  i++)
        vpNew[i]->Out();


    // На базе шаблона vector создание двухмерный массив и
    // заполните его значениями разными способами.
    // Первый вариант - прямоугольная матрица
    // Второй вариант - ступенчатая матрица


    //========= Ступенчатая матрица
    vector <vector<double>> vdd(5);
    for (int i=0;  i < vdd.size();  i++)
        vdd[i] = vector<double>(i+1, double(i));

    cout << "\n\n\tTest vector of vector<double>\n";
    for (int i=0;  i < vdd.size();  i++)
    {
        cout << endl;
        for (int j=0;  j < vdd[i].size();  j++)
            cout << vdd[i][j] << "  ";
    }

    vector <vector<double>> vddp(5);

    for (int i=0;  i < vddp.size();  i++)
        vddp[i] = vector<double>(5, i);

    cout << "\n\n\tTest vector of vector<double>\n";
    for (int i=0;  i < vddp.size();  i++)
    {
        cout << endl;
        for (int j=0;  j < vddp[i].size();  j++)
            cout << vddp[i][j] << "  ";
    }


    stop;

    //===================================
    // Простейшие действия с контейнерами
    //===================================
    //3б. Получение значения первого и последнего элементов последовательности.
    //Получение размера последовательности. Присваивание значений
    //элементов одной последовательности элементам другой - assign().

    //Создайте и проинициализируйте вектор из элементов char. Размер -
    //по желанию.
    vector<char> chVec(8, 'A');

    //Получите значение первого элемента вектора ( front() )

    cout << '\n' << chVec.front();

    //Получите значение последнего элемента вектора ( back() )

    cout << '\n' << chVec.back();
    //Получите размер вектора

    cout << '\n' << chVec.size();
    //Присвойте вектору любой диапазон из значений массива cMas.

    char cMas[] = {'A','B','C','D','K','U','K','U'};

    chVec.assign(cMas, cMas+3);
    //Проверьте размер вектора, первый и последний элементы.

    cout << '\n' << chVec.front();

    cout << '\n' << chVec.back();

    cout << '\n' << chVec.size();

    stop;


    //3в. Доступ к произвольным элементам вектора с проверкой - at()
    //и без проверки - []
    //Создайте неинициализированный вектор из 8 элементов char - vChar2.
    //С помощью at() присвойте четным элементам вектора значения
    //элементов vChar1 из предыдущего задания,
    //а с помощью [] присвойте нечетным элементам вектора vChar2 значения
    //массива {'K','U','K','U'}.

    vector<char> vChar2(8);
    char mas[] = {'K','U','K','U'};

    for (int i = 0; i < vChar2.size(); i++){
        if(i%2 == 0){
            vChar2.at(i) = chVec[i];
        } else{
            vChar2[i] = mas[i/2];
        }
    }

      stop;

    //Попробуйте "выйти" за границы вектора с помощью at() и
    //с помощью []. Обратите внимание: что происходит при
    //попытке обращения к несуществующему элементу в обоих случаях

    char k = vChar2[9];
    cout << k;
    //char p = vChar2.at(9); // std::out_of_range: vector
    //cout << p;

    stop;

    //3г.Добавьте в конец вектора vChar2  - букву Z (push_back()). Для
    //расширения кругозора можете ее сразу же и выкинуть (pop_back())

    vChar2.push_back('Z');
    vChar2.pop_back();

    stop;

    //3д. Вставка-удаление элемента последовательности insert() - erase()
    //Очистка последовательности - clear()



    //Вставьте перед каждым элементом вектора vChar2 букву 'W'

    for(auto iter = vChar2.end(); iter != vChar2.begin(); iter--){
        vChar2.insert(iter,'W');
    }
    vChar2.insert(vChar2.begin(),'W');

    pr(vChar2,"Test");
    //Вставьте перед 5-ым элементом вектора vChar2 3 буквы 'X'

    vChar2.insert(vChar2.begin()+5,{'X','X','X'});

    pr(vChar2,"Test");
    //Вставьте перед 2-ым элементом вектора vChar2 с третьего по
    //шестой элементы массива "aaabbbccc"

    char mas2[] = "aaabbbccc";

    vChar2.insert(vChar2.begin()+1, mas2+2,mas2+6);

    pr(vChar2,"Test");
    //Сотрите c первого по десятый элементы vChar2

    vChar2.erase(vChar2.begin(),vChar2.begin()+10);
    pr(vChar2,"Test");
    stop;

    //Уничтожьте все элементы последовательности - clear()
    vChar2.clear();

    stop;

    //Создание двухмерного массива
    vector<vector<int>> dMas(5,vector<int>(5,1));

    cout << "\n\n\tTest dMas\n";
    for (int i=0;  i < dMas.size();  i++)
    {
        cout << endl;
        for (int j=0;  j < dMas[i].size();  j++)
            cout << dMas[i][j] << "  ";
    }

    stop;

///////////////////////////////////////////////////////////////////

    //Задание 4. Списки. Операции, характерные для списков.
    //Создайте два пустых списка из элементов Vector - ptList1 и
    //ptList2

    list<Vector> ptList1, ptList2;

    //Наполните оба списка значениями с помощью методов push_back(),
    //push_front, insert()

    for(int i = 0; i < 3;i++){
        int num = rand()%10;

        if(num%3 == 0){
            ptList1.push_back(Vector(num,num));
            ptList2.push_back(Vector(num,num));
        } else if(num%3== 1){
            ptList1.push_front(Vector(num,num));
            ptList2.push_front(Vector(num,num));
        } else {
            ptList1.insert(ptList1.end(),Vector(num,num));
            ptList2.insert(ptList2.end(),Vector(num,num));
        }
    }

    //Отсортируйте списки - sort().
    //Подсказка: для того, чтобы работала сортировка, в классе Vector
    //должен быть переопределен оператор "<"

    ptList1.sort();
    ptList2.sort();

    for (auto it = ptList1.begin();it!=ptList1.end();++it) {
        it->Out();
        cout << '\n';
    }

    stop;

    cout << "\n\n";
    //Объедините отсортированные списки - merge(). Посмотрите: что
    //при этом происходит со вторым списком.

    ptList1.merge(ptList2);

    for (auto it = ptList2.begin();it!=ptList2.end();++it) {
        it->Out();
        cout << '\n';
    }
    cout << "\n\n";
    for (auto it = ptList1.begin();it!=ptList1.end();++it) {
        it->Out();
        cout << '\n';
    }
    cout << "\n\n";

    stop;

    //Исключение элемента из списка - remove()
    //Исключите из списка элемент с определенным значением.
    //Подсказка: для этого необходимо также переопределить
    //в классе Vector оператор "=="

    ptList1.remove(Vector(4,4));

    stop;

///////////////////////////////////////////////////////////////////

	//Задание 5. Стандартные алгоритмы.Подключите заголовочный файл
	// <algorithm>
	//5а. Выведите на экран элементы ptList1 из предыдущего
	//задания с помощью алгоритма for_each()

    for_each(ptList1.begin(),ptList1.end(), printVec);

	stop;

	//5б.С помощью алгоритма find() найдите итератор на элемент Vector с
	//определенным значением. С помощью алгоритма find_if() найдите
	//итератор на элемент, удовлетворяющий определенному условию, 
	//например, обе координаты точки должны быть больше 2.
	//Подсказка: напишите функцию-предикат, которая проверяет условие
	//и возвращает boolean-значение (предикат может быть как глобальной
	//функцией, так и методом класса)

    auto founded = find(ptList1.begin(),ptList1.end(),Vector(2,2));


	  stop;

	//Создайте список из указателей на элеметы Vector. С помощью 
	//алгоритма find_if() и предиката (можно использовать предикат - 
	//метод класса Vector, определенный в предыдущем задании) найдите в
	//последовательности элемент, удовлетворяющий условию

    list<Vector> lsFind;

    lsFind.emplace_back(1,1);
    lsFind.emplace_back(3,3);
    lsFind.emplace_back(5,5);


    auto foundedIf = find_if(lsFind.begin(),lsFind.end(), vecPred);


	  stop;

	//5в. Создайте список элементов Vector. Наполните список
	//значениями. С помощью алгоритма replace() замените элемент
	//с определенным значением новым значением. С помощью алгоритма
	//replace_if() замените элемент, удовлетворяющий какому-либо
	//условию на определенное значение. Подсказка: условие
	//задается предикатом.

    list<Vector> lsFind2;

    lsFind2.emplace_back(1,1);
    lsFind2.emplace_back(3,3);
    lsFind2.emplace_back(5,5);

    replace(lsFind2.begin(),lsFind2.end(), Vector(1,1),Vector(2,2));
    for_each(lsFind2.begin(),lsFind2.end(), printVec);

    cout << "\n\n";

    replace_if(lsFind2.begin(),lsFind2.end(), vecPred, Vector(10,10));
    for_each(lsFind2.begin(),lsFind2.end(), printVec);
  
	stop;


	//5г. Создайте вектор строк (string). С помощью алгоритма count()
	//сосчитайте количество одинаковых строк. С помощью алгоритма
	//count_if() сосчитайте количество строк, начинающихся с заданной
	//буквы

    vector<string> vecStr = {"One", "Two", "Three", "Four", "Five", "Five"};

    auto counted = count(vecStr.begin(),vecStr.end(), "Five");
    cout << "\n\n" << counted;


    auto countedIf = count_if(vecStr.begin(),vecStr.end(), strPred);

    cout << "\n\n" << countedIf;

	//5д. С помощью алоритма count_if() сосчитайте количество строк,
	//которые совпадают с заданной строкой. Подсказка: смотри тему
	//объекты-функции

    auto countedIf2 = count_if(vecStr.begin(),vecStr.end(), strPred2);

    cout << "\n\n" << countedIf2;

	stop;


	cout <<"\n\n";
}