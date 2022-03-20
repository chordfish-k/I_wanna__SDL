#pragma once
#ifndef BLOOD_EFFECT_H
#define BLOOD_EFFECT_H


#include <SDL.h>
#include <vector>
#include "Sprite.h"
#include "Vec2.h"
#include "Timer.h"

class BloodEffect : public Node{
private:
	struct Piece {
		SDL_Rect rect;
		Vec2 speed;
		Color color;
		void setPosition(Vec2 p) {
			rect.x = p.x;
			rect.y = p.y;
		}
		Vec2 getPosition() {
			return Vec2(rect.x, rect.y);
		}
	};
	vector<Piece> pieces = {};
	double startAngle = 90;
	double angleRange = 120;
	double startSpeed = -250;
	double speedRange = 50;
	int num = 10;
	int numRange = 3;
	bool fall = true;
	Vec2 gravity = Vec2(0, 550);
	LTimer timer;
	int startTick = 0;
	int burstDuration = 500;
	int existingDuration = 3000;
	bool isEnd = false;
	bool isBurstEnd = false;
public:
	BloodEffect(Vec2 pos);
	void onUpdate(double dt);
	void draw();
};

#endif