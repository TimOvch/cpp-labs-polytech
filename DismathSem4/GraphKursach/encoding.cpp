#include "encoding.h"
#include "supporting.h"

const QString symbols = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя0123456789!?.,@#$%^&*(){}[] ";

QVector<int> compressLZW(const QString& input) {
    HashTable<QString, int> dictionary(hashQString);
    int dictSize = symbols.size();

    for (int i = 0; i < symbols.size(); ++i) {
        dictionary.insert(symbols[i], i);
    }

    QString w;
    QVector<int> result;

    for (const QChar& c : input) {
        QString wc = w + c;

        if (dictionary.contains(wc)) {
            w = wc;
        } else {
            result.append(dictionary[w]);
            dictionary.insert(wc, dictSize++);
            w = c;
        }
    }

    if (!w.isEmpty()) {
        result.append(dictionary[w]);
    }

    return result;
}

QString decompressLZW(const QVector<int>& compressed) {
    HashTable<int, QString> dictionary(hashInt);
    int dictSize = symbols.size();

    for (int i = 0; i < symbols.size(); ++i) {
        dictionary.insert(i, symbols[i]);
    }

    if (compressed.isEmpty()) {
        return "";
    }

    QString w = dictionary[compressed.first()];
    QString result = w;

    for (int i = 1; i < compressed.size(); ++i) {
        int k = compressed.at(i);
        QString entry;

        if (dictionary.contains(k)) {
            entry = dictionary[k];
        } else if (k == dictSize) {
            entry = w + w[0];
        } else {
            qDebug() << "Ошибка в сжатых данных";
            return "";
        }

        result += entry;
        dictionary.insert(dictSize++, w + entry[0]);
        w = entry;
    }

    return result;
}

void fanoRecursive(char branch, QString fullBranch, int startPos, int endPos,
                HashTable<QChar, QString> &codes,const QVector<QPair<QChar, int>>& sortedFrequency) {
    if (startPos >= endPos) {
        codes[sortedFrequency[startPos].first] = fullBranch+branch;
        return;
    }

    int split = findPartitionIndex(sortedFrequency,startPos,endPos);

    fanoRecursive('1', fullBranch + branch,startPos, split, codes, sortedFrequency);
    fanoRecursive('0', fullBranch + branch,split+1, endPos, codes, sortedFrequency);
}

QString encodeFano(const QString& inputText, QStringList& formattedCodes, double& ck, double& sj){
    QString outputText;
    HashTable<QChar, QString> codes(hashQChar);

    HashTable<QChar, int> frequency(hashQChar);
    int sumFrec = 0;
    for (const QChar &ch : inputText) {
        frequency[ch]++;
        sumFrec++;
    }

    QVector<QPair<QChar, int>> sortedFrequency;
    for (auto it = frequency.begin(); it != frequency.end(); ++it) {
        sortedFrequency.append(qMakePair(it.key(), it.value()));
    }

    std::sort(sortedFrequency.begin(), sortedFrequency.end(), [](const QPair<QChar, int> &a, const QPair<QChar, int> &b) {
        return a.second < b.second;
    });

    int split = findPartitionIndex(sortedFrequency,0, sortedFrequency.length()-1);

    fanoRecursive('1', "",  0 , split, codes, sortedFrequency);
    fanoRecursive('0', "", split+1, sortedFrequency.length()-1, codes, sortedFrequency);

    for (auto it = codes.begin(); it != codes.end(); ++it) {
        outputText.append(QString("\"%1\": %2\n").arg(it.key()).arg(it.value()));
    }
    outputText.append("\n");

    for(const QChar &ch : inputText){
        outputText.append(codes[ch]);
    }

    sj = ((double)(inputText.length()*sizeof(QChar)*8))/((double)outputText.length());

    for (auto it = sortedFrequency.cbegin(); it != sortedFrequency.cend(); ++it) {
        ck+=((double)codes[it->first].length())*((double)it->second/sumFrec);
    }
    formattedCodes.append(QString("Коэффициент сжатия : %1\nЦена кодирования : %2\n").arg(sj).arg(ck));

    for (const auto &pair : sortedFrequency) {
        formattedCodes.append(QString("\"%1\"\t:\t%2 (частота: %3)").arg(pair.first).arg(codes[pair.first]).arg(pair.second));
    }

    return outputText;
}

QString decodeFano(const QString &inputText) {
    HashTable<QString, QChar> codes(hashQString);
    QString outputText;

    QStringList lines = inputText.split("\n");
    int lineIndex = 0;

    while (lineIndex < lines.size() && !lines[lineIndex].isEmpty()) {
        QStringList parts = lines[lineIndex].split(": ");
        if (parts.size() == 2) {
            codes[parts[1]] = parts[0].remove('"').at(0);
            qDebug() << parts[1] << parts[0];
        }
        lineIndex++;
    }

    QString encodedData;
    for (int i = lineIndex; i < lines.size(); ++i) {
        if (!lines[i].trimmed().isEmpty()) {
            encodedData += lines[i].trimmed();
        }
    }

    QString currentCode;

    for (const QChar &ch : encodedData) {
        currentCode.append(ch);

        if (codes.contains(currentCode)) {
            outputText.append(codes[currentCode]);
            currentCode.clear();
        }
    }

    if (!currentCode.isEmpty()) {
        qDebug() << "Не удалось декодировать код:" << currentCode;
    }

    return outputText;
}

QString twoStepsEncoding(const QString& inputText){
    QVector<int> lzw = compressLZW(inputText);

    QString lzwStr = vectorToString(lzw);
    QStringList zaglushka;
    double one, two;

    QString fano = encodeFano(lzwStr,zaglushka, one, two);

    return fano;
}

QString twoStepsDecoding(const QString& inputText){
    QString fanoDecoded = decodeFano(inputText);
    QVector<int> lzwVec = stringToVector(fanoDecoded);
    QString lzwDecoded = decompressLZW(lzwVec);
    return lzwDecoded;
}
