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
#include <QTabBar>
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
#include <QStylePainter>

#include "abstractgraph.h"
#include "orientedgraph.h"
#include "unorientedgraph.h"
#include "graphview.h"
#include "pruferwidget.h"

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
    int spanTreesNum;
    int primSum;
    int minSetGraph;
    int minSetTree;
    bool euler;
    bool halfEuler;
    QString prufersCode;
    QString prufersWeights;
    QString eulerCycle;
    QString hamilCycle;

    QTableWidget *adjacencyTable;
    QTableWidget *shimbellTable;
    QTableWidget *weightsTable;
    QTableWidget *dijkstraTable;
    QTableWidget *capacityTable;
    QTableWidget *costsTable;
    QTableWidget *takenCapabilityTable;
    QTableWidget *kirchgoff;
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
    QComboBox *showCombo;
    QCheckBox *negativeWeightsCheckBox;
    QCheckBox *negativedijkstraCheckBox;
    QCheckBox *showWeightsCheckBox;
    QCheckBox *showCapacitiesCheckBox;
    QCheckBox *showCostsCheckBox;
    QCheckBox *showSetsCheckBox;
    QCheckBox *showCycleEdgesBox;

    void setupToolBar(QToolBar *toolBar, GraphApp *app);
    void refactorSpinBoxes();

private slots:

    void generateGraph();

    void changeActiveGraph(const int& newActiveGraphIndex);
    void changeTable(QTableWidget *table,const QVector<QVector<int> > &matrix);
    void changeView();
    void changeTypeView(int index);
    void changeInfo();

    void tabChanged(int index);
    void setsChanges();

    void saveGraphToFile();
    void loadGraphFromFile();

    void shimbellMethod();

    void findPaths();
    void handlePathSelected(const QVector<int>& path);

    void edgesDFS();

    void dijkstraAlgorithm();
    void onDijkstraTableClicked(QTableWidgetItem* item);

    void spanNum();

    void openPruferWidget();

    void makeEuler();
    void makeHamilton();
    void showHamCycle();
    void showCycleEdges(bool high);
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
    PathsDialog(const QVector<QVector<int>>& pths, QWidget *parent = nullptr, QVector<int> wghts = QVector<int>(0));

signals:
    void pathSelected(const QVector<int>& path);

private:
    QListWidget *listWidget;

    std::string formatPath(const QVector<int>& path);

private slots:
    void emitPathSelected(QListWidgetItem *item);

private:
    QVector<QVector<int>> paths;
    QVector<int> weights;
};


#endif // GRAPHAPP_H
