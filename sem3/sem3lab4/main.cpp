// Контейнеры STL: 
//deque, stack, queue, priority_queue
//set, multiset, map, multimap
//Итераторы. Стандартные алгоритмы. Предикаты.

#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <algorithm>
#include "stack"
#include "queue"
#include "deque"
#include "set"
#include "Rect.h"
#include "MyVector.h"
#include "MyString.h"

using namespace std;	
#define	  stop

template <class T> void pr(T& v, string s)
{
    cout<<"\n\n\t"<<s<<"  # Sequence:\n";

    // Итератор любого контейнера
    typename T::iterator p;
    int i;

    for (p = v.begin(), i=0;  p != v.end();  p++, i++)
        cout << endl << i+1 <<". " << *p;
    cout << '\n';
}

template<class T>
void printStackPriorQueue(T s) {
    int i = 0;
    while (!s.empty()) {
        cout << endl << i+1 <<". " << s.top();
        s.pop();
        i++;
    }
    cout << endl;
}

template<class T>
void printQueue(T q) {
    int i = 0;
    while (!q.empty()) {
        cout << endl << i+1 <<". " << q.front();
        q.pop();
        i++;
    }
    cout << endl;
}

template<class T>
void forEach(T&elem){
    cout<< '\n' << elem;
}

void changeVec(Vector& vec){
    Vector mv(5,5);
    vec.Move(mv);
}

bool Pred1_1(const Vector& vec){
    return ((vec.getX() > -1) && (vec.getX()<5) && (vec.getY() > -1) && (vec.getY() < 5));
}

bool compareByDistance(const Rect& r1, const Rect& r2) {
    return r1.distanceFromOrigin() < r2.distanceFromOrigin();
}

