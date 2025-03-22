#ifndef ORIENTEDGRAPH_H
#define ORIENTEDGRAPH_H

#include "abstractgraph.h"

class OrientedGraph : public AbstractGraph
{
public:
    OrientedGraph(const int& vershini, const bool& negative_weights);
    virtual ~OrientedGraph(){}

    virtual void graphGenerate() override;
    virtual void acycleGraphGenerate() override;

    virtual void addEdge(const int& v, const int& u) override;

};

#endif // ORIENTEDGRAPH_H
