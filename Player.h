#pragma once
#ifndef  PLAYER_H
#define PLAYER_H

#include "Sprite.h"

class Player : public Sprite {
private:
	Animation* animation_idle;
	Animation* animation_run;
	Animation* animation_jump;
	Animation* animation_fall;

	//¿ØÖÆ
	double acceleration = 9000;
	double friction = 15000;
	double YFirction = friction / 5;
	double gravity = 2000;
	double jumpSpeed = 680;
	double speed = 250.0;
	bool hasLastpoint = false;
	Vec2 lastPosition = Vec2(0, 0);
	Vec2 velocity = Vec2(0, 0);
	Vec2 YTargetVel = Vec2(0, 0);
	Vec2 XTargetVel = Vec2(0, 0);
	Vec2 re = Vec2(0, 0);
	bool jumping = false;
	int jumpCnt = 0;

	

	enum class State {
		IDLE=0,
		RUN=1,
		JUMP=2,
		FALL=3,
		DEATH=4
	}state = State::IDLE;
public:
	Player();
	void reset();
	void onUpdate(double dt);
	void onCollided(Node* other);
	void setState(State newState);
	void checkMove(double dt);
	void checkShoot(double dt);

private:
	void changeAnime();
};

#endif
