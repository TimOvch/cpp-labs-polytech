#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QStringList>

#include "bdd.h"
#include "nf.h"
#include "polynom.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Polynom polynom;
    BDD bdd;
    NormalForms nf;
    QTableWidget *tableWidget;
    QLineEdit *inputField;
    QPushButton *checkButton;
    QLabel *res;

    void populateTruthTable();

    bool isValidInput(const QString &input);

private slots:
    void onCheckButtonClicked();
    void checkInput();

public:
    MainWindow(QWidget *parent = nullptr);
};
#endif // MAINWINDOW_H
