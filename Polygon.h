#pragma once

#ifndef POLYGON_H
#define POLYGON_H


#include <iostream>
#include <vector>
#include <cstdlib>
#include <set>
#include "Vec2.h"
#include "Line.h"
#include "Shape.h"
#include "Color.h"
#include "Drawable.h"
#include "Collider.h"

#define eps 1e-6

using namespace std;

class Polygon2D : public Shape2D {

private:
	double rotation = 0;

public:

	bool linesOverlap(Collider::Projection& a, Collider::Projection& b, double& r);
	Collider::Projection projectOn(Vec2& v);


public:
	Polygon2D();
	Polygon2D(const Polygon2D& p);
	Polygon2D(vector<Vec2> points, Vec2 pos = Vec2(0, 0))
		: Shape2D(points)//points(points), point_num(points.size())//,Shape(Vec2(0, 0))
	{
		position = pos;
		setColor(Color::WHITE);
	}
	bool checkCollision(Collider* other, Vec2& dir);
	bool checkPointInside(Vec2& v);
	vector<Line2D> getAllSides(); //获取所有边
	vector<Vec2> getAllSidesNormal(); //获取所有边的法向量
	vector<Vec2> getAllPoints() const { return points; };
	void setPosition(Vec2 p); //设置中心点位置
	Vec2 getPosition(){ return position; };
	Polygon2D* getPolygonCollider(){ return this; }
	void scale(double k);
	void rotateBy(double angle);
	double getRotation();

	string getShapeType(){ return "Polygon"; };

	void draw(); //画
	void print() {
		cout << "Polygon(";
		auto ps = getAllPoints();
		for (auto p : ps) {
			cout << p;
			cout << ", ";
		}
		cout << ")\n";
	}
	friend ostream& operator << (ostream& os, const Polygon2D& l) {
		os << "Polygon(";
		auto ps = l.getAllPoints();
		for (auto p : ps) {
			os << p;
			os << ", ";
		}
		os << ")\n";
		return os;
	}
};


#endif
