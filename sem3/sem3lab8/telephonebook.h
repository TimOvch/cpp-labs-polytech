  #ifndef TELEPHONEBOOK_H
#define TELEPHONEBOOK_H

// Написать приложение телефонный справочник с использованием библиотеки Qt:
//Обязательные поля для хранения: Имя, Фамилия, Отчество, адрес, дата рождения, email, телефонные номера (рабочий, домашний, служебный) в любом количестве.
//Организовать проверку всех вводимых данных на корректность при помощи регулярных выражений:

//Фамилия, Имя или Отчество --- должны содержать только буквы и цифры различных алфавитов, а также дефис и пробел, но при этом должны начинаться только на буквы, и не могли бы оканчиваться или начинаться на дефис. Все незначимые пробелы перед и после данных должны удаляться.

//Телефон должен быть записан в международном формате, а храниться внутри как последовательность цифр. Один из вариантов записи телефона: префикс_выхода_на международную_линию код_страны код_города телефон. Пример, +7 812 1234567, 8(800)123-1212, + 38 (032) 123 11 11

//Дата рождения должна быть меньше текущей даты, число месяцев в дате должно быть от 1 до 12, число дней от 1 до 31, причем должно учитываться различное число дней в месяце и високосные года. Для обработки даты как вариант можно использовать классы QDateEdit или QCalendarWidget.

//E-mail должен содержать в себе имя пользователя состоящее из латинских букв и цифр, символ разделения пользователя и имени домена(@), а также сам домен состоящий из латинских букв и цифр. Все незначащие пробелы (включая пробелы перед и после символа @) должны быть удалены.

//Приложение должно позволять добавлять/удалять записи, а также редактировать все поля. Осуществлять сортировку отображаемых данных по указанному полю и поиск по нескольким полям.

//Хранение и загрузку данных осуществить ввиде файла, для чтения/записи файла можно использовать класс QFile.

//Для удобного представления данных пользователю, можно использовать таблицы (см. классы QTableWidget, QTableView) + получаем бесплатную сортировку по полям.

#include <QMainWindow>
#include <QString>
#include <QList>
#include <QDate>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QDialog>
#include <QLineEdit>
#include <QComboBox>


class TelephoneBook : public QMainWindow
{
    QTableWidget *tableWidget;
    Q_OBJECT

    void showError(const QString &message);

public:
    explicit TelephoneBook(QWidget *parent = nullptr);


public slots:
    void addRow();
    void deleteRow();

    void search();
    void filter();
    void resetFilter();

    void saveToFileJSON();
    void readFromFileJSON();

    void checkInput(QTableWidgetItem *item);

};

class SearchDialog : public QDialog {
    Q_OBJECT

public:
    SearchDialog(QWidget *parent = nullptr);

    QString getSearchText() const;

    int getSelectedColumn() const;

private slots:
    void onSearchClicked();

private:
    QLineEdit *lineEdit;
    QComboBox *comboBox;
};

class FilterDialog : public QDialog {
    Q_OBJECT

public:
    FilterDialog(QWidget *parent = nullptr);
    QString getSearchText() const;
    int getSelectedColumn() const;

private slots:
    void onFilterClicked();

private:
    QLineEdit *lineEdit;
    QComboBox *comboBox;
};


#endif // TELEPHONEBOOK_H
