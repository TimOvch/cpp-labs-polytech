#include "abstractgraph.h"
#include <QFile>
#include <QTextStream>
#include <random>
#include <algorithm>
#include <QDebug>
#include <QQueue>
#include <QPair>
#include <QStack>
#include <QHash>
#include <QSet>
#include <QString>
#include <unordered_set>
#include <limits.h>
#include <queue>
#include <vector>
#include <limits>
#include <math.h>

int AbstractGraph::getP() const
{
    return p;
}

void AbstractGraph::setP(const int& newP)
{
    p = newP;
}

int AbstractGraph::getQ() const
{
    return q;
}

void AbstractGraph::setQ(const int& newQ)
{
    q = newQ;
}

Matrix AbstractGraph::getAdjacency() const
{
    return adjacency;
}

QString AbstractGraph::getName() const
{
    return name;
}

void AbstractGraph::setName(const QString &newName)
{
    name = newName;
}

QString AbstractGraph::getType() const
{
    return type;
}

void AbstractGraph::loadAdjacency(const Matrix &mat)
{
    adjacency = mat;
    p = mat.getCols();
}

QPair<int, QVector<QVector<int>>> AbstractGraph::countPathsBFS(const int& startVertex, const int& targetVertex) {
    if (startVertex == targetVertex) {
        QVector<QVector<int>> paths;
        paths.append({startVertex});
        return qMakePair(1, paths);
    }

    QVector<int> pathCounts(p, 0);
    QVector<QVector<QVector<int>>> allPaths(p);
    QQueue<int> queue;

    queue.enqueue(startVertex);
    pathCounts[startVertex] = 1;
    allPaths[startVertex].append({startVertex});

    while (!queue.isEmpty()) {
        int currentVertex = queue.dequeue();

        for (int i = 0; i < p; ++i) {
            if (adjacency.getElem(currentVertex, i) == 1) {
                if (pathCounts[i] == 0) {
                    queue.enqueue(i);
                }

                pathCounts[i] += pathCounts[currentVertex];
                for (const QVector<int>& path : allPaths[currentVertex]) {
                    QVector<int> newPath = path;
                    newPath.append(i);
                    allPaths[i].append(newPath);
                }
            }
        }
    }

    return qMakePair(pathCounts[targetVertex], allPaths[targetVertex]);
}





// КОНСТРУКТОР

AbstractGraph::AbstractGraph(const int &vershini)
    :p(vershini), adjacency(p,p), weights(p,p),
    capacities(p,p), powers(p,0), degrees(p,QVector<int>(2,0)),
    q(0), costs(p,p), TakenCaps(p,p), Kirchhoff(p,p),
    treeAdj(p,p), isUnoriented(0), adjacencySave(p,p),
    weightsSave(p,p), unorDegrees(p,0), hamilton(0)
{

}




Matrix AbstractGraph::shimbellMethod(const int &times, const bool &max)
{
    Matrix out(weights);
    if(isUnoriented){
        return out;
    }
    for(int i =0; i < times; i++){
        out = out.shimbelMult(weights,max);
    }

    return out;
}

QString AbstractGraph::edgesDFS(const int &startVertex, const int &endVertex) {
    QString result;
    QVector<QPair<int, int>> visitedEdges;
    QStack<QPair<int, int>> stack;

    stack.push(qMakePair(startVertex, endVertex));

    while (!stack.isEmpty()) {
        QPair<int, int> currentEdge = stack.pop();
        int u = currentEdge.first;
        int v = currentEdge.second;

        bool isVisited = false;
        for (const auto& edge : visitedEdges) {
            if ((edge.first == u && edge.second == v) ||
                (edge.first == v && edge.second == u)) {
                isVisited = true;
                break;
            }
        }

        if (!isVisited) {
            visitedEdges.append(qMakePair(u, v));
            result += QString("(%1, %2) ").arg(u+1).arg(v+1);

            for (int i = 0; i < p; ++i) {
                if (adjacency.getElem(v, i) == 1 || adjacency.getElem(i, v) == 1) {
                    stack.push(qMakePair(v, i));
                }
            }
        }
    }

    return result;
}

