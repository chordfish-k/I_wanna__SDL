#include "Spike.h"
#include "Triangle.h"
#include <thread>

/*
	0:up
	1:right
	2:down
	3:left
*/
Spike::Spike(int type) {
	Polygon2D tri;

	switch (type) {
	case 0:
		this->open("res/block/spike_up.bmp");
		tri = Triangle2D(Vec2(-16, -16), Vec2(16, 0), Vec2(0, 32), Vec2(32, 32));
		break;
	case 1:
		this->open("res/block/spike_right.bmp");
		tri = Triangle2D(Vec2(-16, -16), Vec2(0, 0), Vec2(32, 16), Vec2(0, 32));
		break;
	case 2:
		this->open("res/block/spike_down.bmp");
		tri = Triangle2D(Vec2(-16, -16), Vec2(16, 32), Vec2(0, 0), Vec2(32, 0));
		break;
	case 3:
		this->open("res/block/spike_left.bmp");
		tri = Triangle2D(Vec2(-16, -16), Vec2(32, 0), Vec2(32, 32), Vec2(0, 16));
		break;
	}
	
	this->setPolygonCollider(tri);
	this->setColor(Color(255,0,0,255));
	//this->anchor = Vec2(0.5, 0.5);

}

void Spike::onUpdate(double dt) {
	Sprite::onUpdate(dt);
	//cout << "sp" << endl;
}
