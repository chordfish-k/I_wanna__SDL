#include "Bullet.h"
#include "Saver.h"

Bullet::Bullet(bool left) {
	speed = 500;
	this->open("res/player/bullet_0.bmp");
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

void Bullet::onCollided(Node* other, Vec2 dir) {
	enableCollider = false;
	if (other->name == "saver") {
		//cout << "!!" << endl;
		cout << other->getNodeType() << endl;
		Sprite* sp = dynamic_cast<Sprite*> (other);
		if (sp) {
			cout << "?" << endl;
			Saver* s = dynamic_cast<Saver*> (sp);
			if (s) {
				cout << "!" << endl;
				s->saverPoint();
			}
				
		}
		
	}
	visable = false;
}
