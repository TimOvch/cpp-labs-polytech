#include "supporting.h"

int findPartitionIndex(const QVector<QPair<QChar, int>> sortedVector, int start, int end) {
    if (sortedVector.isEmpty() || start < 0 || end >= sortedVector.size() || start >= end) {
        throw std::invalid_argument("Параметры должны быть корректными и вектор не должен быть пустым.");
    }

    int totalSum = 0;
    for (int i = start; i <= end; ++i) {
        totalSum += sortedVector[i].second;
    }

    int leftSum = 0;
    int minDiff = std::numeric_limits<int>::max();
    int partitionIndex = -1;

    for (int i = start; i < end; ++i) {
        leftSum += sortedVector[i].second;
        int rightSum = totalSum - leftSum;

        int diff = std::abs(leftSum - rightSum);

        if (diff < minDiff) {
            minDiff = diff;
            partitionIndex = i;
        }
    }

    return partitionIndex;
}

QString vectorToString(const QVector<int>& vec) {
    QStringList stringList;

    for (int num : vec) {
        stringList << QString::number(num);
    }

    return stringList.join(' ');
}

QVector<int> stringToVector(const QString& str) {
    QVector<int> vec;
    QStringList stringList = str.split(' ', Qt::SkipEmptyParts);

    for (const QString& s : stringList) {
        bool ok;
        int num = s.toInt(&ok);
        if (ok) {
            vec.append(num);
        } else {
            qDebug() << "Ошибка преобразования строки в число:" << s;
        }
    }

    return vec;
}

