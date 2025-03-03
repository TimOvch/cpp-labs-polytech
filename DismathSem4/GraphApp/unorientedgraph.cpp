#include "unorientedgraph.h"
#include <QRandomGenerator>

UnorientedGraph::UnorientedGraph(const int &vershini)
    : AbstractGraph(vershini)
{}

void UnorientedGraph::graphGenerate()
{
    acycleGraphGenerate();

    int additionalEdges = QRandomGenerator::global()->bounded((p*(p-1))/2 - p - 1);

    for (int i = 0; i < additionalEdges; ++i) {
        int u = QRandomGenerator::global()->bounded(p);
        int v = QRandomGenerator::global()->bounded(p);

        if (u != v && adjacency.getElem(u,v) == 0 && adjacency.getElem(v,u) == 0) {
            addEdge(u, v);
        } else{
            additionalEdges++;
        }
    }
}

void UnorientedGraph::acycleGraphGenerate()
{
    for (int i = 1; i < p; ++i) {
        int parent = QRandomGenerator::global()->bounded(i);
        addEdge(parent, i);
    }
}

void UnorientedGraph::addEdge(const int &v, const int &u)
{
    adjacency.setElement(u,v,1);
    adjacency.setElement(v,u,1);
}
