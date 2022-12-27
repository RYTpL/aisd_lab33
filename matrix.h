#pragma once
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
#include <iomanip>
#include <vector>
using namespace std;

template <class T>
class Matrix
{
private:
	int rows, columns;
	vector<vector<T>> matrix;


	auto begin() { return matrix.begin(); }
	auto end() { return matrix.end(); }

public:
	T epsilon;
	Matrix() = default; //
	Matrix(const Matrix& Matrix) = default;//
	Matrix(int rows, int columns); //
	void EnterMatrix(); 
	T operator () (int i, int j); //

	Matrix operator + (const Matrix& rhs);//
	Matrix operator - (const Matrix& rhs);//
	Matrix operator * (const Matrix& rhs);//
	Matrix operator * (const T& h);//
	Matrix operator / (const T& h);//
	Matrix& operator () (int m, int n, const T& value);
	auto cbegin() const { return matrix.cbegin(); }//

	auto cend() const { return matrix.cend(); }//

	friend std::ostream& operator << (std::ostream& s, const Matrix& matrix)
	{
	
		for (auto it = matrix.cbegin(); it != matrix.cend(); it++)
		{
			for (auto iter : (*it))
			{
				s << iter << " ";
			}
		}
		return s;
	}//
	int GetRows() const;//
	int GetCols() const;//
	T tr();//
	void CreateMatrixForCheck();
	void CheckTheDeterminant();
	void Random();//
	~Matrix() = default;//
};