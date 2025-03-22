#include "abstractgraph.h"
#include <QFile>
#include <QTextStream>
#include <random>
#include <algorithm>
#include <QDebug>
#include <QQueue>
#include <QPair>
#include <QStack>
#include <limits.h>

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


AbstractGraph::AbstractGraph(const int &vershini)
    :p(vershini), adjacency(p,p), weights(p,p), powers(p,0), q(0)
{
}

Matrix AbstractGraph::shimbellMethod(const int &times, const bool &max)
{
    Matrix out(weights);
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
                if (adjacency.getElem(v, i) == 1) {
                    stack.push(qMakePair(v, i));
                }
            }
        }
    }

    return result;
}

QVector<int> AbstractGraph::dijkstra(const int& startVertex) {
    int numVertices = p;
    QVector<int> distances(numVertices, INT_MAX);
    QVector<bool> visited(numVertices, false);

    distances[startVertex] = 0;

    for (int i = 0; i < numVertices - 1; ++i) {
        int minDistance = INT_MAX;
        int minIndex = -1;
        for (int j = 0; j < numVertices; ++j) {
            if (!visited[j] && distances[j] <= minDistance) {
                minDistance = distances[j];
                minIndex = j;
            }
        }

        if (minIndex == -1) break;

        visited[minIndex] = true;

        for (int k = 0; k < numVertices; ++k) {
            if (!visited[k] && adjacency.getElem(minIndex, k) == 1 &&
                distances[minIndex] != INT_MAX &&
                distances[minIndex] + weights.getElem(minIndex, k) < distances[k]) {
                distances[k] = distances[minIndex] + weights.getElem(minIndex, k);
            }
        }
    }

    return distances;
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
    qDebug() << powers;
}

AbstractGraph::AbstractGraphExeption::AbstractGraphExeption(const std::string &error)
    : text(error)
{}

const char *AbstractGraph::AbstractGraphExeption::what() const noexcept{
    return text.c_str();
}
