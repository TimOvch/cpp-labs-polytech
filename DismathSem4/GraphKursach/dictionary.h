#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <QString>
#include <QVector>
#include <QList>
#include <QPair>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <iostream>

class Dictionary {
public:
    Dictionary(int size);
    ~Dictionary();

    void addWord(const QString &word);
    void removeWord(const QString &word);
    int searchWord(const QString &word) const;
    void clear();
    void loadFromFile(const QString &filename);

    int getWordCount() const;
    int getWordCountAtIndex(int index) const;

    QVector<QList<QPair<QString, int> > > getTable() const;

private:
    QVector<QList<QPair<QString, int>>> table;
    int tableSize;
    int wordCount;

    int hashFunction(const QString &word) const;
};


#endif // DICTIONARY_H