QPair<QVector<int>, QVector<QVector<int>>> AbstractGraph::dijkstra(const int& startVertex, int& iterations,const bool& by_weights) {
    int numVertices = p;
    QVector<int> distances(numVertices, INT_MAX);
    QVector<int> parents(numVertices, -1);
    distances[startVertex] = 0;
    iterations = 0;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push(std::make_pair(0, startVertex));

    int it = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        int currentDist = pq.top().first;
        pq.pop();

        if (currentDist > distances[u]) continue;

        for (int v = 0; v < numVertices; ++v) {
            iterations++;
            if (adjacency.getElem(u, v) == 1) {
                int newDistance = by_weights ? distances[u] + weights.getElem(u, v) : distances[u] + costs.getElem(u, v);
                if (newDistance < distances[v]) {
                    distances[v] = newDistance;
                    parents[v] = u;
                    pq.push(std::make_pair(newDistance, v));
                }\
            }
        }
        it++;
    }

    QVector<QVector<int>> paths(numVertices);
    for (int i = 0; i < numVertices; ++i) {
        if (distances[i] != INT_MAX) {
            int current = i;
            while (current != -1) {
                paths[i].push_front(current);
                current = parents[current];
            }
        }
    }

    return qMakePair(distances, paths);
}

QPair<QVector<int>, QVector<QVector<int>>> AbstractGraph::dijkstraWithNeg(const int &startVertex, int& iterations) {
    int numVertices = p;

    QVector<int> distances(numVertices, INT_MAX);
    QVector<int> parents(numVertices, -1);
    distances[startVertex] = 0;

    IndexedHeap<int> pq(numVertices);
    pq.push(startVertex, 0);
    for (int v = 0; v < numVertices; ++v) {
        iterations++;

        if (adjacency.getElem(startVertex, v) == 1) {
            pq.push(startVertex, weights.getElem(startVertex, v));
        }
    }

    iterations = 0;

    while (!pq.empty()) {
        auto [currentDist, u] = pq.pop();

        for (int v = 0; v < numVertices; ++v) {
            iterations++;

            if (adjacency.getElem(u, v) == 1) {
                int newDistance = distances[u] + weights.getElem(u, v);

                if (newDistance < distances[v]) {
                    distances[v] = newDistance;
                    parents[v] = u;

                    pq.push(v, newDistance);
                    pq.decreaseKey(v, newDistance);
                }
            }
        }
    }

    QVector<QVector<int>> paths(numVertices);
    for (int i = 0; i < numVertices; ++i) {
        if (distances[i] != INT_MAX) {
            int current = i;
            while (current != -1) {
                paths[i].push_front(current);
                current = parents[current];
            }
        }
    }

    return qMakePair(distances, paths);
}

int AbstractGraph::fordFulkerson() {
    if(isUnoriented){
        return 0;
    }
    int maxFlow = 0;
    int sink = p-1;

    Matrix residualGraph = capacities;

    QVector<int> parent(p, -1);

    for(auto& source : sources){
        while (bfs(residualGraph, source, sink, parent)) {
            int pathFlow = INT_MAX;
            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                pathFlow = std::min(pathFlow, residualGraph.getElem(u, v));
            }

            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                residualGraph.setElement(u, v, residualGraph.getElem(u, v) - pathFlow);
                residualGraph.setElement(v, u, residualGraph.getElem(v, u) + pathFlow);
            }

            maxFlow += pathFlow;
        }
    }

    return maxFlow;
}

