#pragma once

#ifndef GAME_SCENE2_H
#define GAME_SCENE2_H

#include <iostream>
#include "OverSDL.h"
#include "MySprite.h"
#include "Line.h"



class Scene2 : public Scene {
private:

	Polygon2D* ground = NULL;
	Polygon2D* ground2 = NULL;
	Polygon2D* ground3 = NULL;
	Polygon2D* rect = NULL;
	Polygon2D* tri = NULL;
	double dt = 0;

	//控制
	double acceleration = 8000;
	double friction = 15000;
	double YFirction = friction / 5;
	double gravity = 2500;
	double jumpSpeed = 950;
	double speed = 600.0;

	Vec2 velocity = Vec2(0, 0);
	Vec2 YTargetVel = Vec2(0, 0);
	Vec2 XTargetVel = Vec2(0, 0);
	bool jumping = false;


public:

	void onLoad() {
		ground = new Polygon2D({Vec2(0, Draw::H-80), Vec2(Draw::W, Draw::H-80) , Vec2(Draw::W, Draw::H) , Vec2(0, Draw::H) });
		ground2 = new Rectangle2D(Vec2(100, Draw::H - 200), 300, 30);//new Polygon({ Vec2(0, Draw::H - 280), Vec2(Draw::W, Draw::H - 280) , Vec2(Draw::W, Draw::H-220) , Vec2(0, Draw::H-220) });
		ground3 = new Polygon2D({ Vec2(0, 0), Vec2(0, Draw::H) , Vec2(-5, Draw::H - 220) , Vec2(-5, 0) });
		rect = new Rectangle2D(Vec2(100, Draw::H-150), 20, 30); //new Polygon({Vec2(-15, 40), Vec2(15, 40) , Vec2(15, -30) , Vec2(-20, -30) });

		tri = new Polygon2D({ Vec2(-20, 10), Vec2(0, -30) , Vec2(20, 10)});
		tri->setPosition(Vec2(300, Draw::H - 90));

		addChild("ground", ground);
		addChild("ground2", ground2);
		addChild("ground3", ground3);
		addChild("rect", rect);
		addChild("tri", tri);
	}


	void onUpdate(double dt) {
		Scene::onUpdate(dt);
		this->dt = dt;

		
		if (Game::game->keys['A']) {
			XTargetVel.x = -speed;
		}
		else if (Game::game->keys['D']) {
			XTargetVel.x = speed;
		}
		else {
			XTargetVel.x = 0;
		}

		if (Game::game->keys[VK_SPACE]) {
			
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
			velocity = velocity.moveToword(kvel , (move ? acceleration : friction) * dt , YFirction * dt);
		}
		else {
			velocity = velocity.moveToword(Vec2(0, 0), friction * dt , YFirction * dt);
		}

		Node* p = rect;

		Vec2 re = p->moveAndCollide(velocity * dt);

		if (fabs(re.x) > eps || fabs(re.y) > eps) {
			
			if (velocity.y >= 0 && !Game::game->keys[VK_SPACE]) {
				jumping = false;
			}
			YTargetVel = Vec2(0, jumpSpeed);
			if(fabs(re.y) > eps)
				velocity.y = 0;
		}


	}
	void onExit() {

	}

	

};

#endif