#ifndef SUPPORTING_H
#define SUPPORTING_H

#include <algorithm>
#include <QVector>
#include <QDebug>
#include <stdexcept>
#include <cmath>
#include <QString>
#include <QStringList>

int findPartitionIndex(const QVector<QPair<QChar, int>> sortedVector, int start, int end);
QString vectorToString(const QVector<int>& vec);
QVector<int> stringToVector(const QString& str);


#endif // SUPPORTING_H
