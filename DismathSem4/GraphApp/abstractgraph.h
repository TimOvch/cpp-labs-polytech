 #ifndef ABSTRACTGRAPH_H
#define ABSTRACTGRAPH_H

#include "matrix.h"
#include "distribution.h"
#include "QString"
#include "QPair"
#include "QQueue"
#include "QStack"

class AbstractGraph
{
protected:
    int p,q;
    int sum;
    Matrix adjacency;
    Matrix weights;
    Matrix adjacencySave;
    Matrix weightsSave;
    Matrix capacities;
    Matrix costs;
    Matrix TakenCaps;
    Matrix Kirchhoff;
    Matrix treeAdj;
    QVector<int> powers;
    QVector<int> level;
    QVector<int> sources;
    QVector<int> Prufer;
    QVector<int> PruferWeights;
    QVector<QVector<int>> degrees;
    QVector<int> unorDegrees;
    QString type;
    QString name;
    bool connected;
    bool acycle;
    bool negativeWeights;
    bool isUnoriented;
    bool hamilton;

    bool bfs(const Matrix& residualGraph, int source, int sink, QVector<int>& parent);

    void generatePowers();

    void Prim();
    void PruferCode();

    void hamiltonianCycleUtil(QVector<int> &path, int pos, QVector<QPair<QVector<int>, int> > &cycles);

    bool isSafe(int v, QVector<int> &path, int pos);

public:
    AbstractGraph(const int& vershini);
    virtual ~AbstractGraph() {}
    virtual void graphGenerate() = 0;
    virtual void acycleGraphGenerate() = 0;

    virtual void addEdge(const int& v, const int& u) = 0;
    Matrix shimbellMethod(const int& times, const bool& max);
    QString edgesDFS(const int& startVertex, const int& endVertex);
    QPair<QVector<int>, QVector<QVector<int>>> dijkstra(const int& startVertex, int& iterations,const bool& by_weights=1);
    QPair<QVector<int>, QVector<QVector<int>>> dijkstraWithNeg(const int& startVertex, int& iterations);
    int fordFulkerson();
    QPair<int, int> minCostFlow();
    int getSpanTreesNum();
    QVector<QPair<int, int>> maxIndependentEdgeSetTree();
    QVector<QPair<int, int>> maxEdgeIndependentSetDAG();
    void countKirchhoff();
    void makeUnoriented();
    QPair<bool,bool> isEuler();
    QPair<QVector<QPair<int,int>>,QVector<QPair<int,int>>> makeEuler(bool& possible);
    QVector<int> eulerCycle();
    QString eulerCycleStr();
    QVector<QPair<QVector<int>, int>> findHamiltonianCycles();
    QVector<QPair<int, int>> makeHamilton();
    QString hamiltonCyclesStr();

    bool checkEdge(const int& startVertex, const int& endVertex);

    class AbstractGraphExeption : public std::exception {
    private:
        std::string text;

    public:

        AbstractGraphExeption(const std::string& error);

        const char* what() const noexcept override;

        virtual ~AbstractGraphExeption() override {}
    };

    QPair<int, QVector<QVector<int>>> countPathsBFS(const int& startVertex, const int& targetVertex);

    int getP() const;
    void setP(const int& newP);
    int getQ() const;
    void setQ(const int& newQ);
    Matrix getAdjacency() const;
    QString getName() const;
    void setName(const QString &newName);
    QString getType() const;
    void loadAdjacency(const Matrix& mat);
    Matrix getWeights() const;
    bool getConnected() const;
    bool getAcycle() const;
    bool getWeighted() const;
    bool getNegativeWeights() const;
    Matrix getCapacities() const;
    Matrix getCosts() const;
    Matrix getTakenCaps() const;
    QPair<QVector<int>,QVector<int>> getPrufer();
    Matrix getKirchhoff() const;
    int getSum() const;
    QPair<QString,QString> getPruferStr();
    bool getIsUnoriented() const;
};

template <typename T>
class IndexedHeap {
public:
    IndexedHeap(int capacity);
    void push(int key, const T& value);
    std::pair<T, int> pop();
    void decreaseKey(int key, const T& newValue);
    bool empty() const;

private:
    QVector<std::pair<T, int>> data;
    QVector<int> indices;
    void heapifyUp(int index);
    void heapifyDown(int index);
    void swapNodes(int i, int j);
};


#endif // ABSTRACTGRAPH_H