QPair<int, int> AbstractGraph::minCostFlow() {
    if(isUnoriented){
        return qMakePair(0,0);
    }
    int maxFlow = fordFulkerson();
    int targetFlow = ceil((2 * maxFlow) / 3);
    if (targetFlow == 0) {
        targetFlow = 1;
    }

    Matrix residualGraph = capacities;
    TakenCaps = Matrix(p, p);
    Matrix adjSave = adjacency;
    int totalCost = 0;
    int flowAchieved = 0;
    const int sink = p - 1;

    while (flowAchieved < targetFlow) {
        bool pathFound = false;
        int minCost = INT_MAX;
        QVector<int> bestPath;
        int bestSource = -1;

        for (const auto& source : sources) {
            int iterations = 0;
            auto dijkstraResult = dijkstra(source, iterations, 0);
            QVector<int> distances = dijkstraResult.first;
            QVector<QVector<int>> paths = dijkstraResult.second;

            if (distances[sink] != INT_MAX && distances[sink] < minCost) {
                minCost = distances[sink];
                bestPath = paths[sink];
                bestSource = source;
                pathFound = true;
            }
        }

        if (!pathFound) {
            break;
        }

        int pathFlow = INT_MAX;
        for (int i = 0; i < bestPath.size() - 1; ++i) {
            int u = bestPath[i];
            int v = bestPath[i + 1];
            pathFlow = std::min(pathFlow, residualGraph.getElem(u, v));
        }
        pathFlow = std::min(pathFlow, targetFlow - flowAchieved);

        for (int i = 0; i < bestPath.size() - 1; ++i) {
            int u = bestPath[i];
            int v = bestPath[i + 1];

            residualGraph.setElement(u, v, residualGraph.getElem(u, v) - pathFlow);
            residualGraph.setElement(v, u, residualGraph.getElem(v, u) + pathFlow);
            TakenCaps.setElement(u, v, TakenCaps.getElem(u, v) + pathFlow);
            totalCost += pathFlow * costs.getElem(u, v);

            if (residualGraph.getElem(u, v) == 0) {
                adjacency.setElement(u, v, 0);
                adjacency.setElement(v, u, 0);
            }
        }

        flowAchieved += pathFlow;
        if (pathFlow == 0) {
            break;
        }
    }

    adjacency = adjSave;
    return qMakePair(flowAchieved, totalCost);
}

int AbstractGraph::getSpanTreesNum()
{
    return Kirchhoff.algebraicComplement(p-1,p-1);
}

QVector<QPair<int, int> > AbstractGraph::maxIndependentEdgeSetTree() {
    QVector<bool> used(p, false);
    QVector<QPair<int, int>> result;

    std::function<void(int, int)> dfs = [&](int v, int parent) {
        for (int u = 0; u < p; ++u) {
            if (treeAdj.getElem(v, u) != 0 && u != parent) {
                dfs(u, v);

                if (!used[v] && !used[u]) {
                    result.push_back({v, u});
                    used[v] = used[u] = true;
                }
            }
        }
    };

    dfs(0, -1);

    qDebug() << result;

    return result;
}

QVector<QPair<int, int> > AbstractGraph::maxEdgeIndependentSetDAG() {
    if(!isUnoriented){
        QVector<QPair<int, int>> result;

        QVector<int> topologicalOrder;
        QVector<int> inDegree(p, 0);
        QQueue<int> queue;

        for (int v = 0; v < p; ++v) {
            for (int u = 0; u < p; ++u) {
                if (adjacency.getElem(u, v) == 1) {
                    inDegree[v]++;
                }
            }
            if (inDegree[v] == 0) {
                queue.enqueue(v);
            }
        }

        while (!queue.isEmpty()) {
            int u = queue.dequeue();
            topologicalOrder.push_back(u);

            for (int v = 0; v < p; ++v) {
                if (adjacency.getElem(u, v) == 1) {
                    inDegree[v]--;
                    if (inDegree[v] == 0) {
                        queue.enqueue(v);
                    }
                }
            }
        }

        QVector<bool> usedVertices(p, false);

        for (int u : topologicalOrder) {
            if (usedVertices[u]) continue;

            for (int v = 0; v < p; ++v) {
                if (adjacency.getElem(u, v) == 1 && !usedVertices[v]) {
                    result.push_back(qMakePair(u, v));
                    usedVertices[u] = true;
                    usedVertices[v] = true;
                    break;
                }
            }
        }
        qDebug() << result;

        return result;
    } else{

    }
}

