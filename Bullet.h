#pragma once

#ifndef BULLET_H
#define BULLET_H

#include "Sprite.h"

class Bullet : public Sprite{
private:
	bool isCollided = false;
	double speed = 800;
public:
	Bullet(bool left);
	void onUpdate(double dt);
	void onCollided(Node* other, Vec2 dir);
};

#endif



