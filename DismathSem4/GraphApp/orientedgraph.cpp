#include "orientedgraph.h"
#include <QRandomGenerator>


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
                    el = std::abs(dist.getRandom());
                }
                weights.setElement(i,j,el);

                int cap = negativeWeights ? dist.getRandom() : std::abs(dist.getRandom());
                while(cap == 0){
                    cap = std::abs(dist.getRandom());
                }
                capacities.setElement(i,j,cap);
                degrees[i][0]++;
                degrees[j][1]++;
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