void AbstractGraph::Prim()
{
    QSet<int> S;
    QSet<int> V;
    QSet<QPair<int,int>> T;
    QVector<int> alpha(p,-1);
    QVector<int> beta(p, INT_MAX);
    int u = 0;
    sum = 0;

    S.insert(u);

    for(int i = 0; i < p; i++){
        V.insert(i);
    }

    for (int v = 1; v < p; v++){
        if (adjacency.getElem(u,v)==1 || adjacency.getElem(v,u)==1){
            alpha[v] = u;
            beta[v] = adjacency.getElem(u,v)==1 ? weights.getElem(u,v) : weights.getElem(v,u);
        } else{
            alpha[v] = 0;
            beta[v] = INT_MAX;
        }
    }

    for(int i = 1; i < p; i++){
        int x = INT_MAX;
        int w = -1;
        QSet<int> VsubS = V-S;
        for (auto it = VsubS.begin(); it != VsubS.end(); ++it) {
            int v = *it;
            if(beta[v] < x){
                w = v;
                x = beta[v];
            }
        }
        if(w!=-1){
            S.insert(w);
            T.insert(qMakePair(alpha[w],w));
            treeAdj.setElement(alpha[w],w,1);
            treeAdj.setElement(w,alpha[w],1);
            int sumplus = 0;
            for(int k = 0; k < p; k++){
                if(adjacency.getElem(k,w)==1 || adjacency.getElem(w,k)==1){
                    int weig = adjacency.getElem(k,w)==1 ? weights.getElem(k,w) : weights.getElem(w,k);
                    if(beta[k] > weig){
                        alpha[k] = w;
                        beta[k] = weig;
                        sumplus = beta[k];
                    }
                }
            }
        }
    }

    for(int i = 0; i < p; i++){
        for(int j = 0; j < p; j++){
            if(treeAdj.getElem(i,j)==1){
                sum+=weights.getElem(i,j);
            }
        }
    }
}

void AbstractGraph::PruferCode() {
    Prufer.clear();
    PruferWeights.clear();
    QVector<int> degrees(p, 0);
    Matrix adjCopy = treeAdj;
    Prufer.reserve(p-1);
    PruferWeights.reserve(p);

    for (int i = 0; i < p; ++i) {
        for(int j = 0; j < p; ++j){
            degrees[i]+=treeAdj.getElem(i,j);
        }
    }

    for(int i = 0; i < p-1; i++){
        int v;
        for(int j = 0; j < p; j++){
            if(degrees[j] == 1){
                v = j;
                break;
            }
        }

        for(int j = 0; j < p; j++){
            if(adjCopy.getElem(v,j) == 1){
                Prufer.append(j);
                PruferWeights.append(weights.getElem(v,j) != 0 ? weights.getElem(v,j) : weights.getElem(j,v));
                adjCopy.setElement(v,j,0);
                adjCopy.setElement(j,v,0);
                degrees[j]--;
                degrees[v]--;
                break;
            }
        }
    }
}

void AbstractGraph::hamiltonianCycleUtil(QVector<int> &path, int pos, QVector<QPair<QVector<int>, int> > &cycles) {
    if (pos == p) {
        if (adjacency.getElem(path[pos - 1], path[0]) == 1) {
            QVector<int> cycle;
            int totalWeight = 0;

            for (int i = 0; i < p; i++) {
                cycle.append(path[i]);

                if (i > 0) {
                    totalWeight += weights.getElem(path[i - 1], path[i]);
                }
            }

            totalWeight += weights.getElem(path[p - 1], path[0]);

            cycle.append(path[0]);

            cycles.append(qMakePair(cycle, totalWeight));
        }

        return;
    }

    for (int v = 1; v < p; v++) {
        if (isSafe(v, path, pos)) {
            path[pos] = v;

            hamiltonianCycleUtil(path, pos + 1, cycles);

            path[pos] = -1;
        }
    }
}

