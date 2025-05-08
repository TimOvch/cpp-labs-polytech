#ifndef ENCODING_H
#define ENCODING_H

#include <QString>
#include <QChar>
#include <QVector>
#include "hashtable.h"

QVector<int> compressLZW(const QString& input);
QString decompressLZW(const QVector<int>& compressed);
QString encodeFano(const QString& inputText, QStringList& formattedCodes, double& ck, double& sj);
QString decodeFano(const QString &inputText);
QString twoStepsEncoding(const QString& inputText);
QString twoStepsDecoding(const QString& inputText);

#endif // ENCODING_H
