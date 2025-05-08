#include "fano.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <algorithm>
#include <QVector>
#include <QDebug>
#include <stdexcept>
#include <cmath>

FanoEncoderDialog::FanoEncoderDialog(QWidget *parent)
    : QDialog(parent), inputFilePath(""), outputFilePath(""), decodeOutputFilePath("") {

    inputFileLabel = new QLabel("Выберите входной файл");
    outputFileLabel = new QLabel("Выберите выходной файл");
    decodeOutputFileLabel = new QLabel("Выберите файл для декодирования");

    inputFileButton = new QPushButton("Выбрать входной файл");
    outputFileButton = new QPushButton("Выбрать файл для кодирования");
    decodeOutputFileButton = new QPushButton("Выбрать файл для декодирования");

    encodeButton = new QPushButton("Закодировать Фано");
    decodeButton = new QPushButton("Декодировать Фано");
    QPushButton* twoStageEncodeButton = new QPushButton("Двухступенчатое кодирование");
    QPushButton* twoStageDecodeButton = new QPushButton("Двухступенчатое декодирование");
    compareButton = new QPushButton("Сравнить файлы");
    QPushButton* ishodButton = new QPushButton("Отобразить исходный файл");

    codeOutput = new QTextEdit();
    encodedData = new QTextEdit();
    decodedData = new QTextEdit();
    codeOutput->setReadOnly(true);
    encodedData->setReadOnly(true);
    decodedData->setReadOnly(true);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    QWidget * mainWidget = new QWidget(this);
    QWidget * coddecWidget = new QWidget(this);
    QVBoxLayout *coddecLayout = new QVBoxLayout();
    QHBoxLayout *mainmainLayout = new QHBoxLayout();

    mainLayout->addWidget(inputFileLabel);
    mainLayout->addWidget(inputFileButton);


    mainLayout->addWidget(outputFileLabel);
    mainLayout->addWidget(outputFileButton);


    mainLayout->addWidget(decodeOutputFileLabel);
    mainLayout->addWidget(decodeOutputFileButton);

    mainLayout->addWidget(encodeButton);
    mainLayout->addWidget(decodeButton);
    mainLayout->addWidget(twoStageEncodeButton);
    mainLayout->addWidget(twoStageDecodeButton);
    mainLayout->addWidget(codeOutput);
    mainWidget->setLayout(mainLayout);
    mainLayout->addWidget(compareButton);
    mainLayout->addWidget(ishodButton);
    mainWidget->setFixedSize(400,600);

    coddecLayout->addWidget(encodedData);
    coddecLayout->addWidget(decodedData);
    coddecWidget->setLayout(coddecLayout);
    coddecWidget->setFixedSize(600,600);

    mainmainLayout->addWidget(mainWidget);
    mainmainLayout->addWidget(coddecWidget);

    setLayout(mainmainLayout);
    setWindowTitle("Алгоритм Фано");

    connect(inputFileButton, &QPushButton::clicked, this, &FanoEncoderDialog::selectInputFile);
    connect(outputFileButton, &QPushButton::clicked, this, &FanoEncoderDialog::selectOutputFile);
    connect(decodeOutputFileButton, &QPushButton::clicked, this, &FanoEncoderDialog::selectDecodeOutputFile);
    connect(encodeButton, &QPushButton::clicked, this, &FanoEncoderDialog::encode);
    connect(decodeButton, &QPushButton::clicked, this, &FanoEncoderDialog::decode);
    connect(twoStageEncodeButton, &QPushButton::clicked, this, &FanoEncoderDialog::twoStepsEnc);
    connect(twoStageDecodeButton, &QPushButton::clicked, this, &FanoEncoderDialog::twoStepsDec);
    connect(compareButton, &QPushButton::clicked, this, &FanoEncoderDialog::compareEncodedToOriginal);
    connect(ishodButton, &QPushButton::clicked, this, &FanoEncoderDialog::setIshod);
}

FanoEncoderDialog::~FanoEncoderDialog() {}

void FanoEncoderDialog::selectInputFile() {
    inputFilePath = QFileDialog::getOpenFileName(this, "Выберите входной файл", QString(), "Text Files (*.txt);;All Files (*)");
    inputFileLabel->setText(inputFilePath.isEmpty() ? "Выберите входной файл" : inputFilePath);
}

void FanoEncoderDialog::selectOutputFile() {
    outputFilePath = QFileDialog::getSaveFileName(this, "Выберите файл для кодирования", QString(), "Text Files (*.txt);;All Files (*)");
    outputFileLabel->setText(outputFilePath.isEmpty() ? "Выберите файл для кодирования" : outputFilePath);
}

void FanoEncoderDialog::selectDecodeOutputFile() {
    decodeOutputFilePath = QFileDialog::getSaveFileName(this, "Выберите файл для декодирования", QString(), "Text Files (*.txt);;All Files (*)");
    decodeOutputFileLabel->setText(decodeOutputFilePath.isEmpty() ? "Выберите файл для декодирования" : decodeOutputFilePath);
}

