#pragma once
#include "Sprite.h"
#include "Draw.h"

class GameOverSprite : public Sprite {

public:
	GameOverSprite() {
		open("res/other/gameover.png");
		setScale(0.5);
		setPosition(Vec2(Draw::W / 2, Draw::H / 2));
	}
};