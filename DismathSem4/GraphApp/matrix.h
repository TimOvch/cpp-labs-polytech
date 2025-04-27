#ifndef MATRIX_H
#define MATRIX_H

#include <QVector>
#include <QDebug>

class Matrix {
public:
    Matrix();
    Matrix(int r, int c, int initValue = 0);
    Matrix(const Matrix& other);
    Matrix(const QVector<QVector<int> >& vec);

    Matrix& operator=(const Matrix& other);
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;

    Matrix boolMult(const Matrix& other) const;
    Matrix ternMult(const Matrix& other) const;
    Matrix shimbelMult(const Matrix& other, const bool& if_max) const;
    Matrix minorMatrix(int excludeRow, int excludeCol) const;
    int determinant() const;
    int algebraicComplement(int row, int col) const;



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

    void setCols(int newCols);
    void setRows(int newRows);

    void insertRow(int index, const QVector<int>& row);

    void insertColumn(int index, const QVector<int>& column);

    Matrix transposed() const;

private:
    int rows, cols;
    QVector<QVector<int>> data;

};


#endif // MATRIX_H
