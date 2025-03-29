#ifndef GRAPHAPP_H
#define GRAPHAPP_H

#include <QApplication>
#include <QMainWindow>
#include <QTableWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVector>
#include <QFrame>
#include <QLabel>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QTabWidget>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QToolButton>
#include <QWidgetAction>
#include <QToolBar>
#include <QHeaderView>
#include <QDockWidget>
#include <QStyledItemDelegate>
#include <QDialog>
#include <QListWidget>
#include <sstream>
#include <QCheckBox>
#include <QHeaderView>

#include "abstractgraph.h"
#include "orientedgraph.h"
#include "unorientedgraph.h"
#include "graphview.h"

class GraphApp : public QMainWindow {
    Q_OBJECT
public:
    GraphApp(QWidget *parent = nullptr);
    virtual ~GraphApp() override;

private:
    QVector<AbstractGraph*> graphs;
    QVector<QVector<int>> dijkstraPaths;
    int graphsCount;
    int activeGraphIndex;
    int dijkstraIterations;
    int dijkstraWithNegIterations;
    int maxCapacity;
    int minCostFlow;
    int minCostFlowCost;

    QTableWidget *adjacencyTable;
    QTableWidget *shimbellTable;
    QTableWidget *weightsTable;
    QTableWidget *dijkstraTable;
    QTextEdit *graphInfoDisplay;
    GraphView* view;

    QSpinBox *verticesSpin;
    QSpinBox *shimbellSpin;
    QSpinBox *startVertexSpin;
    QSpinBox *endVertexSpin;
    QSpinBox *startDfsSpin;
    QSpinBox *endDfsSpin;
    QSpinBox *dijkstraSpin;
    QComboBox *graphTypeCombo;
    QComboBox *shimbellCombo;
    QCheckBox *negativeWeightsCheckBox;
    QCheckBox *negativedijkstraCheckBox;

    void setupToolBar(QToolBar *toolBar, GraphApp *app);
    void refactorSpinBoxes();

private slots:

    void generateGraph();

    void changeActiveGraph(const int& newActiveGraphIndex);
    void changeTable(QTableWidget *table,const QVector<QVector<int> > &matrix);
    void changeInfo();

    void tabChanged(int index);

    void saveGraphToFile();
    void loadGraphFromFile();

    void shimbellMethod();

    void findPaths();
    void handlePathSelected(const QVector<int>& path);

    void edgesDFS();

    void dijkstraAlgorithm();
    void onDijkstraTableClicked(QTableWidgetItem* item);

    void makeFlow();
};




class HighlightNonEmptyDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    HighlightNonEmptyDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};





class PathsDialog : public QDialog {
    Q_OBJECT

public:
    PathsDialog(const QVector<QVector<int>>& paths, QWidget *parent = nullptr);

signals:
    void pathSelected(const QVector<int>& path);

private:
    QListWidget *listWidget;

    std::string formatPath(const QVector<int>& path);

private slots:
    void emitPathSelected(QListWidgetItem *item);

private:
    QVector<QVector<int>> paths;
};

#endif // GRAPHAPP_H
