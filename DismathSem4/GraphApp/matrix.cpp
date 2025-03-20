#include "matrix.h"
#include "algorithm"

Matrix::Matrix()
    : rows(0), cols(0)
{}

Matrix::Matrix(int r, int c, int initValue)
    : rows(r), cols(c), data(QVector<QVector<int>>(r, QVector<int>(c, initValue)))
{}

Matrix::Matrix(const Matrix &other)
    : rows(other.rows), cols(other.cols), data(other.data)
{}

Matrix::Matrix(const QVector<QVector<int> > &vec)
{
    data = vec;
    rows = vec.size();
    cols = vec[0].size();
}

Matrix &Matrix::operator=(const Matrix &other) {
    if (this != &other) {
        rows = other.rows;
        cols = other.cols;
        data = other.data;
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix &other) const {
    if (rows != other.rows || cols != other.cols) {
        throw MatrixExeption("Ошибка : Размерность матриц при сложении не совпадаeт");
    }
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix &other) const {
    if (rows != other.rows || cols != other.cols) {
        throw MatrixExeption("Размерность матриц при разности не совпадаeт");
    }
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.data[i][j] = data[i][j] - other.data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix &other) const {
    if (cols != other.rows) {
        throw MatrixExeption("Ошибка : Матрицы данной размерности не могут быть умножены");
    }
    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < other.cols; ++j) {
            for (int k = 0; k < cols; ++k) {
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}

Matrix Matrix::boolMult(const Matrix &other) const
{
    if (cols != other.rows) {
        throw MatrixExeption("Ошибка : Матрицы данной размерности не могут быть умножены булево");
    }
    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < other.cols; ++j) {
            for (int k = 0; k < cols; ++k) {
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
            if (result.data[i][j] > 1) {
                result.data[i][j] = 1;
            }
        }
    }
    return result;
}

Matrix Matrix::ternMult(const Matrix &other) const
{
    if (cols != other.rows) {
        throw MatrixExeption("Ошибка : Матрицы данной размерности не могут быть умножены тернарно");
    }
    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < other.cols; ++j) {
            for (int k = 0; k < cols; ++k) {
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
            if (result.data[i][j] > 1) {
                result.data[i][j] = 1;
            } else if (result.data[i][j] < -1){
                result.data[i][j] = -1;
            }
        }
    }
    return result;
}

Matrix Matrix::shimbelMult(const Matrix &other, const bool& if_max) const
{
    if (cols != other.rows) {
        throw MatrixExeption("Ошибка : Матрицы данной размерности не могут быть умножены методом Шимбелла");
    }
    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < other.cols; ++j) {
            QVector<int> temp;
            for (int k = 0; k < cols; ++k) {
                int sum = data[i][k] + other.data[k][j];
                if((data[i][k] == 0) || (other.data[k][j] == 0)){
                    sum = 0;
                }
                temp.push_back(sum);
            }
            if(if_max){
                result.data[i][j] = *std::max_element(temp.begin(),temp.end());
            } else {
                int min=temp[0];
                for(auto& num : temp){
                    if(num!=0){
                        if((min == 0) || (num < min)){
                            min = num;
                        }
                    }
                }
                result.data[i][j] = min;
            }
        }
    }
    return result;
}

int Matrix::getRows() const
{
    return rows;
}

int Matrix::getCols() const
{
    return cols;
}

QDebug operator<<(QDebug dbg, const Matrix& m) {
    for (int i = 0; i < m.rows; ++i) {
        for (int j = 0; j < m.cols; ++j) {
            dbg << m.data[i][j] << " ";
        }
        dbg << "\n";
    }
    return dbg;
}

int Matrix::getElem(const int &row, const int &col) const
{
    return data[row][col];
}

QVector<QVector<int> > Matrix::getData() const
{
    return data;
}

void Matrix::setElement(const int &row, const int &col, const int &value)
{
    if((row <= rows)&&(row>=0)&&(col<=cols)&&(col>=0)){
        data[row][col] = value;
    } else {
        throw MatrixExeption("Ошибка : Номер строки или колонки выходит за размерность матрицы");
    }
}

void Matrix::setData(const QVector<QVector<int> > &vec)
{
    if ((vec.length() == rows) && (vec[0].length() == cols)){
        data = vec;
    } else {
        throw MatrixExeption("Ошибка : Размерность вектора не совпадает с размерностью матрицы");
    }
}

void Matrix::setCols(int newCols)
{
    cols = newCols;
}

void Matrix::setRows(int newRows)
{
    rows = newRows;
}

Matrix::MatrixExeption::MatrixExeption(const std::string& error)
    : text(error)
{}

const char *Matrix::MatrixExeption::what() const noexcept
{
    return text.c_str();
}
