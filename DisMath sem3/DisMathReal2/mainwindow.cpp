#include "mainwindow.h"
#include <QFont>

const QString func = "1111110111101001";

void MainWindow::populateTruthTable() {
    for (int i = 0; i < 16; ++i) {
        int x1 = (i & 8) ? 1 : 0;
        int x2 = (i & 4) ? 1 : 0;
        int x3 = (i & 2) ? 1 : 0;
        int x4 = (i & 1) ? 1 : 0;

        tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(x1)));
        tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(x2)));
        tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(x3)));
        tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(x4)));

        bool functionValue = func[i]=='1';
        tableWidget->setItem(i, 4, new QTableWidgetItem(functionValue ? "1" : "0"));
    }
}

bool MainWindow::isValidInput(const QString &input) {
    for (QChar ch : input) {
        if (ch != '0' && ch != '1') {
            return false;
        }
    }
    return true;
}

void MainWindow::onCheckButtonClicked() {
    QString result;
    QString input = inputField->text();
    if(input.length() == 4){
        result.append("Результат вычисления с помощью БДР: " + QString::number(bdd.getResult(input)) + "\n\n");
        result.append("Вычисленная СКНФ: " + nf.getSKNF() + "\n" + "Вычисленная СДНФ: " + nf.getSDNF() + "\n" + "Результат вычисления с помощью СДНФ: " + QString::number(nf.calulateBySDNF(input)) + "\n\n");
        result.append("Вычисленный полином Жегалкина: " + polynom.getPol() + "\nРезультат вычисления с помощью полинома Жегалкина: " + QString::number(polynom.getRes(input)));
    }
    res->setText(result);
}

void MainWindow::checkInput()
{
    QString input = inputField->text();
    if (input.length() > 4 || !isValidInput(input)) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, введите 4 цифры (0 или 1).");
        inputField->setText("");
        return;
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Таблица истинности");
    setFixedSize(1200,600);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QWidget *resWidget = new QWidget(this);
    resWidget->setFixedSize(600,550);

    res = new QLabel(resWidget);
    res->setWordWrap(true);
    QFont font = res->font();
    font.setPointSize(16);
    res->setFont(font);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addStretch();
    layout->addWidget(res);
    layout->addStretch();

    resWidget->setLayout(layout);

    tableWidget = new QTableWidget(16, 5, this);
    tableWidget->setHorizontalHeaderLabels(QStringList() << "x" << "y" << "z" << "k" << "65001");
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    populateTruthTable();

    inputField = new QLineEdit(this);
    inputField->setPlaceholderText("Введите 4 цифры (0 или 1)");

    checkButton = new QPushButton("Рассчитать", this);
    connect(checkButton, &QPushButton::clicked, this, &MainWindow::onCheckButtonClicked);

    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->addWidget(tableWidget);

    QVBoxLayout *inResLayout = new QVBoxLayout;

    inResLayout->addWidget(resWidget);

    QHBoxLayout *inputLayout = new QHBoxLayout();
    inputLayout->addWidget(inputField);
    inputLayout->addWidget(checkButton);

    inResLayout->addLayout(inputLayout);
    mainLayout->addLayout(inResLayout);

    connect(inputField, &QLineEdit::textChanged, this, &MainWindow::checkInput);
}
