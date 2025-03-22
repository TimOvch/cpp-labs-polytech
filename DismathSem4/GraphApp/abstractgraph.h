 #ifndef ABSTRACTGRAPH_H
#define ABSTRACTGRAPH_H

#include "matrix.h"
#include "distribution.h"
#include "QString"
#include "QPair"

class AbstractGraph
{
protected:
    int p,q;
    Matrix adjacency;
    Matrix weights;
    QVector<int> powers;
    QString type;
    QString name;
    bool connected;
    bool acycle;
    bool negativeWeights;

    void generatePowers();

public:
    AbstractGraph(const int& vershini);
    virtual ~AbstractGraph() {}
    virtual void graphGenerate() = 0;
    virtual void acycleGraphGenerate() = 0;

    virtual void addEdge(const int& v, const int& u) = 0;
    Matrix shimbellMethod(const int& times, const bool& max);
    QString edgesDFS(const int& startVertex, const int& endVertex);
    QVector<int> dijkstra(const int& startVertex);

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
};

#endif // ABSTRACTGRAPH_H
