#include "Scene2.h"
void Scene2::onLoad() {
	ground = new Polygon({ Vec2(0, Draw::H - 80), Vec2(Draw::W, Draw::H - 80) , Vec2(Draw::W, Draw::H) , Vec2(0, Draw::H) });
	ground2 = new Rectangle(Vec2(100, Draw::H - 200), 300, 30);//new Polygon({ Vec2(0, Draw::H - 280), Vec2(Draw::W, Draw::H - 280) , Vec2(Draw::W, Draw::H-220) , Vec2(0, Draw::H-220) });
	ground3 = new Polygon({ Vec2(0, 0), Vec2(0, Draw::H) , Vec2(-5, Draw::H - 220) , Vec2(-5, 0) });
	rect = new Rectangle(Vec2(100, Draw::H - 150), 20, 30); //new Polygon({Vec2(-15, 40), Vec2(15, 40) , Vec2(15, -30) , Vec2(-20, -30) });

	tri = new Polygon({ Vec2(-20, 10), Vec2(0, -30) , Vec2(20, 10) });
	tri->setPosition(Vec2(300, Draw::H - 90));

	addChild("ground", ground);
	addChild("ground2", ground2);
	addChild("ground3", ground3);
	addChild("rect", rect);
	addChild("tri", tri);
}


void Scene2::onUpdate(double dt) {
	Scene::onUpdate(dt);
	this->dt = dt;


	if (game->keys['A']) {
		XTargetVel.x = -speed;
	}
	else if (game->keys['D']) {
		XTargetVel.x = speed;
	}
	else {
		XTargetVel.x = 0;
	}

	if (game->keys[VK_SPACE]) {

		if (!jumping) {
			jumping = true;
			velocity.y = -jumpSpeed;
		}
	}


	YTargetVel = YTargetVel.moveToword(Vec2(0, gravity), 0, gravity * dt);
	Vec2 kvel = XTargetVel + YTargetVel; //目标合速度

	bool move = (fabs(XTargetVel.x) > eps || fabs(XTargetVel.y) > eps);
	bool jp = (fabs(YTargetVel.y) > eps);

	if (move || jp) {
		velocity = velocity.moveToword(kvel, (move ? acceleration : friction) * dt, YFirction * dt);
	}
	else {
		velocity = velocity.moveToword(Vec2(0, 0), friction * dt, YFirction * dt);
	}

	Node* p = rect;

	Vec2 re = moveAndCollide(p, velocity * dt);

	if (fabs(re.x) > eps || fabs(re.y) > eps) {

		if (velocity.y >= 0 && !game->keys[VK_SPACE]) {
			jumping = false;
		}
		YTargetVel = Vec2(0, jumpSpeed);
		if (fabs(re.y) > eps)
			velocity.y = 0;
	}


}
void Scene2::onExit() {

}

/*
* 该函数将返回一个受力方向
*/
Vec2 Scene2::moveAndCollide(Node* p, Vec2 velocity, bool slide) {
	Vec2 res(0, 0);


	Vec2 first(0, 0), all(0, 0);
	Vec2 tmp = p->getPosition();

	p->setPosition(tmp + velocity);

	map<string, Node* > ch = getAllChilden();
	for (auto n : ch) {
		if (n.first != p->name && p->getPolygonCollider()->checkCollision(*n.second->getPolygonCollider(), first)) {
			all = all + first;
		}
	}

	res = all;

	double err = 1; //使用遍历搜出刚好不发生碰撞的位置。。有点莽，理论上可以用二分改进
	bool flag = false;
	int cnt = 0;
	while (cnt < 20 && (all.x != 0 || all.y != 0))
	{
		p->setPosition(tmp);
		if (all.x != 0 || all.y != 0) {
			double angle = all.angleWith(velocity);

			velocity = Vec2(fabs(all.x) < eps ? 0 : velocity.x, fabs(all.x) < eps ? velocity.y : 0);
			if (slide) {
				if (angle < 90) {
					velocity = velocity.project(all.normalize());
					p->setPosition(tmp + velocity * err);
				}
				else if (angle > 90) {
					velocity = velocity.project(-all.normalize());
					p->setPosition(tmp + velocity * err);
				}
			}
			else {
				p->setPosition(tmp + velocity * err);
			}
			err -= 0.1;
			cnt++;
		}
		all = Vec2(0, 0);
		for (auto n : ch) {
			if (n.first != p->name && p->getPolygonCollider()->checkCollision(*n.second->getPolygonCollider(), first)) {
				all = all + first;
			}
		}
	}
	return res.perpendicular();
}