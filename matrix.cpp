#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <iostream>
#include <random>
#include "matrix.h"
#include <complex>
#include <vector>
using namespace std;



template <class T>
Matrix<T>::Matrix(int rows, int columns) {
    if (rows > 0)
        this->rows = rows;
    else throw "Invalid value!";
    if (columns > 0)
        this->columns = columns;
    else throw "Invalid value!";

    vector<vector<T>> new_matrix(rows, vector<T>(columns));

    matrix = new_matrix;
}//
template <class T>
int Matrix<T>::GetRows() const {
    return rows;
}//
template <class T>
int Matrix<T>::GetCols() const {
    return columns;
}//

template <class T>
T Matrix<T>::tr()
{
    T result = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (i == j)
            {
                result += matrix.at(i).at(j);
            }
        }
    }

    return result;
}//
template <class T>
T Matrix<T>::operator () (int i, int j) {
    if ((i >= 0) && (i < rows) && (j >= 0) && (j < columns)) {
        auto it = matrix.cbegin();
        it += i;

        auto jt = (*it).cbegin();
        jt += j;
        return  (*jt);
    }
    else throw "Incorrect index values!";
}//


template <class T>
Matrix<T>& Matrix<T>::operator () (int m, int n, const T& value)
{
    if ((m <= this->rows) && (n <= this->columns))
    {
        auto it = matrix.begin();
        it += m;
        auto jt = (*it).begin();
        jt += n;
        (*jt) = value;
        return *this; }
    else throw "Incorrect index values!";

}

template <class T>
Matrix<T> Matrix<T>::operator + (const Matrix<T>& rhs) {
    if ((rows == rhs.rows) && (columns == rhs.columns)) {
        Matrix<T> result = * this;

        auto iter = rhs.cbegin();
        for (auto it = result.begin(); it != result.end(); it++)
        {
            auto jter = iter->cbegin();
            for (auto jt = it->begin(); jt != it->end(); jt++)
            {
                (*jt) += (*jter);
                jter++;
            }
            iter++;
        }
        return result;

    }
    throw "The dimensions of the matrices do not match! Addition of matrices with different dimensions is unacceptable!";
}//

template <class T>
Matrix<T> Matrix<T>::operator - (const Matrix<T>& rhs) {
    if ((rows == rhs.rows) && (columns == rhs.columns)) {
        Matrix<T> result = *this;

        auto iter = rhs.cbegin();
        for (auto it = result.begin(); it != result.end(); it++)
        {
            auto jter = iter->cbegin();
            for (auto jt = it->begin(); jt != it->end(); jt++)
            {
                (*jt) -= (*jter);
                jter++;
            }
            iter++;
        }
        return result;
    }
    throw "The dimensions of the matrices do not match! Subtraction of matrices with different dimensions is unacceptable!";
}//
template <class T>
Matrix<T> Matrix<T>::operator * (const Matrix<T>& rhs) {
    if (columns == rhs.rows) {
        /*
        Matrix<T> result(rows, rhs.columns);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < rhs.columns; j++)
                result.matrix[i][j] = 0;
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < rhs.columns; j++)
                for (int k = 0; k < columns; k++)
                    result.matrix[i][j] += matrix[i][k] * rhs.matrix[k][j];
        return result;*/
        Matrix<T> result(rows, rhs.columns);


        for (int i = 0; i < result.rows; ++i)
        {
            for (int j = 0; j < result.columns; ++j)
            {

                for (int k = 0; k < columns; ++k)
                {
                    result.matrix.at(i).at(j) += matrix.at(i).at(k) * rhs.matrix.at(k).at(j);
                }

            }
        }

        return result;
    }
    throw "Matrices cannot be multiplied! Invalid dimension!";
}//

template <class T>
Matrix<T> Matrix<T>::operator * (const T& h) {
    Matrix<T> result = *this;

    for (auto it = result.begin(); it != result.cend(); it++)
        for (auto jt = it->begin(); jt != it->cend(); jt++)
            (*jt) = (*jt) * h;


    return result;
}//

