#include "orientedgraph.h"
#include <QRandomGenerator>


QVector<int> findSources(const QVector<QVector<int>>& adjacencyMatrix) {
    QVector<int> sources;
    int n = adjacencyMatrix.size();

    if (n == 0) return sources;

    for (int j = 0; j < n; ++j) {
        bool isSource = true;
        for (int i = 0; i < n; ++i) {
            if (i != j && adjacencyMatrix[i][j] != 0) {
                isSource = false;
                break;
            }
        }
        if (isSource) {
            sources.append(j);
        }
    }

    return sources;
}

OrientedGraph::OrientedGraph(const int &vershini, const bool& negative_weights)
    : AbstractGraph(vershini)
{
    type = "oriented";
    negativeWeights = negative_weights;
}

void OrientedGraph::graphGenerate()
{

}

void OrientedGraph::acycleGraphGenerate()
{
    generatePowers();

    acycle = 1;
    connected = 1;

    Distribution dist(5, 1.1);

    for (int i = 0; i < p ; i++) {
        for (int k = 0; k < powers[p-i-1] ; k++) {
            int j = QRandomGenerator::global()->bounded(p);
            if ( i != j && i < j && adjacency.getElem(i,j) != 1) {
                addEdge(i,j);
                int el = negativeWeights ? dist.getRandom() : std::abs(dist.getRandom());
                while(el == 0){
                    el = negativeWeights ? dist.getRandom() : std::abs(dist.getRandom());
                }
                weights.setElement(i,j,el);

                int cap = std::abs(dist.getRandom());
                while(cap == 0){
                    cap = std::abs(dist.getRandom());
                }
                capacities.setElement(i,j,cap);

                int cost = std::abs(dist.getRandom());
                while(cost == 0){
                    cost = std::abs(dist.getRandom());
                }
                costs.setElement(i,j,cost);

                degrees[i][0]++;
                degrees[j][1]++;
                unorDegrees[i]++;
                unorDegrees[j]++;
            } else{
                k--;
            }
        }
    }

    sources = findSources(adjacency.getData());
    Prim();
    PruferCode();
}

void OrientedGraph::addEdge(const int &v, const int &u)
{
    adjacency.setElement(v,u,1);
    q++;
}

