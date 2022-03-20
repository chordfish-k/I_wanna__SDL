#pragma once
#include <iostream>
#include <SDL.h>
#include "Polygon.h"

using namespace std;

class Triangle2D : public Polygon2D {
public:
	Triangle2D(Vec2 pos, Vec2 mid, Vec2 left, Vec2 right) {
		points = vector<Vec2>({ pos+mid, pos+right, pos+left });
		point_num = 3;
		position = pos;
	}
	string getShapeType() { return "Triangle"; };
};