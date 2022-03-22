#include "Polygon.h"
#include "Draw.h"
#include "Matrix.h"

Polygon2D::Polygon2D() {
	points = vector<Vec2>();
	point_num = 0;
	position = Vec2(0, 0);
}

Polygon2D::Polygon2D(const Polygon2D& p) {
	points = p.points;
	point_num = p.point_num;
	position = p.position;
}


vector<Line2D> Polygon2D::getAllSides() {
	vector<Line2D> res;
	Polygon2D* c = getPolygonCollider();
	if (c == NULL) return res;


	for (int i = 0; i < c->point_num - 1; i++) {
		Line2D v(c->points[i] + c->position, c->points[i + 1] + c->position);
		res.push_back(v);
	}
	res.push_back(Line2D(c->points[c->point_num - 1] + c->position, c->points[0] + c->position));
	return res;
}

vector<Vec2> Polygon2D::getAllSidesNormal() {
	vector<Vec2> res;
	Polygon2D* c = getPolygonCollider();
	if (c == NULL) return res;

	for (int i = 0; i < c->point_num - 1; i++) {
		Vec2 v(c->points[i].x - c->points[i + 1].x, c->points[i].y - c->points[i + 1].y);
		res.push_back(v.perpendicular().normalize());
	}
	Vec2 v(c->points[c->point_num - 1].x - c->points[0].x, c->points[c->point_num - 1].y - c->points[0].y);
	res.push_back(v.perpendicular().normalize());
	return res;
}

//返回的Line: start定义为min, end定义为max

Collider::Projection Polygon2D::projectOn(Vec2& v) {
	Collider::Projection p = { 0x7fffffff, -0x7fffffff };
	double tmp;
	for (int i = 0; i < point_num; i++) {
		tmp = (v) * (points[i] + position);
		p.max = max(p.max, tmp);
		p.min = min(p.min, tmp);
	}
	return p;
}

bool Polygon2D::checkCollision(Collider* other, Vec2& dir) {
	if (other == NULL) {
		return false;
	}
	vector<Vec2> axe1, axe2;
	Vec2 pj1, pj2;
	axe1 = getAllSidesNormal();
	axe2 = other->getAllSidesNormal();
	axe1.insert(axe1.end(), axe2.begin(), axe2.end());


	int cnt = 0, id = 0;
	double mivr = 9999;

	//bool flag = true;

	for (auto aixs : axe1) {

		Collider::Projection l1 = projectOn(aixs);
		Collider::Projection l2 = other->projectOn(aixs);
		double vr = 0;
		bool overlap = linesOverlap(l1, l2, vr);


		if (!overlap) {
			return false;
		}
		else {
			if (vr < mivr) {
				mivr = vr; id = cnt;
			}
		}
		cnt++;
	}
	if (id < axe1.size())
		dir = (-axe1[id].perpendicular());
	else
		dir = Vec2(0, 0);
	return true;
}

bool Polygon2D::linesOverlap(Collider::Projection& a, Collider::Projection& b, double& r) {
	r = fabs(a.max - b.min);
	return a.max > b.min
		&& b.max > a.min;
}

bool Polygon2D::checkPointInside(Vec2& v) {
	if (point_num < 3) return false;
	if ((points[point_num - 1] + position - v).cross(points[0] + position - v) < -eps) {
		return false;
	}
	for (int i = 0; i < point_num - 1; i++) {
		Vec2 a = points[i] + position - v;
		Vec2 b = points[i + 1] + position - v;
		if (a.cross(b) < -eps) {
			return false;
		}
	}
	return true;
}

void Polygon2D::setPosition(Vec2 p) {
	position = p;
}

void Polygon2D::scale(double k) {
	for (int i = 0; i < point_num; i++) {
		points[i].x *= k;
		points[i].y *= k;
	}
}

void Polygon2D::rotateBy(double angle) {
	
	double sub = (angle) * M_PI / 180.0;
	for (int i = 0; i < point_num; i++) {
		double ts[4] = { cos(sub), -sin(sub), sin(sub), cos(sub)};

		Matrix mat(2, 2), r_mat(2, 2);
		mat = Matrix::eye(2, 1);
		r_mat = ts;
		mat *= r_mat;

		double p[2] = { points[i].x, points[i].y};
		Matrix v_mat(2, 1);
		v_mat = p;
		mat *= v_mat;
		points[i] = { mat.at(0,0), mat.at(1, 0)};
	}
	this->rotation += angle;
}

double Polygon2D::getRotation() {
	return rotation;
}

void Polygon2D::draw() {
	if (!Draw::isInited) return;
	//cout << points.size() << endl;
	auto sides = getAllSides();
	for (auto s : sides) {
		Draw::DrawLine(s, color);
	}
}