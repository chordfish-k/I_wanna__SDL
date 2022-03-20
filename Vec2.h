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
	double norm() const; //求模
	double normSquare() const; //求模平方
	Vec2 normalize()  const; //求单位向量
	Vec2 project(const Vec2& n)  const; //求对某向量投影的向量
	Vec2 perpendicular() const; //获取法向量
	double angleWith(Vec2 &n);
	double toAngle();
	Vec2 moveToword(Vec2 ed, double dtSpeedx, double dtSpeedy);
	Vec2 moveToword(Vec2 ed, double dtSpeed);
	//Vec2 &operator = (const Vec2& v); //复制
	bool operator == (const Vec2& v)const; //比较
	bool operator != (const Vec2& v)const;
	bool operator < (const Vec2& v) const; //比较
	Vec2 operator + (const Vec2& v)const;
	Vec2 operator - (const Vec2& v)const;
	Vec2 operator - ()const;
	double operator * (const Vec2& v)const; //点乘
	Vec2 operator * (double k)const; //数乘
	double cross(const Vec2& v) const; //叉乘(仅长度)
	Vec2 operator / (double k)const;
	friend ostream& operator << (ostream& os, Vec2& v) {
		os << "(" << v.x << ", " << v.y << ")";
		return os;
	}
};



