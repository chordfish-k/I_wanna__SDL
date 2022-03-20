#include "Vec2.h"
#include "Tool.h"
#include <cmath>
/*
	角度的转单位向量
*/
Vec2::Vec2(double angle) {
	x = -cos(angle / 180.0 * M_PI);
	y = sin(angle / 180.0 * M_PI);
}

double Vec2::normSquare()  const {
	return x * x + y * y;
}

double Vec2::norm() const {
	return sqrt(normSquare());
}

Vec2 Vec2::normalize()  const {
	double n = norm();
	Vec2 v(x, y);
	return v / n;
}

Vec2 Vec2::project(const Vec2& v) const {
	double normNsquare = v.normSquare();
	Vec2 u(x, y);
	Vec2 prjnV = v.normalize() * norm();
	return prjnV;
}

Vec2 Vec2::perpendicular() const {
	Vec2 v(y, -x);
	return v;
}

double Vec2::angleWith(Vec2& n) {
	Vec2 v(x, y);
	return acos(v * n / v.norm() / n.norm()) / 3.14156535 * 180.0;
}

double Vec2::toAngle() {
	Vec2 right = Vec2(1, 0);
	return angleWith(right);
}

//Vec2 &Vec2::operator = (const Vec2& v){
//	if (this != &v) {
//		x = v.x;
//		y = v.y;
//	}
//	return *this;
//}


bool Vec2::operator == (const Vec2& v)const {
	return (x == v.x) && (y == v.y);
}
bool Vec2::operator != (const Vec2& v)const {
	return (x != v.x) || (y != v.y);
}

bool Vec2::operator < (const Vec2& v) const {
	if (x != v.x) return x < v.x;
	return y < v.y;
}

Vec2 Vec2::operator + (const Vec2& v)const {
	Vec2 ans(x + v.x, y + v.y);
	return ans;
}

Vec2 Vec2::operator - (const Vec2& v) const {
	Vec2 ans(x - v.x, y - v.y);
	return ans;
}

Vec2 Vec2::operator - () const {
	Vec2 ans(-x, -y);
	return ans;
}

double Vec2::operator * (const Vec2& v)const {
	return x * v.x + y * v.y;
}

Vec2 Vec2::operator * (double k) const {
	Vec2 ans(x * k, y * k);
	return ans;
}


double Vec2::cross(const Vec2& v) const {
	return (x * v.y - v.x * y);
}



Vec2 Vec2::operator / (double k)const {
	if (k <= 1e-6) return *this;
	Vec2 ans(x / k, y / k);
	return ans;
}

Vec2 Vec2::moveToword(Vec2 ed, double dtSpeedx, double dtSpeedy) {
	Vec2 st(x, y);
	Vec2 s = (ed - st).normalize();
	Vec2 ss(s.x * dtSpeedx, s.y * dtSpeedy);
	Vec2 p = st + ss;
	Vec2 t = (ed - p).normalize();
	if (s == -t) { //超了
		p = ed;
	}

	return p;
}

Vec2 Vec2::moveToword(Vec2 ed, double dtSpeed) {
	Vec2 st(x, y);
	Vec2 s = (ed - st).normalize();
	Vec2 p = st + s * dtSpeed;
	Vec2 t = (ed - p).normalize();
	if (s == -t) { //超了
		p = ed;
	}

	return p;
}