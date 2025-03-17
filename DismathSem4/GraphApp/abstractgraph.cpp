#include "abstractgraph.h"
#include <QFile>
#include <QTextStream>
#include <random>
#include <algorithm>
#include <QDebug>
#include <QQueue>


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

Matrix AbstractGraph::getWeights() const
{
    return weights;
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
