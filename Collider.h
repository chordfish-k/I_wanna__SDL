#pragma once
#ifndef COLLIDER_H
#define COLLIDER_H
//#include "Polygon.h"
#include <vector>
#include "Vec2.h"

using namespace std;

class Polygon2D;

class Collider {
public:
	struct Projection {
		double min;
		double max;
	};
public:
	Collider() {};
	virtual bool checkPointInside(Vec2& p) { return false; };
	virtual bool checkCollision(Collider& other, Vec2& dir) { return false; };
	virtual vector<Vec2> getAllSidesNormal() { return vector<Vec2>(); };
	virtual Projection projectOn(Vec2& v) { return { 0, 0 }; };
	virtual Polygon2D *getPolygonCollider() { return NULL; }
};

#endif