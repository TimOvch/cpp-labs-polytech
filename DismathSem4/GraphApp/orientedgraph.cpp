#include "orientedgraph.h"
#include <QRandomGenerator>


OrientedGraph::OrientedGraph(const int &vershini)
    : AbstractGraph(vershini)
{
    type = "oriented";
}

void OrientedGraph::graphGenerate()
{

}

void OrientedGraph::acycleGraphGenerate()
{
    generatePowers();

    Distribution dist(2, 0.9);

    for (int i = 0; i < p ; i++) {
        for (int k = 0; k < powers[p-i-1] ; k++) {
            int j = QRandomGenerator::global()->bounded(p);
            if ( i != j && i < j && adjacency.getElem(i,j) != 1) {
                addEdge(i,j);
                weights.setElement(i,j,std::abs(dist.getRandom()));
            } else{
                k--;
            }
        }
    }
}

void OrientedGraph::addEdge(const int &v, const int &u)
{
    adjacency.setElement(v,u,1);
    q++;
}

