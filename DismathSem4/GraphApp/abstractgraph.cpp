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
#include <queue>
#include <vector>

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

QPair<QVector<int>, QVector<QVector<int>>> AbstractGraph::dijkstra(const int& startVertex, int& iterations) {
    int numVertices = p;
    QVector<int> distances(numVertices, INT_MAX);
    QVector<int> parents(numVertices, -1);
    distances[startVertex] = 0;
    iterations = 0;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push(std::make_pair(0, startVertex));

    while (!pq.empty()) {
        int u = pq.top().second;
        int currentDist = pq.top().first;
        pq.pop();

        if (currentDist > distances[u]) continue;

        for (int v = 0; v < numVertices; ++v) {
            iterations++;
            if (adjacency.getElem(u, v) == 1) {
                int newDistance = distances[u] + weights.getElem(u, v);

                if (newDistance < distances[v]) {
                    distances[v] = newDistance;
                    parents[v] = u;
                    pq.push(std::make_pair(newDistance, v));
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
