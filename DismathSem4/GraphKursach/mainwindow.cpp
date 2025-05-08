#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    dictionary = new Dictionary(20);
    redBlackTree = new RedBlackTree();

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    wordInput = new QLineEdit(this);
    outputArea = new QTextEdit(this);

    QPushButton *addButton = new QPushButton("Добавить слово", this);
    QPushButton *removeButton = new QPushButton("Удалить слово", this);
    QPushButton *searchButton = new QPushButton("Найти слово", this);
    QPushButton *loadButton = new QPushButton("Загрузить из файла", this);
    QPushButton *inorTraversButton = new QPushButton("Префиксный обход", this);
    QPushButton *bucketCountButton = new QPushButton("Количество слов по бакетам", this);
    QPushButton *clearButton = new QPushButton("Очистить вывод", this);
    QPushButton *generateFileButton = new QPushButton("Сгенерировать файл", this);
    QPushButton *encodeFileButton = new QPushButton("Кодирование", this);


    layout->addWidget(new QLabel("Введите слово:"));
    layout->addWidget(wordInput);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QHBoxLayout* buttonLayout2 = new QHBoxLayout();
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(removeButton);
    buttonLayout->addWidget(searchButton);
    buttonLayout->addWidget(loadButton);
    buttonLayout->addWidget(clearButton);
    buttonLayout->addWidget(inorTraversButton);
    buttonLayout->addWidget(bucketCountButton);
    buttonLayout2->addWidget(generateFileButton);
    buttonLayout2->addWidget(encodeFileButton);

    layout->addLayout(buttonLayout);
    layout->addLayout(buttonLayout2);

    layout->addWidget(new QLabel("Результаты:"));
    layout->addWidget(outputArea);

    connect(addButton, &QPushButton::clicked, this, &MainWindow::onAddWord);
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::onRemoveWord);
    connect(searchButton, &QPushButton::clicked, this, &MainWindow::onSearchWord);
    connect(loadButton, &QPushButton::clicked, this, &MainWindow::onLoadFromFile);
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::clearOutput);
    connect(inorTraversButton, &QPushButton::clicked, this, &MainWindow::inorTravers);
    connect(bucketCountButton, &QPushButton::clicked, this, &MainWindow::bucketCount);
    connect(generateFileButton, &QPushButton::clicked, this, &MainWindow::onGenerateFile);
    connect(encodeFileButton, &QPushButton::clicked, this, &MainWindow::onEncodeFile);
}

MainWindow::~MainWindow() {
    delete dictionary;
    delete redBlackTree;
}

void MainWindow::onAddWord() {
    QString word = wordInput->text().toLower();
    if (!word.isEmpty()) {
        dictionary->addWord(word);
        redBlackTree->insert(word);
        outputArea->append("Добавлено: " + word);
    } else {
        QMessageBox::warning(this, "Ошибка", "Введите слово для добавления.");
    }
}

void MainWindow::onRemoveWord() {
    QString word = wordInput->text();
    if (!word.isEmpty()) {
        dictionary->removeWord(word);
        redBlackTree->remove(word);
        outputArea->append("Удалено: " + word);
    } else {
        QMessageBox::warning(this, "Ошибка", "Введите слово для удаления.");
    }
}

void MainWindow::onSearchWord() {
    QString word = wordInput->text();
    if (!word.isEmpty()) {
        int countInHash = dictionary->searchWord(word);
        Node* result = redBlackTree->search(word);

        QString output = "Результаты поиска для '" + word + "':\n";
        output += "Хеш-таблица: " + QString::number(countInHash) + "\n";

        if (result != nullptr) {
            output += "Красно-черное дерево: " + QString::number(result->count);
        } else {
            output += "Красно-черное дерево: 0";
        }

        outputArea->append(output);
    } else {
        QMessageBox::warning(this, "Ошибка", "Введите слово для поиска.");
    }
}

void MainWindow::onLoadFromFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть файл", "", "Text Files (*.txt)");
    if (!fileName.isEmpty()) {
        dictionary->loadFromFile(fileName);
        redBlackTree->loadFromFile(fileName);
        outputArea->append("Загружены слова из файла: " + fileName);
    }
}

void MainWindow::clearOutput() {
    outputArea->clear();
}

void MainWindow::inorTravers()
{
    QString result = redBlackTree->getAllWords();
    outputArea->setText(result);
}

void MainWindow::bucketCount()
{
    QString res;
    for (int i = 0; i < 20; i++){
        res += "Бакет " + QString::number(i+1) + " : " +QString::number(dictionary->getWordCountAtIndex(i)) + "\n";
    }
    outputArea->setText(res);
}

void MainWindow::onGenerateFile() {
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить файл", "", "Text Files (*.txt)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            const QString characters = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя0123456789!?.,@#$%^&*(){}[] ";
            QString randomString;
            Distribution dist(5, 1.1);
            for (int i = 0; i < 10000; ++i) {
                int index = std::abs((int)dist.getRandom())%(int)(characters.length());
                randomString.append(characters[index]);
            }
            QTextStream out(&file);
            out << randomString;
            file.close();
            outputArea->append("Сгенерирован файл: " + fileName);
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для записи.");
        }
    }
}

void MainWindow::onEncodeFile() {
    FanoEncoderDialog* dial = new FanoEncoderDialog(this);
    dial->exec();
}
