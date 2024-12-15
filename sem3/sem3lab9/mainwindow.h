#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QTableView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QToolBar>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QSplitter>
#include <QPointF>
#include <QComboBox>
#include <QLabel>
#include <QStyledItemDelegate>

#include "shapesgraphics.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

    void addShape(const QString& type, int &count);
    void collectRelatedIds(int id, QSet<int> &idsToDelete);
    void drawExisting();
    void typeFilter(QString& type);
    void openFilter();
public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:
    void addRectangle();
    void addEllipse();
    void addTriangle();

    void deleteSelected();
    void relateSelected();
    void detachSelectedFromAll();

public slots:
    void filterRects();
    void filterEllipses();
    void filterTriangles();
    void unFilter();
    void startFilter();

    void markRelated();

    void posChanged(const int& id, const int& x, const int &y);

private:
    QSqlDatabase db;
    QSqlTableModel *model;
    QTableView *tableView;
    ShapesGraphics *graphics;
    QComboBox *filterOption;
    QPushButton* markSelected;
    int ellipseCount;
    int rectCount;
    int triangleCount;
    bool filterActive;
    bool markActive;
};

class ColorDelegate : public QStyledItemDelegate {
public:
    ColorDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};


#endif // MAINWINDOW_H
