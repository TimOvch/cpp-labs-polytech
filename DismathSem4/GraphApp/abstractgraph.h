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
    Matrix adjacency;
    Matrix weights;
    Matrix capacities;
    QVector<int> powers;
    QVector<int> level;
    QVector<QVector<int>> degrees;
    QString type;
    QString name;
    bool connected;
    bool acycle;
    bool negativeWeights;
    bool flow;

    bool bfs(const Matrix& residualGraph, int source, int sink, QVector<int>& parent);

    void generatePowers();

public:
    AbstractGraph(const int& vershini);
    virtual ~AbstractGraph() {}
    virtual void graphGenerate() = 0;
    virtual void acycleGraphGenerate() = 0;

    virtual void addEdge(const int& v, const int& u) = 0;
    void makeFlow();
    Matrix shimbellMethod(const int& times, const bool& max);
    QString edgesDFS(const int& startVertex, const int& endVertex);
    QPair<QVector<int>, QVector<QVector<int>>> dijkstra(const int& startVertex, int& iterations);
    QPair<QVector<int>, QVector<QVector<int>>> dijkstraWithNeg(const int& startVertex, int& iterations);
    int fordFulkerson(int source, int sink);
    QPair<int, int> minCostFlow(int source, int sink);



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
    bool getFlow() const;
    Matrix getCapacities() const;
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
