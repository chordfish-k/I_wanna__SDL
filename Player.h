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

	//控制
	double acceleration = 9000;
	double friction = 15000;
	double YFirction = friction / 5;
	
	double jumpSpeed = 680;
	double speed = 280.0;
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
	void onCollided(Node* other, Vec2 dir);
	void setState(State newState);
	void checkMove(double dt);
	void checkShoot(double dt);
	void checkOutside(); //掉出世界
	void die();
private:
	void changeAnime();
};

#endif
