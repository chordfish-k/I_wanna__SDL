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
	void initialize();//��ʼ������

public:
	Matrix(const Matrix&);

	Matrix(int, int);
	Matrix(int, int, double);//Ԥ��ֿռ�
	~Matrix();
	Matrix& operator=(const Matrix&);//����ĸ���
	Matrix& operator=(double*);//�������ֵ��������
	Matrix& operator+=(const Matrix&);//�����+=����
	Matrix& operator-=(const Matrix&);//-=
	Matrix operator+(const Matrix&);//+
	Matrix operator-(const Matrix&);//-
	Matrix& operator*=(const Matrix&);//*=
	Matrix operator*(const Matrix& m)const;
	void print() const;//������ʾ
	double det();//����������ʽ
	double at(int i, int j) const;
	static Matrix eye(int, double);//����һ���Խ��;���
	int row() const;
	int col() const;
	static Matrix T(const Matrix& m);//����ת�õ�ʵ��,�Ҳ��ı����
};



#endif 