bool AbstractGraph::isSafe(int v, QVector<int> &path, int pos) {
    if (adjacency.getElem(path[pos - 1], v) == 0) {
        return false;
    }

    for (int i = 0; i < pos; i++) {
        if (path[i] == v) {
            return false;
        }
    }

    return true;
}

bool AbstractGraph::checkEdge(const int &startVertex, const int &endVertex){
    return adjacency.getElem(startVertex,endVertex)!=0;
}

Matrix AbstractGraph::getWeights() const
{
    return weights;
}

bool AbstractGraph::getConnected() const
{
    return connected;
}

bool AbstractGraph::getAcycle() const
{
    return acycle;
}

bool AbstractGraph::getNegativeWeights() const
{
    return negativeWeights;
}

Matrix AbstractGraph::getCapacities() const
{
    return capacities;
}

Matrix AbstractGraph::getCosts() const
{
    return costs;
}

Matrix AbstractGraph::getTakenCaps() const
{
    return TakenCaps;
}

QPair<QVector<int>, QVector<int> > AbstractGraph::getPrufer()
{
    return qMakePair(Prufer,PruferWeights);
}


Matrix AbstractGraph::getKirchhoff() const
{
    return Kirchhoff;
}

int AbstractGraph::getSum() const
{
    return sum;
}

QPair<QString, QString> AbstractGraph::getPruferStr()
{
    QString pruf = "",weight = "";

    for(int i = 0; i < Prufer.size(); i++){
        pruf.append(QString::number(Prufer[i])).append(" ");
    }

    for(int i = 0; i < PruferWeights.size(); i++){
        weight.append(QString::number(PruferWeights[i])).append(" ");
    }

    return qMakePair(pruf,weight);
}

bool AbstractGraph::getIsUnoriented() const
{
    return isUnoriented;
}

bool AbstractGraph::bfs(const Matrix &residualGraph, int source, int sink, QVector<int> &parent) {
    QVector<bool> visited(p, false);
    QQueue<int> queue;
    queue.enqueue(source);
    visited[source] = true;
    parent[source] = -1;

    while (!queue.isEmpty()) {
        int u = queue.dequeue();

        for (int v = 0; v < p; ++v) {
            if (!visited[v] && residualGraph.getElem(u, v) > 0) {
                queue.enqueue(v);
                parent[v] = u;
                visited[v] = true;

                if (v == sink) {
                    return true;
                }
            }
        }
    }

    return false;
}

void AbstractGraph::generatePowers()
{
    int bound = p;
    Distribution dist(2, 0.9);
    for(int i = 0; i < p-1; ++i){
        int random = static_cast<int>(dist.getRandom());
        if (random <= bound - 1 && random > 0) {
            powers[i] = random;
            bound--;
        } else{
            i--;
        }
    }

    std::sort(powers.begin(),powers.end());
}

void AbstractGraph::countKirchhoff()
{
    Matrix diagDeg(p,p);

    for(int i = 0; i < p; i++){
        diagDeg.setElement(i,i,degrees[i][0]+degrees[i][1]);
    }

    if(isUnoriented){
        Kirchhoff = diagDeg-adjacency;
    }else{
        Kirchhoff = diagDeg-adjacency-adjacency.transposed();
    }
}

void AbstractGraph::makeUnoriented(){
    isUnoriented = 1;
    type = "unoriented";

    adjacencySave = adjacency;
    weightsSave = weights;

    adjacency = adjacency+adjacency.transposed();
    weights = weights+weights.transposed();
}

