#ifndef ORIENTEDGRAPH_H
#define ORIENTEDGRAPH_H

#include "abstractgraph.h"

class OrientedGraph : AbstractGraph
{
public:
    OrientedGraph(const int& vershini);
    virtual ~OrientedGraph();

    void graphGenerate();
    void acycleGraphGenerate();

    void addEdge(const int& v, const int& u);

};

#endif // ORIENTEDGRAPH_H