int main()
{
    setlocale(LC_ALL, "Russian");
	//Очередь с двумя концами - контейнер deque

	//Создайте пустой deque с элементами типа Point. С помощью
	//assign заполните deque копиями элементов вектора. С помощью
	//разработанного Вами в предыдущем задании универсального шаблона
	//выведите значения элементов на печать

    vector<Vector> vecVec(3,Vector(3,5));
    deque<Vector> vecDec;

    vecDec.assign(vecVec.begin(), vecVec.end());

    pr(vecDec, "Deque test");

	//Создайте deque с элементами типа MyString. Заполните его значениями
	//с помощью push_back(), push_front(), insert()
	//С помощью erase удалите из deque все элементы, в которых строчки
	//начинаются с 'A' или 'a'

    deque<MyString> strDec;

    strDec.push_back("astring");
    strDec.push_front("Astring");
    strDec.insert(strDec.begin(), "bstring");

    for(auto it = strDec.begin(); it!=strDec.end()--;){
        if(it->GetString()[0] == 'a' || it->GetString()[0] == 'A'){
            strDec.erase(it);
        } else{
            ++it;
        }
    }


	////////////////////////////////////////////////////////////////////////////////////


	//Напишите шаблон функции для вывода значений stack, queue, priority_queue
	//Подумайте, как "получать" данное "с верхушки"?
	//Что происходит с контейнерами после вывода значений?

    stack<double> prStack;

    prStack.push(1);
    prStack.push(9.33);
    prStack.push(0.44);

    printStackPriorQueue(prStack);
	////////////////////////////////////////////////////////////////////////////////////
	//stack

	//Создайте стек таким образом, чтобы
	//а) элементы стека стали копиями элементов вектора
	//б) при выводе значений как вектора, так и стека порядок значений был одинаковым 

    vector<int> copyVec = {1,5,2,7,3,8};
    stack<int> copyStack;

    for(auto it = copyVec.end()-1; it != copyVec.begin()-1;it--){
        copyStack.push(*it);
    }


    pr(copyVec,"Vector");

    printStackPriorQueue(copyStack);

	//Сравнение и копирование стеков
	//а) создайте стек и любым способом задайте значения элементов
	//б) создайте новый стек таким образом, чтобы он стал копией первого
	//в) сравните стеки на равенство
	//г) модифицируйте любой из стеком любым образом (push, pop, top)
	//д) проверьте, какой из стеков больше (подумайте, какой смысл вкладывается в такое сравнение)
	{
	    stack<int> forCopy;

        forCopy.push(3);
        forCopy.push(1);
        forCopy.push(8);
        forCopy.push(4);

        stack<int> copy = forCopy;

        cout << "\n\nStack are equal: " << (copy == forCopy);

        forCopy.push(9);

        if(forCopy.size() > copy.size()){
            cout << "\n\nforCopy is bigger";
        } else {
            cout << "\n\ncopy is bigger";
        }

	    stop

	}


	////////////////////////////////////////////////////////////////////////////////////
	//queue

	//Создайте очередь, которая содержит указатели на объекты типа Point,
	//при этом явно задайте базовый контейнер.
	//Измените значения первого и последнего элементов посредством front() и back()
	//Подумайте, что требуется сделать при уничтожении такой очереди?
	{
        queue<Vector, list<Vector>> vecQue;

        vecQue.front() = Vector(1,4);
        vecQue.back() = Vector(5,3);


	}
	////////////////////////////////////////////////////////////////////////////////////
	//priority_queue
	//а) создайте очередь с приоритетами, которая будет хранить адреса строковых литералов - const char*
	//б) проинициализируйте очередь при создании с помощью вспомогательного массива с элементами const char*
	//в) проверьте "упорядоченность" значений (с помощью pop() ) - если они оказываются не упорядоченными, подумайте:
	//		что сравнивается при вставке?


	{
        const char* mas[] = {"ab", "bb", "cb", "db", "eb", "hb"};

	    priority_queue<const char*> conChPriorQue(mas,mas+6);

        cout << "\n\nPriority queue test:";

        printStackPriorQueue(conChPriorQue); // сравнивается по адресу в памяти

		stop
	}
	
	
	////////////////////////////////////////////////////////////////////////////////////
	//set
	//a) создайте множество с элементами типа Point - подумайте, что необходимо определить
	//		в классе Point (и каким образом) Необходимо переопределить операторы == и <
	//б) распечатайте значения элементов с помощью шаблона, реализованного в предыдущей лаб. работе
	//в) попробуйте изменить любое значение...
	//г) Создайте два множества, которые будут содержать одинаковые значения
	//		типа int, но занесенные в разном порядке
	//д) Вставьте в любое множество диапазон элементов из любого другого
	//	контейнера, например, элементов массива	(что происходит, если в массиве имеются дубли?)

    set<Vector> vecSet = {Vector(4,2), Vector(1,44), Vector(3,5), Vector(8,9), Vector(4,2)};

    pr(vecSet, "Testing vector set:");


    set<int> intSet1 = {1,2,3,4,5}, intSet2 = {5,4,3,2,1};

    pr(intSet1, "Increasing order set:");
    pr(intSet2, "Decreasing order set:");

    int masInt[] = {7,7,4,3,9,0,23,23};

    set<int> intSet3(masInt,masInt+8);

    pr(intSet3, "Set for array {7,7,4,3,9,0,23,23}:");


	////////////////////////////////////////////////////////////////////////////////////
	//multiset
    multiset<int> intMultiSet(masInt,masInt+8);

    pr(intMultiSet, "Multi Set for array {7,7,4,3,9,0,23,23}:");

	////////////////////////////////////////////////////////////////////////////////////
	//map	
	//а) создайте map, который хранит пары "фамилия, зарплата" - pair<const char*, int>,
	//	при этом строки задаются строковыми литералами
	//б) заполните контейнер значениями посредством operator[] и insert()
	//в) распечатайте содержимое

    map<const char*,int> surnameSalary;

    const char* Ivanova = "Ivanova";

    surnameSalary[Ivanova] = 60000;
    surnameSalary["Kan"] = 120000;
    surnameSalary.insert({"Kurbanov", 400000});
    surnameSalary.insert(pair<const char*, int>("Sahanov",90000));

    for (auto &elem:surnameSalary) {
        cout << "\nSurname: " << elem.first << ", Salary: " << elem.second;
    }

	//е) замените один из КЛЮЧЕЙ на новый (была "Иванова", вышла замуж => стала "Петрова")

    auto it = surnameSalary.begin();
    while(it!=surnameSalary.end()){
        if(it->first == Ivanova){
            surnameSalary.erase(it);
            surnameSalary["Petrova"] = 60000;
            break;
        }
    }

	stop
	


	////////////////////////////////////////////////////////////////////////////////////
	//multimap
	//а) создайте "англо-русский" словарь, где одному и тому же ключу будут соответствовать
	//		несколько русских значений - pair<string,string>, например: strange: чужой, странный...
	//б) Заполните словарь парами с помощью метода insert или проинициализируйте с помощью 
	//		вспомогательного массива пара (пары можно конструировать или создавать с помощью шаблона make_pair)
	//в) Выведите все содержимое словаря на экран
	//г) Выведите на экран только варианты "переводов" для заданного ключа. Подсказка: для нахождения диапазона
	//		итераторов можно использовать методы lower_bound() и upper_bound()

    multimap<string,string> EngRus;

    EngRus.insert({"strange","странный"});
    EngRus.insert({"strange","чужой"});

    EngRus.insert({"map","карта"});
    EngRus.insert({"map","словарь"});

    EngRus.insert({"round","круг"});
    EngRus.insert({"round","раунд"});

    for (auto &elem:EngRus) {
        cout << "\nEnglish: " << elem.first << ", Russian: " << elem.second;
    }
    cout << '\n';

    auto upper = EngRus.upper_bound("map");
    auto lower = EngRus.lower_bound("map");

    cout << "Translations for map: ";
    for (auto it = lower; it != upper; ++it) {
        cout << it->second << '\n';

    }
    cout << "\n\n ";
///////////////////////////////////////////////////////////////////

	//Итераторы

	//Реверсивные итераторы. Сформируйте set<Point>. Подумайте, что
	//нужно перегрузить в классе Point. Создайте вектор, элементы которого 
	//являются копиями элементов set, но упорядочены по убыванию

    set<Vector> vecSet2 = {{1,1},{2,2},{3,3},{4,4}};

    pr(vecSet2, "Set for reversing");

    vector<Vector> vecVec2(vecSet2.rbegin(),vecSet2.rend());

    pr(vecVec2, "Reversed vector:");
	//Потоковые итераторы. С помощью ostream_iterator выведите содержимое
	//vector и set из предыдущего задания на экран.

    copy(vecVec2.begin(), vecVec2.end(), ostream_iterator<Vector>(cout, " "));

    cout << '\n';

    copy(vecSet2.begin(), vecSet2.end(), ostream_iterator<Vector>(cout, " "));
	//Итераторы вставки. С помощью возвращаемых функциями:
	//back_inserter()
	//front_inserter()
	//inserter()
	//итераторов вставки добавьте элементы в любой из созданных контейнеров. Подумайте:
	//какие из итераторов вставки можно использовать с каждым контейнером.

    vector<int> backIns, toInsert = {1,2,3,4,5};

    list<int> frontIns;

    set<int> ins;

    copy(toInsert.begin(),toInsert.end(), back_inserter(backIns));

    pr(backIns,"Back inserter:");

    copy(toInsert.begin(),toInsert.end(), front_inserter(frontIns));

    pr(frontIns,"Front inserter:");

    copy(toInsert.begin(),toInsert.end(), inserter(ins,ins.end()));

    pr(frontIns,"Front inserter:");

///////////////////////////////////////////////////////////////////

	//Обобщенные алгоритмы (заголовочный файл <algorithm>). Предикаты.

	// алгоритм for_each() - вызов заданной функции для каждого элемента любой последовательности
	//(массив, vector, list...)
	//С помощью алгоритма for_each в любой последовательности с элементами любого типа
	//распечатайте значения элементов
	//Подсказка : неплохо вызываемую функцию определить как шаблон

    vector<int> frEch = {4,6,7,9,0,123};

    for_each(frEch.begin(),frEch.end(), forEach<int>);

	stop

	//С помощью алгоритма for_each в любой последовательности с элементами типа Point
	//измените "координаты" на указанное значение (такой предикат тоже стоит реализовать 
	//как шаблон) и выведите результат с помощью предыдущего предиката

    for_each(vecVec2.begin(),vecVec2.end(), changeVec);

    for_each(vecVec2.begin(),vecVec2.end(), forEach<Vector>);


	//С помощью алгоритма find() найдите в любой последовательности элементов Point
	//все итераторы на элемент Point с указанным значением.


    vector<vector<Vector>::iterator> iters;

    auto begin = vecVec.begin();

    while (begin!=vecVec.end()){
        begin = find(begin,vecVec.end(),Vector(3,5));
        if(begin!=vecVec.end()) iters.push_back(begin);
        ++begin;
    }


	//С помощью алгоритма sort() отсортируйте любую последовательность элементов Point. 
	////По умолчанию алгоритм сортирует последовательность по возрастанию.
	//Что должно быть определено в классе Point?
	// Замечание: обобщенный алгоритм sort не работает со списком, так как
	//это было бы не эффективно => для списка сортировка реализована методом класса!!!
	
    vector<Vector> forSort = {Vector(5,5),Vector(4,4),Vector(3,3),Vector(2,2),Vector(1,1)};

    pr(forSort,"Before sort:");

    sort(forSort.begin(),forSort.end());

    pr(forSort,"After sort:");

	//Создайте глобальную функцию вида: bool Pred1_1(const Point& ), которая будет вызываться
	//алгоритмом find_if(), передавая в качестве параметра очередной элемент последовательности.
	//С помощью алгоритма find_if() найдите в любой последовательности элементов Point
	//итератор на элемент Point, удовлетворяющий условию: координаты x и y лежат в промежутке
	//[-n, +m].

    auto needed = find_if(vecVec2.begin(),vecVec2.end(), Pred1_1);

	//С помощью алгоритма sort() отсортируйте любую последовательность элементов Rect,
	//располагая прямоугольники по удалению центра от начала координат.

    vector<Rect> rectangles = {Rect(1, 2, 4, 5),Rect(-1, -3, 2, 2),Rect(3, 3, 1, 1)};

    sort(rectangles.begin(), rectangles.end(), compareByDistance);


	{//transform
		//Напишите функцию, которая с помощью алгоритма transform переводит 
		//содержимое объекта string в нижний регистр.
		//Подсказка: класс string - это "почти" контейнер, поэтому для него
		// определены методы begin() и end()
        string str = "Hello, World!";

        transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return tolower(c); });

		//Заполните list объектами string. С помощью алгоритма transform сформируте
		//значения "пустого" set, конвертируя строки в нижний регистр
	
        list<string> strLst = {"Test","teST","Red","Green","grEEn"};

        set<string> strSet;

        for(auto&elem:strLst){
            transform(elem.begin(), elem.end(), elem.begin(), [](unsigned char c) { return tolower(c); });
            strSet.insert(elem);
        }



		stop
	}
	{// map
		
		//Сформируйте любым способом вектор с элементами типа string.
		//Создайте (и распечатайте для проверки) map<string, int>, который будет
		//содержать упорядоченные по алфавиту строки и
		//количество повторений каждой строки в векторе
        list<string> strLst = {"Test","teST","Red","Green","grEEn"};

        map<string,int> strIntMap;

        for(auto&elem:strLst){
            transform(elem.begin(), elem.end(), elem.begin(), [](unsigned char c) { return tolower(c); });
        }

        for(auto&elem:strLst){
            if(strIntMap.find(elem) == strIntMap.end()){
                strIntMap.insert({elem,1});
            } else{
                strIntMap[elem]+=1;
            }
        }


	}

	


	return 0;
}

