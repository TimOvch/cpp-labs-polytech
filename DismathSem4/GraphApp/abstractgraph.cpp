#include "abstractgraph.h"
#include <QFile>
#include <QTextStream>
#include <random>

AbstractGraph::AbstractGraph(const int &vershini)
    : adjacency(p,p)
{
    p = vershini;
}

void AbstractGraph::saveToFile(const QString &fileName) const
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning("Не удалось открыть файл для записи");
        return;
    }

    QTextStream out(&file);
    for (const QVector<int>& row : adjacency.getData()) {
        for (int val : row) {
            out << val << " ";
        }
        out << "\n";
    }

    file.close();
}

void AbstractGraph::loadFromFile(const QString &fileName)
{
    QVector<QVector<int>> matrix;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Не удалось открыть файл для чтения");
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList strings = line.split(" ", Qt::SkipEmptyParts);
        QVector<int> row;
        for (const QString& str : strings) {
            row.append(str.toInt());
        }
        matrix.append(row);
    }

    adjacency.setData(matrix);

    file.close();
}

AbstractGraph::AbstractGraphExeption::AbstractGraphExeption(const std::string &error)
    : text(error)
{}

const char *AbstractGraph::AbstractGraphExeption::what() const noexcept{
    return text.c_str();
}
