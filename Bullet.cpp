#include "Bullet.h"
#include "Saver.h"

Bullet::Bullet(bool left) {
	speed = 500;
	this->open("res/player/bullet_0.png");
	speed = left ? -speed : speed;
	collideWith.insert("saver");
	collideWith.insert("floor");
	enableCollider = true;
}


void Bullet::onUpdate(double dt) {
	if (isCollided)
		return;
	moveAndCollide({speed * dt, 0});
}

void Bullet::onCollided(Node* other) {
	enableCollider = false;
	if (other->name == "saver") {
		//cout << "!!" << endl;
		Saver* s = (Saver*)other;
		s->saverPoint();
	}
	visable = false;
}
