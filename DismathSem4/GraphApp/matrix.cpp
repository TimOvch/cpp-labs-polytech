#include "matrix.h"
#include "algorithm"
#include <cmath>

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

Matrix Matrix::minorMatrix(int excludeRow, int excludeCol) const {
    if (rows < 2 || cols < 2) {
        throw MatrixExeption("Ошибка: Минор можно вычислить только для матрицы размерностью больше 1x1");
    }

    Matrix minor(rows - 1, cols - 1);
    int minorRow = 0;

    for (int i = 0; i < rows; ++i) {
        if (i == excludeRow) continue;
        int minorCol = 0;

        for (int j = 0; j < cols; ++j) {
            if (j == excludeCol) continue;
            minor.data[minorRow][minorCol] = data[i][j];
            minorCol++;
        }

        minorRow++;
    }

    return minor;
}

int Matrix::determinant() const {
    if (rows != cols) {
        throw MatrixExeption("Ошибка: Определитель можно вычислить только для квадратной матрицы");
    }

    if (rows == 1) {
        return data[0][0];
    }

    if (rows == 2) {
        return data[0][0] * data[1][1] - data[0][1] * data[1][0];
    }

    int det = 0;
    for (int col = 0; col < cols; ++col) {
        Matrix minor = minorMatrix(0, col);
        int sign = (col % 2 == 0) ? 1 : -1;
        det += sign * data[0][col] * minor.determinant();
    }

    return det;
}

int Matrix::algebraicComplement(int row, int col) const {
    if (rows != cols) {
        throw MatrixExeption("Ошибка: Алгебраическое дополнение можно вычислить только для квадратной матрицы");
    }

    Matrix minor = this->minorMatrix(row, col);

    int sign = ((row + col) % 2 == 0) ? 1 : -1;

    return sign * minor.determinant();
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

void Matrix::insertRow(int index, const QVector<int> &row) {
    if (row.size() != cols) {
        throw MatrixExeption("Ошибка : Длина вектора не совпадает с количеством столбцов матрицы insertRow");
    }
    if (index < 0 || index > rows) {
        throw MatrixExeption("Ошибка : Индекс строки выходит за пределы матрицы");
    }

    data.insert(index, row);
    rows++;
}

void Matrix::insertColumn(int index, const QVector<int> &column) {
    if (column.size() != rows) {
        throw MatrixExeption("Ошибка : Длина вектора не совпадает с количеством строк матрицы insertColumn");
    }
    if (index < 0 || index > cols) {
        throw MatrixExeption("Ошибка : Индекс столбца выходит за пределы матрицы");
    }

    for (int i = 0; i < rows; ++i) {
        data[i].insert(index, column[i]);
    }
    cols++;
}

Matrix Matrix::transposed() const {
    Matrix result(cols, rows);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.data[j][i] = data[i][j];
        }
    }

    return result;
}

Matrix::MatrixExeption::MatrixExeption(const std::string& error)
    : text(error)
{}

const char *Matrix::MatrixExeption::what() const noexcept
{
    return text.c_str();
}
