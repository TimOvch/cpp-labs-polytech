#include "mainwindow.h"

void fillTableWithHashTable(QTableWidget* tableWidget,HashTable<QString, int>& hashTable) {
    tableWidget->setRowCount(10);

    tableWidget->setColumnCount(11);
    tableWidget->clear();

    QStringList headers;
    headers << "Bucket Number" << "Values 1" << "Values 2" << "Values 3" << "Values 4"
            << "Values 5" << "Values 6" << "Values 7" << "Values 8" << "Values 9" << "Values 10";
    tableWidget->setHorizontalHeaderLabels(headers);

    for (size_t i = 0; i < 10; ++i) {
        tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(i+1)));

        int bucketSize = hashTable.getBucketSize(i);

        for (size_t j = 0; j < bucketSize && j < 10; ++j) {
            tableWidget->setItem(i, j + 1, new QTableWidgetItem(hashTable.getKeyByBacketAndIndex(i,j)+":"+QString::number(hashTable.getByBacketAndIndex(i,j))));
        }
    }
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), dictionary(hashQString,10) {
    setFixedSize(1200,800);
    redBlackTree = new RedBlackTree();

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    tabwid = new QTabWidget(this);
    tabwid->setFixedSize(1200,400);
    HT = new QTableWidget();
    HT->horizontalHeader()->setStretchLastSection(true);
    HT->verticalHeader()->setStretchLastSection(false);
    HT->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    wordInput = new QLineEdit(this);
    outputArea = new QTextEdit(this);
    treeArea = new QTextEdit(this);

    QPushButton *addButton = new QPushButton("Добавить слово", this);
    QPushButton *removeButton = new QPushButton("Удалить слово", this);
    QPushButton *searchButton = new QPushButton("Найти слово", this);
    QPushButton *loadButton = new QPushButton("Загрузить из файла", this);
    QPushButton *clearSlovariButton = new QPushButton("Очистить словари", this);
    QPushButton *bucketCountButton = new QPushButton("Количество слов по бакетам", this);
    QPushButton *clearButton = new QPushButton("Очистить вывод", this);
    QPushButton *generateFileButton = new QPushButton("Сгенерировать файл", this);
    QPushButton *encodeFileButton = new QPushButton("Кодирование", this);

    tabwid->addTab(HT, "Хеш-таблица");
    tabwid->addTab(treeArea, "Красно-черное дерево");
    fillTableWithHashTable(HT,dictionary);

    layout->addWidget(new QLabel("Введите слово:"));
    layout->addWidget(wordInput);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QHBoxLayout* buttonLayout2 = new QHBoxLayout();
    QHBoxLayout* buttonLayout3 = new QHBoxLayout();
    buttonLayout3->addWidget(addButton);
    buttonLayout3->addWidget(removeButton);
    buttonLayout3->addWidget(searchButton);
    buttonLayout3->addWidget(clearSlovariButton);
    buttonLayout->addWidget(loadButton);
    buttonLayout->addWidget(clearButton);
    buttonLayout->addWidget(bucketCountButton);
    buttonLayout2->addWidget(generateFileButton);
    buttonLayout2->addWidget(encodeFileButton);

    layout->addLayout(buttonLayout3);
    layout->addLayout(buttonLayout);
    layout->addLayout(buttonLayout2);

    layout->addWidget(new QLabel("Результаты:"));
    layout->addWidget(outputArea);
    layout->addWidget(tabwid);

    connect(addButton, &QPushButton::clicked, this, &MainWindow::onAddWord);
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::onRemoveWord);
    connect(searchButton, &QPushButton::clicked, this, &MainWindow::onSearchWord);
    connect(loadButton, &QPushButton::clicked, this, &MainWindow::onLoadFromFile);
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::clearOutput);
    connect(bucketCountButton, &QPushButton::clicked, this, &MainWindow::bucketCount);
    connect(generateFileButton, &QPushButton::clicked, this, &MainWindow::onGenerateFile);
    connect(encodeFileButton, &QPushButton::clicked, this, &MainWindow::onEncodeFile);
    connect(clearSlovariButton, &QPushButton::clicked, this, &MainWindow::onClear);
}

MainWindow::~MainWindow() {
    delete redBlackTree;
}

void MainWindow::onAddWord() {
    QString word = wordInput->text().toLower();
    if (!word.isEmpty()) {
        if(dictionary.contains(word)){
            dictionary[word]++;
        } else{
            dictionary[word] = 1;
        }
        redBlackTree->insert(word);
        outputArea->append("Добавлено: " + word);
        treeArea->setText(redBlackTree->getFirstThreeLevels());
        fillTableWithHashTable(HT,dictionary);
    } else {
        QMessageBox::warning(this, "Ошибка", "Введите слово для добавления.");
    }
}

void MainWindow::onRemoveWord() {
    QString word = wordInput->text();
    if (!word.isEmpty()) {
        if(!dictionary.contains(word) || (redBlackTree->search(word) == nullptr)){
            return;
        }
        dictionary.remove(word);
        redBlackTree->remove(word);
        outputArea->append("Удалено: " + word);
        treeArea->setText(redBlackTree->getFirstThreeLevels());
        fillTableWithHashTable(HT,dictionary);
    } else {
        QMessageBox::warning(this, "Ошибка", "Введите слово для удаления.");
    }
}

void MainWindow::onSearchWord() {
    QString word = wordInput->text();
    if (!word.isEmpty()) {
        int countInHash;
        if(dictionary.contains(word)){
            countInHash = dictionary[word];
        } else{
            countInHash = 0;
        }

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
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Не удалось открыть файл:" << fileName;
            return;
        }

        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QRegularExpression re("[А-Яа-яЁё]+");
            QRegularExpressionMatchIterator it = re.globalMatch(line);

            while (it.hasNext()) {
                QString word = it.next().captured(0).toLower();
                if (!word.isEmpty()) {
                    if(dictionary.contains(word)){
                        dictionary[word]++;
                    } else{
                        dictionary[word] = 1;
                    }

                    qDebug() << word;

                    redBlackTree->insert(word);

                    qDebug() << word;
                }
            }
        }
        file.close();
        fillTableWithHashTable(HT,dictionary);
        qDebug() << "Слова загружены из файла:" << fileName;
        treeArea->setText(redBlackTree->getFirstThreeLevels());
        outputArea->append("Загружены слова из файла: " + fileName);
    }
}

void MainWindow::clearOutput() {
    outputArea->clear();
}

void MainWindow::bucketCount()
{
    QString res;
    for (int i = 0; i < 10; i++){
        res += "Бакет " + QString::number(i+1) + " : " +QString::number(dictionary.bucketSize(i)) + "\n";
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

void MainWindow::onClear()
{
    dictionary.clear();
    redBlackTree->clear();
    treeArea->setText(redBlackTree->getFirstThreeLevels());
    fillTableWithHashTable(HT,dictionary);
}
