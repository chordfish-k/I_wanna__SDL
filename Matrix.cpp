#include "Matrix.h"

using std::endl;
using std::cout;
using std::istream;
const double EPS = 1e-10;

void Matrix::initialize() {//��ʼ�������С
	for (int i = 0; i < rows_num; ++i) {
		p.push_back(vector<double>());
		for (int j = 0; j < cols_num; ++j) {
			p[i].push_back(0);
		}
	}
}
//����һ��ȫ0����
Matrix::Matrix(int rows, int cols) :p(NULL)
{
	rows_num = rows;
	cols_num = cols;
	initialize();
}
//����һ��ֵȫ��Ϊvalue�ľ���
Matrix::Matrix(int rows, int cols, double value) :p(NULL)
{
	rows_num = rows;
	cols_num = cols;
	initialize();
	for (int i = 0; i < rows_num; i++) {
		for (int j = 0; j < cols_num; j++) {
			p[i][j] = value;
		}
	}

}

//��������
Matrix::~Matrix() {
	p.clear();

}

//���ƹ���
Matrix::Matrix(const Matrix& m) {
	p.clear();
	rows_num = m.row();
	cols_num = m.col();
	initialize();
	for (int i = 0; i < rows_num; i++) {
		for (int j = 0; j < cols_num; j++) {
			p[i][j] = m.p[i][j];
		}
	}

}


//ʵ�־���ĸ���
Matrix& Matrix::operator=(const Matrix& m)
{
	if (this == &m) {
		return *this;
	}

	if (rows_num != m.rows_num || cols_num != m.cols_num) {

		p.clear();

		rows_num = m.rows_num;
		cols_num = m.cols_num;
		initialize();
	}

	for (int i = 0; i < rows_num; i++) {
		for (int j = 0; j < cols_num; j++) {
			p[i][j] = m.p[i][j];
		}
	}
	return *this;
}
//�������ֵ���ݸ�����(Ҫ�����Ĵ�С�Ѿ�����������)
Matrix& Matrix::operator=(double* a) {
	for (int i = 0; i < rows_num; i++) {
		for (int j = 0; j < cols_num; j++) {
			p[i][j] = *(a + i * cols_num + j);
		}
	}
	return *this;
}
//+=����
Matrix& Matrix::operator+=(const Matrix& m)
{
	for (int i = 0; i < rows_num; i++) {
		for (int j = 0; j < cols_num; j++) {
			p[i][j] += m.p[i][j];
		}
	}
	return *this;
}
//ʵ��-
Matrix Matrix::operator-(const Matrix& m)
{
	Matrix res(rows_num, cols_num);
	for (int i = 0; i < rows_num; i++) {
		for (int j = 0; j < cols_num; j++) {
			res.p[i][j] = p[i][j] - m.p[i][j];
		}
	}
	return res;
}
Matrix Matrix::operator+(const Matrix& m)
{
	Matrix res(rows_num, cols_num);
	for (int i = 0; i < rows_num; i++) {
		for (int j = 0; j < cols_num; j++) {
			res.p[i][j] = p[i][j] + m.p[i][j];
		}
	}
	return res;
}
//ʵ��-=
Matrix& Matrix::operator-=(const Matrix& m)
{
	for (int i = 0; i < rows_num; i++) {
		for (int j = 0; j < cols_num; j++) {
			p[i][j] -= m.p[i][j];
		}
	}
	return *this;
}
//ʵ��*=
Matrix& Matrix::operator*=(const Matrix& m)
{
	Matrix temp(rows_num, m.cols_num);//��C=AB,�����C���������ھ���A��������C����������B��������
	for (int i = 0; i < temp.rows_num; i++) {
		for (int j = 0; j < temp.cols_num; j++) {
			for (int k = 0; k < cols_num; k++) {
				temp.p[i][j] += (p[i][k] * m.p[k][j]);
			}
		}
	}
	*this = temp;
	return *this;
}
//ʵ�־���ĳ˷�
Matrix Matrix::operator*(const Matrix& m)const {
	Matrix ba_M(rows_num, m.cols_num, 0.0);
	for (int i = 0; i < rows_num; i++) {
		for (int j = 0; j < m.cols_num; j++) {
			for (int k = 0; k < cols_num; k++) {
				ba_M.p[i][j] += (p[i][k] * m.p[k][j]);
			}
		}
	}
	return ba_M;
}



//������ʾ
void Matrix::print() const {
	cout << rows_num << " " << cols_num << endl;//��ʾ���������������
	for (int i = 0; i < rows_num; i++) {
		for (int j = 0; j < cols_num; j++) {
			cout << p[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

//�����������ʽ��ֵ
double Matrix::det() {
	//Ϊ��������ʽ��һ������
	double** back_up;
	back_up = new double* [rows_num];
	for (int i = 0; i < rows_num; i++) {
		back_up[i] = new double[cols_num];
	}
	for (int i = 0; i < rows_num; i++) {
		for (int j = 0; j < cols_num; j++) {
			back_up[i][j] = p[i][j];
		}
	}
	if (rows_num != cols_num) {
		std::abort();//ֻ�з�����ܼ�������ʽ����������ж�ǿ��ֹͣ����
	}
	double ans = 1;
	for (int i = 0; i < rows_num; i++) {
		//ͨ���б仯����ʽ��ʹ�þ���Խ����ϵ���Ԫ�ز�Ϊ0
		if (abs(p[i][i]) <= EPS) {
			bool flag = false;
			for (int j = 0; (j < cols_num) && (!flag); j++) {
				//�������һ���Խ����ϵ�Ԫ�ؽӽ���0���ܹ�ͨ���б任ʹ�þ���Խ����ϵ�Ԫ�ز�Ϊ0
				if ((abs(p[i][j]) > EPS) && (abs(p[j][i]) > EPS)) {
					flag = true;
					//ע�����л�����,p[i][j]��Ϊp[j][j]��p[j][i]��Ϊp[i][i]
					//�Ծ�������б任
					double temp;
					for (int k = 0; k < cols_num; k++) {
						temp = p[i][k];
						p[i][k] = p[j][k];
						p[j][k] = temp;
					}
				}
			}
			if (flag)
				return 0;
		}
	}
	for (int i = 0; i < rows_num; i++) {
		for (int j = i + 1; j < rows_num; j++) {
			for (int k = i + 1; k < cols_num; k++) {
				p[j][k] -= p[i][k] * (p[j][i] * p[i][i]);
			}
		}
	}
	for (int i = 0; i < rows_num; i++) {
		ans *= p[i][i];
	}
	for (int i = 0; i < rows_num; i++) {
		for (int j = 0; j < cols_num; j++) {
			p[i][j] = back_up[i][j];
		}
	}
	return ans;
}
//���ؾ����i�е�j�е���
double Matrix::at(int i, int j) const {
	return this->p[i][j];
}

//����һ����λ����
Matrix Matrix::eye(int n, double k = 1.0) {
	Matrix A(n, n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) {
				A.p[i][j] = k;
			}
			else {
				A.p[i][j] = 0;
			}
		}
	}
	return A;
}
//��ȡ����������
int Matrix::row() const {
	return rows_num;
}
int Matrix::col() const {
	return cols_num;
}
//ʵ�־����ת��
Matrix Matrix::T(const Matrix& m)
{
	int col_size = m.col();
	int row_size = m.row();
	Matrix mt(col_size, row_size);
	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < col_size; j++) {
			mt.p[j][i] = m.p[i][j];
		}
	}
	return mt;
}