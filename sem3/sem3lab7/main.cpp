#include "mywidget.h"

#include <QApplication>

// С использованием библиотеки Qt реализовать графический класс содержащий коллекцию фигур: прямоугольников, треугольников, эллипсов.
// В классе должны быть методы для добавления новых фигур и удаления старых. Реализовать графический интерфейс позволяющий проверить работу этих методов.
// Каждая фигура должны представлять из себя объект, который можно перемещать при помощи курсора, а также делать активным (объект поднимается на передний план)
//, при наложении нескольких объектов друг на друга должен перемещаться только активный объект.

// Задание 7.1: Реализовать данное задание с использованием пользовательской модели и рисования на виджетах через перегрузку методов: paintEvent,
// mouse(Press,Move,Release)Event, для упрощения сложные фигуры при определении границ для перемещения можно вписывать в прямоугольник.
// Задание 7.2: Реализовать данное задание с использованием модели графического представления и сцены, в данной реализации границы фигуры должны строго
// контролироваться, можно воспользоваться готовыми классами семейства QGraphicsItem для представления фигур.

// За материалом обращайтесь к Лекции №10, Лекции №12 (стр. 16 и 17).

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyWidget widg;

    widg.show();
    return a.exec();
}
