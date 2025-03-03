#include "orientedgraph.h"

OrientedGraph::OrientedGraph(const int &vershini)
    : AbstractGraph(vershini)
{}

void OrientedGraph::graphGenerate()
{
    for (int i = 1; i < p; ++i) {
        int u = QRandomGenerator::global()->bounded(i);
        addEdge(u, i);
    }

    int additionalEdges = QRandomGenerator::global()->bounded((p*(p-1))/2 - p - 1);

    for (int i = 0; i < additionalEdges; ++i) {
        int u = QRandomGenerator::global()->bounded(p);
        int v = QRandomGenerator::global()->bounded(p);

        if (u != v && adjacency.getElem(u,v) == 0) {
            addEdge(u, v);
        } else{
            additionalEdges++;
        }
    }

}

void OrientedGraph::acycleGraphGenerate()
{
    for (int i = 1; i < p; ++i) {
        int u = QRandomGenerator::global()->bounded(i);
        addEdge(i, u);
    }
}

void OrientedGraph::addEdge(const int &v, const int &u)
{
    adjacency.setElement(v,u,1);
}

