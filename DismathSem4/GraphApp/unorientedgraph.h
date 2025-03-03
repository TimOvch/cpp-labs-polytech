#ifndef UNORIENTEDGRAPH_H
#define UNORIENTEDGRAPH_H

#include "abstractgraph.h"

class UnorientedGraph : public AbstractGraph
{
public:
    UnorientedGraph(const int& vershini);
    virtual ~UnorientedGraph() override{}

    void graphGenerate();
    void acycleGraphGenerate();

    void addEdge(const int &v, const int &u);
};

#endif // UNORIENTEDGRAPH_H
