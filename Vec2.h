#pragma once
#include <iostream>
using namespace std;
//#include "Point.h"

class Vec2 {
public:
	double x;
	double y;

public:
	Vec2() { x = 0; y = 0; }
	Vec2(double x, double y) : x(x), y(y) {}
	Vec2(double angle);
	//Vec2(const Point& p) : x(p.x), y(p.y) {}
	Vec2(const Vec2 &v) : x(v.x), y(v.y) {}
	double norm() const; //��ģ
	double normSquare() const; //��ģƽ��
	Vec2 normalize()  const; //��λ����
	Vec2 project(const Vec2& n)  const; //���ĳ����ͶӰ������
	Vec2 perpendicular() const; //��ȡ������
	double angleWith(Vec2 &n);
	double toAngle();
	Vec2 moveToword(Vec2 ed, double dtSpeedx, double dtSpeedy);
	Vec2 moveToword(Vec2 ed, double dtSpeed);
	//Vec2 &operator = (const Vec2& v); //����
	bool operator == (const Vec2& v)const; //�Ƚ�
	bool operator != (const Vec2& v)const;
	bool operator < (const Vec2& v) const; //�Ƚ�
	Vec2 operator + (const Vec2& v)const;
	Vec2 operator - (const Vec2& v)const;
	Vec2 operator - ()const;
	double operator * (const Vec2& v)const; //���
	Vec2 operator * (double k)const; //����
	double cross(const Vec2& v) const; //���(������)
	Vec2 operator / (double k)const;
	friend ostream& operator << (ostream& os, Vec2& v) {
		os << "(" << v.x << ", " << v.y << ")";
		return os;
	}
};



