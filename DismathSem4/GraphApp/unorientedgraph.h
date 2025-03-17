#ifndef UNORIENTEDGRAPH_H
#define UNORIENTEDGRAPH_H

#include "abstractgraph.h"

class UnorientedGraph : public AbstractGraph
{
public:
    UnorientedGraph(const int& vershini);
    virtual ~UnorientedGraph() override{}

    virtual void graphGenerate() override;
    virtual void acycleGraphGenerate() override;

    virtual void addEdge(const int &v, const int &u) override;
};

#endif // UNORIENTEDGRAPH_H
