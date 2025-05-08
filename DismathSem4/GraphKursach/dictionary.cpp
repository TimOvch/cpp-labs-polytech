#include "dictionary.h"

Dictionary::Dictionary(int size) : tableSize(size), wordCount(0) {
    table.resize(tableSize);
}

Dictionary::~Dictionary() {
    clear();
}

int Dictionary::hashFunction(const QString &word) const {
    unsigned long long hash = 0;
    int prime = 31;
    for (int i = 0; i < word.length(); ++i) {
        hash = (hash * prime + word[i].unicode()) % tableSize;
    }
    return hash;
}

void Dictionary::addWord(const QString &word) {
    int index = hashFunction(word.toLower());
    for (auto &pair : table[index]) {
        if (pair.first == word.toLower()) {
            pair.second++;
            return;
        }
    }
    table[index].append(qMakePair(word.toLower(), 1));
    wordCount++;
}

void Dictionary::removeWord(const QString &word) {
    int index = hashFunction(word);
    for (auto it = table[index].begin(); it != table[index].end(); ++it) {
        if (it->first == word) {
            table[index].erase(it);
            return;
        }
    }
}

int Dictionary::searchWord(const QString &word) const {
    int index = hashFunction(word);
    for (const auto &pair : table[index]) {
        if (pair.first == word) {
            return pair.second;
        }
    }
    return 0;
}

void Dictionary::clear() {
    for (auto &list : table) {
        list.clear();
    }
}

void Dictionary::loadFromFile(const QString &filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Не удалось открыть файл:" << filename;
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QRegularExpression re("[А-Яа-яЁё]+");
        QRegularExpressionMatchIterator it = re.globalMatch(line);

        while (it.hasNext()) {
            QString word = it.next().captured(0);
            if (!word.isEmpty()) {
                addWord(word);
            }
        }
    }
    qDebug() << "Слова загружены из файла:" << filename;
}


int Dictionary::getWordCount() const
{
    return wordCount;
}

int Dictionary::getWordCountAtIndex(int index) const {
    if (index < 0 || index >= tableSize) {
        return 0;
    }
    return table[index].size();
}

QVector<QList<QPair<QString, int> > > Dictionary::getTable() const
{
    return table;
}
