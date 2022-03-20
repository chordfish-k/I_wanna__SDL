#include "Circle.h"
#include "Draw.h"

Circle2D::Circle2D(Circle2D& c) {
	radius = c.radius;
	position = c.position;
	color = c.color;
	points = c.points;
	point_num = c.point_num;
}

void Circle2D::setPosition(Vec2 p) {
	position = p;
}


Vec2 Circle2D::getPosition() {
	return position;

}

void Circle2D::setRadius(double r) {
	radius = r;
	resetPoints();
}


bool Circle2D::checkPointInside(Vec2& v) {
	Vec2 sub = getPosition() - v;
	return radius * radius >= sub.normSquare();
}


Collider::Projection Circle2D::projectOn(Vec2& v) {
	Collider::Projection p = { 0x7fffffff, -0x7fffffff };
	double tmp = v * position;
	p.min = tmp - radius;
	p.max = tmp + radius;
	return p;

}


void Circle2D::draw() {
	auto sides = getAllSides();
	//cout << sides.size() << endl;
	for (auto s : sides) {
		Draw::DrawLine(s, color);
	}
}

