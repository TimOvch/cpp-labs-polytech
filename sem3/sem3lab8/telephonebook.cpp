#include "telephonebook.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QWidget>
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QRegularExpression>
#include <QDate>
#include <QMessageBox>
#include <QStringList>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QVector>
#include <QFormLayout>

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

bool validateDate(const QString &dateStr) {
    QRegularExpression regex(R"(^((0[1-9]|[12][0-9]|3[01])\.(0[1-9]|1[0-2])\.(19|20)\d{2})$)");
    QRegularExpressionMatch match = regex.match(dateStr);

    if (match.hasMatch()) {
        QStringList dateParts = dateStr.split('.');
        int day = dateParts[0].toInt();
        int month = dateParts[1].toInt();
        int year = dateParts[2].toInt();

        QDate birthDate(year, month, day);

        if (birthDate.isValid() && birthDate < QDate::currentDate()) {
            return true;
        }
    }

    return false;
}

enum Columns{
    Name,
    Surname,
    FathName,
    BirthDate,
    Email,
    PhoneNum
};

QVector<QString> columnsArrRus = {"Имя", "Фамилия", "Отчество", "Дата рождения", "Email", "Телефонные номера"};

TelephoneBook::TelephoneBook(QWidget *parent)
    : QMainWindow{parent}
{
    setWindowTitle("Телефонная книга");
    resize(1000,600);

    tableWidget = new QTableWidget(0, columnsArrRus.size(), this);
    tableWidget->setHorizontalHeaderLabels(QStringList() << "Имя" << "Фамилия" << "Отчество" << "Дата рождения" << "Email" << "Телефонные номера");

    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    setCentralWidget(tableWidget);
    tableWidget->setSortingEnabled(true);

    QMenu *fileMenu = menuBar()->addMenu("Файл");

    QAction *saveJsonAction = new QAction("Сохранить в JSON", this);
    connect(saveJsonAction, &QAction::triggered, this, &TelephoneBook::saveToFileJSON);
    fileMenu->addAction(saveJsonAction);

    QAction *readJsonAction = new QAction("Открыть файл JSON", this);
    connect(readJsonAction, &QAction::triggered, this, &TelephoneBook::readFromFileJSON);
    fileMenu->addAction(readJsonAction);

    QToolBar * ptb = new QToolBar("Работа с контактами");
    ptb->addAction("Добавить контакт в конец", this, &TelephoneBook::addRow);
    ptb->addAction("Удалить выбранный контакт", this, &TelephoneBook::deleteRow);
    ptb->addAction("Поиск контакта", this, &TelephoneBook::search);
    addToolBar(Qt::TopToolBarArea, ptb);

    menuBar()->addMenu(fileMenu);
    menuBar()->show();

    connect(tableWidget, &QTableWidget::itemChanged, this, &TelephoneBook::checkInput);

    int rowCount = tableWidget->rowCount();
    tableWidget->insertRow(rowCount);
}

void TelephoneBook::addRow()
{
    int rowCount = tableWidget->rowCount();
    tableWidget->insertRow(rowCount);
}

void TelephoneBook::deleteRow()
{
    int currentRow = tableWidget->currentRow();
    if (currentRow >= 0) {
        tableWidget->removeRow(currentRow);
    } else {
        QMessageBox::warning(this, "Ошибка", "Сначала выберите контакт для удаления.");
    }
}

void TelephoneBook::search()
{
    SearchDialog dialog(this);
    if(dialog.exec() == QDialog::Accepted) {
        Columns column = (Columns)dialog.getSelectedColumn();
        QString searchText = dialog.getSearchText();
        for (int row = 0; row < tableWidget->rowCount(); ++row) {
            QTableWidgetItem *item = tableWidget->item(row, column);
            if (item && item->text().contains(searchText, Qt::CaseInsensitive)) {
                tableWidget->selectRow(row);
                return;
            }
        }
        QMessageBox::information(this, "Результат поиска", "Запись не найдена.");
    }
}

void TelephoneBook::saveToFileJSON()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить в JSON", "", "JSON Files (*.json)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Ошибка открытия файла.");
        return;
    }

    QJsonArray jsonArray;

    for (int row = 0; row < tableWidget->rowCount(); ++row) {
        QJsonObject jsonObject;
        for (int col = 0; col < tableWidget->columnCount(); ++col) {
            QTableWidgetItem *item = tableWidget->item(row, col);
            jsonObject[columnsArrRus[col]] = item ? item->text() : "";
        }
        jsonArray.append(jsonObject);
    }

    QJsonDocument jsonDoc(jsonArray);
    QByteArray jsonData = jsonDoc.toJson(QJsonDocument::Compact);

    file.write(jsonData);
    file.close();
}