template <class T>
Matrix<T> Matrix<T>::operator / (const T& h) { 
    Matrix<T> result = *this;
    if (h == T(0))
    {
        std::cout << "invalid syntax, division by zero is not possible";
    }
    else
    {
        
        for (auto it = result.begin(); it != result.cend(); it++)
            for (auto jt = it->begin(); jt != it->cend(); jt++)
                (*jt) = (*jt) / h;
    }
    return result;
}//
template <class T>
void Matrix<T>::EnterMatrix() {
    matrix.clear();

    std::cout << "Enter the dimension of the matrix:" << endl;
    std::cout << "Number of rows: ";
    int newRows;
    cin >> newRows;
    std::cout << "Number of columns: ";
    int newColumns;
    cin >> newColumns;

    Matrix<T> newMatrix(newRows, newColumns);
    
    for (int i = 0; i < newRows; i++)
        for (int j = 0; j < newColumns; j++) {
            std::cout << "Cell (" << i << ", " << j << ") = ";
            std::cin >> newMatrix.matrix[i][j];
        }
    rows = newRows;
    columns = newColumns;
    vector<vector<T>> matrix(rows, vector<T>(columns));
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            matrix[i][j] = newMatrix.matrix[i][j];
}


template <class T>
void Matrix<T>::CreateMatrixForCheck() {
    vector<T> a(3);
    vector<T> b(3);
    vector<T> c(3);
    std::cout << "Enter a vector a" << endl;
    for (int i = 0; i < 3; i++)
    {
        std::cout << "a(" << i << ") = ";
        cin >> a[i];
        //    a[i] = Check_Double();
    }
    std::cout << "Enter a vector b" << endl;
    for (int i = 0; i < 3; i++)
    {
        std::cout << "b(" << i << ") = ";
        cin >> b[i];
    }
    std::cout << "Enter a vector c" << endl;
    for (int i = 0; i < 3; i++)
    {
        std::cout << "c(" << i << ") = ";
        cin >> c[i];
    }
    Matrix newMatrix(3, 3);
    for (int i = 0; i < 3; i++)
    {
        newMatrix.matrix[0][i] = a[i];
    }
    for (int i = 0; i < 3; i++)
    {
        newMatrix.matrix[1][i] = b[i];
    }
    for (int i = 0; i < 3; i++)
    {
        newMatrix.matrix[2][i] = c[i];
    }
    rows = 3;
    columns = 3;
    vector<vector<T>> matrix(rows, vector<T>(columns));
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            matrix[i][j] = newMatrix.matrix[i][j];
}
template <class T>
void Matrix<T>::CheckTheDeterminant() {
    T d = 0;
    d += matrix[0][0] * matrix[1][1] * matrix[2][2];
    d += matrix[0][1] * matrix[1][2] * matrix[2][0];
    d += matrix[1][0] * matrix[2][1] * matrix[0][2];
    d -= matrix[2][0] * matrix[1][1] * matrix[0][2];
    d -= matrix[2][1] * matrix[1][2] * matrix[0][0];
    d -= matrix[1][0] * matrix[0][1] * matrix[2][2];

    T a = 0;
    if (d == a)
    {
        std::cout << "the determinant of the matrix = 0, the vectors are coplanar" << endl;
    }
    else
    {
        std::cout << "the vectors are non-planar, since the determinant of the matrix is " << d << endl;
    }
}


template <class T>
void Matrix<T>::Random()
{
    srand(time(0));
    for (auto it = matrix.begin(); it != matrix.end(); it++) {
        for (auto jt = it->begin(); jt != it->end(); jt++)
        {
            (*jt) = T((1 + rand() % 100) / 10.0);
        }
    }
}//
template <>
void Matrix<complex<double>>::Random()
{
    srand(time(0));
    for (auto it = matrix.begin(); it != matrix.end(); it++)
        for (auto jt = it->begin(); jt != it->end(); jt++)
        {
            complex<float> value(((1 + rand() % 100) / 10.0), ((1 + rand() % 100) / 10.0));
            (*jt) = value;
        }
}//
template <>
void Matrix<complex<float>>::Random()
{

    srand(time(0));
    for (auto it = matrix.begin(); it != matrix.end(); it++)
        for (auto jt = it->begin(); jt != it->end(); jt++)
        {
            complex<float> value(((1 + rand() % 100) / 10.0), ((1 + rand() % 100) / 10.0));
            (*jt) = value;
        }
}//

template class Matrix<int>;
template class Matrix<float>;
template class Matrix<double>;
template class Matrix<complex<float>>;
template class Matrix<complex<double>>;