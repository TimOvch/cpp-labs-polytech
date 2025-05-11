#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QPen>
#include <QVBoxLayout>
#include <QLabel>
#include <QInputDialog>
#include <algorithm>
#include <QRandomGenerator>
#include <QFile>
#include <QTabWidget>
#include <QTableWidget>
#include <QHeaderView>
#include "dictionary.h"
#include "redblacktree.h"
#include "fano.h"
#include "distribution.h"
#include "hashtable.h"

struct Symbol {
    QString character;
    float probability;
    QString code;
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddWord();
    void onRemoveWord();
    void onSearchWord();
    void onLoadFromFile();
    void clearOutput();
    void bucketCount();

    void onGenerateFile();
    void onEncodeFile();

    void onClear();

private:
    QLineEdit *wordInput;
    QTextEdit *outputArea;
    QTextEdit *treeArea;
    HashTable<QString,int> dictionary;
    RedBlackTree *redBlackTree;
    QString originalText;
    QTabWidget* tabwid;
    QTableWidget* HT;

    QMap<QString, QString> codeMap;
};

#endif // MAINWINDOW_H