void TelephoneBook::readFromFileJSON()
{
    QString fileName = QFileDialog::getOpenFileName(nullptr, "Открыть JSON", "", "JSON Files (*.json)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Ошибка", "Ошибка открытия файла.");
        return;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);

    if (jsonDoc.isNull() || !jsonDoc.isArray()) {
        QMessageBox::warning(nullptr, "Ошибка", "Неверный формат JSON.");
        return;
    }

    QMessageBox saveMsgBox;

    saveMsgBox.setWindowTitle("Сохранение файла");
    saveMsgBox.setText("Вы хотите сохранить изменения перед выходом?");

    QPushButton *saveButton = saveMsgBox.addButton("Сохранить", QMessageBox::AcceptRole);
    saveMsgBox.addButton("Не сохранять", QMessageBox::RejectRole);

    saveMsgBox.exec();

    if (saveMsgBox.clickedButton() == saveButton) {
        saveToFileJSON();
    }

    tableWidget->sortByColumn(5, Qt::AscendingOrder);
    QJsonArray jsonArray = jsonDoc.array();
    tableWidget->setRowCount(jsonArray.size());

    for (int i = 0; i < jsonArray.size(); ++i) {
        QJsonObject jsonObject = jsonArray[i].toObject();

        for (int j = 0; j < columnsArrRus.size(); ++j) {
            QString key = columnsArrRus[j];
            tableWidget->setItem(i, j, new QTableWidgetItem(jsonObject[key].toString()));
        }
    }
}

void TelephoneBook::showError(const QString &message) {
    QMessageBox::warning(this, "Ошибка ввода", message);
}

void TelephoneBook::checkInput(QTableWidgetItem *item)
{
    if (!item) return;

    QString text = item->text().simplified();
    item->setText(text);
    Columns column = (Columns)item->column();

    QRegularExpression regex;
    if(text.isEmpty()) return;
    switch (column) {
    case Name:
        regex.setPattern("^\\s*[A-Za-zА-Яа-яЁё0-9 ][A-Za-zА-Яа-яЁё0-9\\- ]*[A-Za-zА-Яа-яЁё0-9]\\s*$");
        if (!regex.match(text).hasMatch()) {
            showError("Имя может содержать только буквы и цифры различных алфавитов, а также дефис и пробел, но при этом не может начинаться или оканчиваться на дефис.");
            item->setText("");
        }
        break;
    case Surname:
        regex.setPattern("^\\s*[A-Za-zА-Яа-яЁё0-9 ][A-Za-zА-Яа-яЁё0-9\\- ]*[A-Za-zА-Яа-яЁё0-9]\\s*$");
        if (!regex.match(text).hasMatch()) {
            showError("Фамилия может содержать только буквы и цифры различных алфавитов, а также дефис и пробел, но при этом не может начинаться или оканчиваться на дефис.");
            item->setText("");
        }
        break;
    case FathName:
        regex.setPattern("^\\s*[A-Za-zА-Яа-яЁё0-9 ][A-Za-zА-Яа-яЁё0-9\\- ]*[A-Za-zА-Яа-яЁё0-9]\\s*$");
        if (!regex.match(text).hasMatch()) {
            showError("Отчество может содержать только буквы и цифры различных алфавитов, а также дефис и пробел, но при этом не может начинаться или оканчиваться на дефис.");
            item->setText("");
        }
        break;
    case BirthDate:
        if (!validateDate(text)) {
            showError("Дата рождения должна быть меньше текущей даты, число месяцев в дате должно быть от 1 до 12, число дней от 1 до 31.");
            item->setText("");
        }
        break;
    case Email:
        regex.setPattern("^((?!\\.)[\\w\\-_.]*[^.])(@\\w+)(\\.\\w+(\\.\\w+)?[^.\\W])$");
        if (!regex.match(text).hasMatch()) {
            showError("E-mail должен содержать в себе имя пользователя состоящее из латинских букв и цифр, символ разделения пользователя и имени домена(@), а также сам домен состоящий из латинских букв и цифр.");
            item->setText("");
        }
        break;
    case PhoneNum:
        regex.setPattern("^\\+?(([1-9][0-9][0-9])|([1-9][0-9])|([1-9]))((-)|( )|())(\\(?[0-9][0-9][0-9]\\)?)((-)|( )|())([0-9][0-9][0-9])((-)|( )|())([0-9][0-9])((-)|( )|())([0-9][0-9])$");
        bool flag = true;
        QStringList nums = text.split(',', Qt::SkipEmptyParts);
        for (const QString &number : nums) {
            qDebug() << number;
            if(!regex.match(number.simplified()).hasMatch()){
                flag = false;
            }
        }
        if (!flag) {
            showError("Неверная запись номера телефона.");
            item->setText("");
        }
        break;
    }
}

SearchDialog::SearchDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Поиск");

    // Элементы интерфейса
    QFormLayout *layout = new QFormLayout(this);
    comboBox = new QComboBox(this);
    comboBox->addItem("Имя");
    comboBox->addItem("Фамилия");
    comboBox->addItem("Отчество");
    comboBox->addItem("Дата рождения");
    comboBox->addItem("Email");

    lineEdit = new QLineEdit(this);
    QPushButton *searchButton = new QPushButton("Поиск", this);
    connect(searchButton, &QPushButton::clicked, this, &SearchDialog::onSearchClicked);

    layout->addRow("Выберите колонку:", comboBox);
    layout->addRow("Введите текст для поиска:", lineEdit);
    layout->addWidget(searchButton);
    setLayout(layout);
}

QString SearchDialog::getSearchText() const {
    return lineEdit->text();
}

int SearchDialog::getSelectedColumn() const {
    return comboBox->currentIndex();
}

void SearchDialog::onSearchClicked() {
    accept();
}