QPair<bool, bool> AbstractGraph::isEuler(){
    bool euler = true;
    int nechet_sum = 0;

    for(int i = 0; i < p; i++){
        int sum = degrees[i][0] + degrees[i][1];
        if(sum%2!=0){
            euler = false;
            nechet_sum +=1;
        }
    }

    if(euler){
        return qMakePair(1,0);
    } else{
        if(nechet_sum == 2){
            return qMakePair(0,1);
        } else{
            return qMakePair(0,0);
        }
    }
}

QPair<QVector<QPair<int,int>>,QVector<QPair<int,int>>> AbstractGraph::makeEuler(bool& possible)
{
    QVector<QPair<int,int>> added,deleted;
    possible = true;
    if(p == 2){
        possible = false;
        return qMakePair(added,deleted);
    }

    Distribution dist(5, 1.1);

    int counter = 0;
    QVector<int> tmp(2,-1);
    for(int i = 0; i < p; i++){
        if((unorDegrees[i]%2)==1){
            tmp[counter] = i;
            counter++;
        }

        if(counter == 2){
            counter = 0;
            int u = tmp[0],v = tmp[1];

            if(adjacency.getElem(u,v) == 0){
                adjacency.setElement(u,v,1);
                adjacency.setElement(v,u,1);
                int weight = abs(dist.getRandom());
                weights.setElement(u,v,weight);
                weights.setElement(v,u,weight);
                unorDegrees[u]++;
                unorDegrees[v]++;
                degrees[u][0]++;
                degrees[v][1]++;
                q++;
                added.append({u,v});
            } else{
                if((unorDegrees[u] != 1) && (unorDegrees[v] != 1)){
                    adjacency.setElement(u,v,0);
                    adjacency.setElement(v,u,0);
                    weights.setElement(u,v,0);
                    weights.setElement(v,u,0);
                    unorDegrees[u]--;
                    unorDegrees[v]--;
                    degrees[u][0]--;
                    degrees[v][1]--;
                    q--;
                    deleted.append({u,v});
                } else{
                    if(unorDegrees[v]==1){
                        int tmp = v;
                        v = u;
                        u = tmp;
                    }

                    for(int j = 0; j < p; j++){
                        if((adjacency.getElem(v,j) == 1) && (unorDegrees[j]%2 == 0)){
                            adjacency.setElement(u,j,1);
                            adjacency.setElement(j,u,1);
                            int weight = abs(dist.getRandom());
                            weights.setElement(u,j,weight);
                            weights.setElement(j,u,weight);
                            unorDegrees[u]++;
                            unorDegrees[j]++;
                            degrees[u][0]++;
                            degrees[j][1]++;
                            q++;
                            added.append({u,j});

                            adjacency.setElement(j,v,0);
                            adjacency.setElement(v,j,0);
                            weights.setElement(j,v,0);
                            weights.setElement(v,j,0);
                            unorDegrees[j]--;
                            unorDegrees[v]--;
                            if(v < j){
                                degrees[v][0]--;
                                degrees[j][1]--;
                            } else{
                                degrees[v][1]--;
                                degrees[j][0]--;
                            }
                            q--;
                            deleted.append({j,v});
                            break;
                        }
                    }
                }
            }
        }
    }

    PruferCode();
    return qMakePair(added,deleted);
}

QVector<int> AbstractGraph::eulerCycle()
{
    QStack<int> stack;
    QVector<int> eulerianCycle;
    stack.push(0);

    Matrix adjCopy = adjacency;

    while (!stack.isEmpty()) {
        int current = stack.top();
        bool hasNeighbour = false;

        for (int i = 0; i < p; ++i) {
            if (adjCopy.getElem(current,i) == 1) {
                stack.push(i);
                adjCopy.setElement(current,i,0);
                adjCopy.setElement(i,current,0);
                hasNeighbour = true;
                break;
            }
        }

        if (!hasNeighbour) {
            eulerianCycle.append(current);
            stack.pop();
        }
    }

    return eulerianCycle;
}

