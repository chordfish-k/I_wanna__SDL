#pragma once
#ifndef MATRIX_H
#define MATRIX_H
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include "Vec2.h"
#include "stdlib.h"

using namespace std;


class Matrix {
public:
	int rows_num, cols_num;
	vector<vector<double>> p;
	void initialize();//初始化矩阵

public:
	Matrix(const Matrix&);

	Matrix(int, int);
	Matrix(int, int, double);//预配分空间
	~Matrix();
	Matrix& operator=(const Matrix&);//矩阵的复制
	Matrix& operator=(double*);//将数组的值传给矩阵
	Matrix& operator+=(const Matrix&);//矩阵的+=操作
	Matrix& operator-=(const Matrix&);//-=
	Matrix operator+(const Matrix&);//+
	Matrix operator-(const Matrix&);//-
	Matrix& operator*=(const Matrix&);//*=
	Matrix operator*(const Matrix& m)const;
	void print() const;//矩阵显示
	double det();//求矩阵的行列式
	double at(int i, int j) const;
	static Matrix eye(int, double);//制造一个对角型矩阵
	int row() const;
	int col() const;
	static Matrix T(const Matrix& m);//矩阵转置的实现,且不改变矩阵
};



#endif 