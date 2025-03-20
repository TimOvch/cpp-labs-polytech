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
    int graphsCount;
    int activeGraphIndex;

    QTableWidget *adjacencyTable;
    QTableWidget *shimbellTable;
    QTableWidget *weightsTable;
    QTextEdit *graphInfoDisplay;
    GraphView* view;

    QSpinBox *verticesSpin;
    QSpinBox *shimbellSpin;
    QSpinBox *startVertexSpin;
    QSpinBox *endVertexSpin;
    QComboBox *graphTypeCombo;
    QComboBox *shimbellCombo;

    void setupToolBar(QToolBar *toolBar, GraphApp *app);

private slots:

    void generateGraph();

    void changeActiveGraph(const int& newActiveGraphIndex);
    void changeTable(QTableWidget *table,const QVector<QVector<int> > &matrix);

    void saveGraphToFile();
    void loadGraphFromFile();

    void shimbellMethod();

    void findPaths();
};

#endif // GRAPHAPP_H