QString AbstractGraph::eulerCycleStr()
{
    QVector<int> cycle = eulerCycle();
    QString result = "";

    for(int i = 0; i < cycle.size(); i++){
        result.append(QString::number(cycle[i]+1));
        result.append(' ');
    }

    return result;
}

QVector<QPair<QVector<int>, int>> AbstractGraph::findHamiltonianCycles() {
    QVector<int> path(p, -1);
    QVector<QPair<QVector<int>, int>> cycles;
    path[0] = 0;

    hamiltonianCycleUtil(path, 1, cycles);

    return cycles;
}

QVector<QPair<int, int> > AbstractGraph::makeHamilton()
{
    QVector<QPair<int,int>> added;
    if(hamilton){
        return added;
    }

    Distribution dist(5,1.1);

    for(int i = 0; i < p-1; i++){
        if(adjacency.getElem(i,i+1)!=1){
            int u = i, v = i+1;
            adjacency.setElement(u,v,1);
            adjacency.setElement(v,u,1);
            int weight = abs(dist.getRandom());
            weights.setElement(u,v,weight);
            weights.setElement(v,u,weight);
            unorDegrees[u]++;
            unorDegrees[v]++;
            degrees[u][0]++;
            degrees[v][1]++;
            q++;
            added.append({u,v});
        }
    }

    if(adjacency.getElem(p-1,0)!=1){
        int u = p-1, v = 0;
        adjacency.setElement(u,v,1);
        adjacency.setElement(v,u,1);
        int weight = abs(dist.getRandom());
        weights.setElement(u,v,weight);
        weights.setElement(v,u,weight);
        unorDegrees[u]++;
        unorDegrees[v]++;
        degrees[u][0]++;
        degrees[v][1]++;
        q++;
        added.append({u,v});
    }

    return added;
}

QString AbstractGraph::hamiltonCyclesStr()
{
    QString res = "";

    auto hamCycles = findHamiltonianCycles();

    if(hamCycles.isEmpty()){
        return "Нет";
    } else{
        return "Да";
    }

    return res;
}

AbstractGraph::AbstractGraphExeption::AbstractGraphExeption(const std::string &error)
    : text(error)
{}

const char *AbstractGraph::AbstractGraphExeption::what() const noexcept{
    return text.c_str();
}

template<typename T>
IndexedHeap<T>::IndexedHeap(int capacity) : indices(capacity, -1), data(capacity) {}

template<typename T>
void IndexedHeap<T>::push(int key, const T &value) {
    if (indices[key] != -1) return;
    data.push_back({value, key});
    indices[key] = data.size() - 1;
    heapifyUp(data.size() - 1);
}

template<typename T>
std::pair<T, int> IndexedHeap<T>::pop() {
    std::pair<T, int> root = data.front();
    std::swap(data[0], data.back());
    indices[data[0].second] = 0;
    data.pop_back();
    indices[root.second] = -1;
    heapifyDown(0);
    return root;
}

template<typename T>
void IndexedHeap<T>::decreaseKey(int key, const T &newValue) {
    int index = indices[key];
    if (index == -1 || data[index].first <= newValue) return;
    data[index].first = newValue;
    heapifyUp(index);
}

template<typename T>
bool IndexedHeap<T>::empty() const {
    return data.empty();
}

template<typename T>
void IndexedHeap<T>::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (data[parent].first <= data[index].first) break;
        swapNodes(parent, index);
        index = parent;
    }
}

template<typename T>
void IndexedHeap<T>::heapifyDown(int index) {
    int size = data.size();
    while (true) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < size && data[left].first < data[smallest].first) smallest = left;
        if (right < size && data[right].first < data[smallest].first) smallest = right;

        if (smallest == index) break;
        swapNodes(index, smallest);
        index = smallest;
    }
}

template<typename T>
void IndexedHeap<T>::swapNodes(int i, int j) {
    std::swap(data[i], data[j]);
    indices[data[i].second] = i;
    indices[data[j].second] = j;
}
