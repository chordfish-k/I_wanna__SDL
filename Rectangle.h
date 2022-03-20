#pragma once
#include <iostream>
#include <SDL.h>
#include "Polygon.h"

using namespace std;

class Rectangle2D : public Polygon2D {
private:
	double H;
	double W;
public:
	Rectangle2D(Vec2 pos, double w, double h) : H(h), W(w) {
		position = pos;
		points = vector<Vec2>({Vec2(position.x, position.y), Vec2(position.x + w, position.y),
				Vec2(position.x + w, position.y + h), Vec2(position.x, position.y + h)});
		point_num = 4;
		
	}
	Rectangle2D(Vec2 pos, Vec2 LT, Vec2 RB) : H(RB.y-LT.y), W(RB.x-LT.x) {
		position = pos;
		points = vector<Vec2>({ LT + pos, Vec2(RB.x, LT.y) + pos,
				RB + pos, Vec2(LT.x, RB.y) + pos });
		point_num = 4;
	}
	string getShapeType() { return "Rectangle"; };
};