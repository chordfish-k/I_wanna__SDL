#pragma once
#ifndef CIRCLE_H
#define CIRCLE_H

#include <iostream>
#include <string>
#include "Polygon.h"
#include "Vec2.h"
#include "Shape.h"
#include "Color.h"

using namespace std;

class Circle2D : public Polygon2D{
protected:
	double radius;

protected:
	void resetPoints() {
		points.clear();
		int count = 12 * (radius / 20);
		double dt = 2 * M_PI / count;
		int cnt = 0;

		for (double t = 0; t <= M_PI * 2; t += dt, cnt++) {
			points.push_back(Vec2((int)round(radius * cos(t)), (int)round(radius * sin(t))));
		}
		point_num = points.size();
	}

public:
	Circle2D(double radius = 10.0, int x = 0.0, int y = 0.0) 
		:radius(radius){
		position = Vec2(x, y);
		color = Color::WHITE;
		resetPoints();
	};
	Circle2D(double radius = 10.0, Vec2 position = Vec2()) 
		:radius(radius){
		position = position;
		color = Color::WHITE;
		resetPoints();
	};
	Circle2D(Circle2D &c);
	bool checkPointInside(Vec2& v);
	void setPosition(Vec2 p);
	Vec2 getPosition();
	void setRadius(double r);
	Collider::Projection projectOn(Vec2& v);
	Polygon2D* getPolygonCollider() { return this; }

	void draw();

	string getShapeType() { return "Circle"; };
};

#endif