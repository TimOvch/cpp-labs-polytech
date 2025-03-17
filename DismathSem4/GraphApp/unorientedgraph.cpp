#include "unorientedgraph.h"
#include <QRandomGenerator>

UnorientedGraph::UnorientedGraph(const int &vershini)
    : AbstractGraph(vershini)
{
    type = "unoriented";
}

void UnorientedGraph::graphGenerate()
{

}

void UnorientedGraph::acycleGraphGenerate()
{
    generatePowers();

    for (int i = 0; i < p ; i++) {
        for (int k = 0; k < powers[p-i-1] ; k++) {
            int j = QRandomGenerator::global()->bounded(p);
            if ( i != j && i < j && adjacency.getElem(i,j) != 1) {
                addEdge(i,j);
            } else{
                k--;
            }
        }
    }
}

void UnorientedGraph::addEdge(const int &v, const int &u)
{
    adjacency.setElement(u,v,1);
    adjacency.setElement(v,u,1);
}
