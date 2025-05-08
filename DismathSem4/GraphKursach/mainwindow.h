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
#include "dictionary.h"
#include "redblacktree.h"
#include "fano.h"
#include "distribution.h"

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
    void inorTravers();
    void bucketCount();

    void onGenerateFile();
    void onEncodeFile();

private:
    QLineEdit *wordInput;
    QTextEdit *outputArea;
    Dictionary *dictionary;
    RedBlackTree *redBlackTree;
    QString originalText;

    QMap<QString, QString> codeMap;
};

#endif // MAINWINDOW_H
