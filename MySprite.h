#pragma once

#ifndef MY_SPRITE_H
#define MY_SPRITE_H



#include "Sprite.h"

class MySprite : public Sprite {

public:
	MySprite(Vec2 v) : Sprite(v) {}
	void setPosition(Vec2 p) {
		Sprite::setPosition(p);
	}

};

#endif