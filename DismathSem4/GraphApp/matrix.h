#ifndef MATRIX_H
#define MATRIX_H

#include <QVector>
#include <QDebug>

class Matrix {
public:
    Matrix();

    Matrix(int r, int c, int initValue = 0);


    Matrix(const Matrix& other);

    Matrix& operator=(const Matrix& other);
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;

    Matrix boolMult(const Matrix& other) const;
    Matrix ternMult(const Matrix& other) const;
    Matrix shimbelMult(const Matrix& other, const bool& max) const;

    friend QDebug operator<<(QDebug dbg, const Matrix& m);

    class MatrixExeption : public std::exception {
    private:
        std::string text;

    public:

        MatrixExeption(const std::string& error);

        const char* what() const noexcept override;

        virtual ~MatrixExeption() override {}
    };

    int getRows() const;
    int getCols() const;
    int getElem(const int &row, const int &col) const;

    QVector<QVector<int> > getData() const;

    void setElement(const int &row, const int &col, const int& value);
    void setData(const QVector<QVector<int>>& mat);

private:
    int rows, cols;
    QVector<QVector<int>> data;

};


#endif // MATRIX_H