void FanoEncoderDialog::compareFiles(const QString &file1Path, const QString &file2Path) {
    QFile file1(file1Path);
    QFile file2(file2Path);

    if (!file1.open(QIODevice::ReadOnly | QIODevice::Text) || !file2.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть один из файлов для сравнения.");
        return;
    }

    QTextStream in1(&file1);
    QTextStream in2(&file2);

    int position = 0;
    while (!in1.atEnd() && !in2.atEnd()) {
        QString line1 = in1.readLine();
        QString line2 = in2.readLine();

        if (line1 != line2) {
            QMessageBox::information(this, "Результат сравнения",
                                     QString("Файлы различаются на позиции %1:\n\nФайл 1: \"%2\"\nФайл 2: \"%3\"")
                                         .arg(position).arg(line1).arg(line2));
            file1.close();
            file2.close();
            return;
        }

        position += line1.length() + 1;
    }

    if (!in1.atEnd() || !in2.atEnd()) {
        QMessageBox::information(this, "Результат сравнения", "Файлы имеют разную длину.");
    } else {
        QMessageBox::information(this, "Результат сравнения", "Файлы совпадают.");
    }

    file1.close();
    file2.close();
}

void FanoEncoderDialog::compareEncodedToOriginal() {
    if (inputFilePath.isEmpty() || outputFilePath.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, выберите файлы для сравнения.");
        return;
    }
    compareFiles(inputFilePath, outputFilePath);
}

void FanoEncoderDialog::twoStepsEnc()
{
    if (inputFilePath.isEmpty() || outputFilePath.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, выберите оба файла.");
        return;
    }

    QFile inputFile(inputFilePath);
    if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть входной файл.");
        return;
    }

    QTextStream in(&inputFile);
    QString inputText = in.readAll();
    inputFile.close();

    QString outputText = twoStepsEncoding(inputText);
    double sj = ((double)(inputText.length()*32))/((double)outputText.length());
    QString info = QString("Коэффициент сжатия : %1\n").arg(sj);
    codeOutput->setPlainText(info);

    QFile outputFile(outputFilePath);
    if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть выходной файл.");
        return;
    }

    QTextStream out(&outputFile);
    out << outputText;
    encodedData->setPlainText(outputText);
    outputFile.close();
}

void FanoEncoderDialog::twoStepsDec()
{
    if (inputFilePath.isEmpty() || decodeOutputFilePath.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, выберите файл для декодирования.");
        qDebug() << inputFilePath << decodeOutputFilePath;
        return;
    }

    QFile inputFile(inputFilePath);
    if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть входной файл.");
        return;
    }

    QTextStream in(&inputFile);
    QString inputText = in.readAll();
    inputFile.close();


    if (inputText.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Закодированные данные отсутствуют.");
        return;
    }

    QString outputText = twoStepsDecoding(inputText);

    QFile outputFile(decodeOutputFilePath);
    if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть выходной файл декодирования.");
        return;
    }

    QTextStream out(&outputFile);
    out << outputText;
    decodedData->setPlainText(outputText);
    outputFile.close();
}

void FanoEncoderDialog::setIshod()
{
    QFile inputFile(inputFilePath);
    if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть входной файл.");
        return;
    }

    QTextStream in(&inputFile);
    QString inputText = in.readAll();
    encodedData->setPlainText(inputText);
    inputFile.close();
}

void FanoEncoderDialog::encode() {
    if (inputFilePath.isEmpty() || outputFilePath.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, выберите оба файла.");
        return;
    }

    QFile inputFile(inputFilePath);
    if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть входной файл.");
        return;
    }

    QTextStream in(&inputFile);
    QString inputText = in.readAll();
    QStringList formattedCodes;
    double ck = 0, sj = 0;
    inputFile.close();

    QString outputText = encodeFano(inputText,formattedCodes,ck,sj);

    QFile outputFile(outputFilePath);
    if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть выходной файл.");
        return;
    }

    QTextStream out(&outputFile);
    out << outputText;
    encodedData->setPlainText(outputText);
    outputFile.close();

    codeOutput->setPlainText(formattedCodes.join("\n"));
}

void FanoEncoderDialog::decode() {
    if (inputFilePath.isEmpty() || decodeOutputFilePath.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, выберите файл для декодирования.");
        qDebug() << inputFilePath << decodeOutputFilePath;
        return;
    }

    QFile inputFile(inputFilePath);
    if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть входной файл.");
        return;
    }

    QTextStream in(&inputFile);
    QString inputText = in.readAll();
    inputFile.close();


    if (inputText.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Закодированные данные отсутствуют.");
        return;
    }

    QString outputText = decodeFano(inputText);

    QFile outputFile(decodeOutputFilePath);
    if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть выходной файл декодирования.");
        return;
    }

    QTextStream out(&outputFile);
    out << outputText;
    decodedData->setPlainText(outputText);
    outputFile.close();
}

