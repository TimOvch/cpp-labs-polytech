#ifndef FANO_H
#define FANO_H

#ifndef FANOENCODERDIALOG_H
#define FANOENCODERDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QMap>
#include <QVector>
#include <QPair>

#include <QDialog>
#include <QFileDialog>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QMap>
#include <QVector>
#include <QPair>
#include "hashtable.h"
#include "encoding.h"

class FanoEncoderDialog : public QDialog {
    Q_OBJECT

public:
    explicit FanoEncoderDialog(QWidget *parent = nullptr);
    ~FanoEncoderDialog();

private slots:
    void selectInputFile();
    void selectOutputFile();
    void selectDecodeOutputFile();
    void encode();
    void decode();
    void compareEncodedToOriginal();
    void twoStepsEnc();
    void twoStepsDec();
    void setIshod();

private:
    void compareFiles(const QString &file1Path, const QString &file2Path);

    QLabel *inputFileLabel;
    QLabel *outputFileLabel;
    QLabel *decodeOutputFileLabel;
    QPushButton *inputFileButton;
    QPushButton *outputFileButton;
    QPushButton *decodeOutputFileButton;
    QPushButton *encodeButton;
    QPushButton *decodeButton;
    QPushButton *compareButton;
    QTextEdit *codeOutput;
    QTextEdit *encodedData;
    QTextEdit *decodedData;
    QString inputFilePath;
    QString outputFilePath;
    QString decodeOutputFilePath;
};

#endif // FANOENCODERDIALOG_H
#endif // FANO_H
