#pragma once
#ifndef LINE_H
#define LINE_H

#include <iostream>
#include "Vec2.h"

using namespace std;

class Line2D {
public:
	Vec2 st;
	Vec2 ed;
public:
	Line2D(const Vec2 st, const Vec2 ed) : st(st), ed(ed) {}
	Line2D(double x1=0, double y1=0, double x2=0, double y2=0) {
		st = Vec2(x1, y1);
		ed = Vec2(x2, y2);
	}
	Line2D(const Line2D& l) {
		st = l.st;
		ed = l.ed;
	}
	
	friend ostream &operator << (ostream& os, const Line2D& l) {
		os << "(" << l.st.x << ", " << l.st.y << ")->(" << l.ed.x<<", "<<l.ed.y <<")" << endl;
		return os;
	}
};

#endif