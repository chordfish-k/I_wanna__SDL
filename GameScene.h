#pragma once

#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include <iostream>
#include "OverSDL.h"
#include "MySprite.h"
#include "Circle.h"



class GameScene : public Scene{
private:
	
	Sprite* sp;
	Circle2D* pp1, *pp4;
	Polygon2D* pp2;
	Polygon2D* pp3;
	double dt = 0;
	

public:
	GameScene() {
		dt = 0;
		sp = NULL;
		pp1 = NULL;
		pp2 = NULL;
		pp3 = NULL;
		pp4 = NULL;
	};
	void onLoad() {

		sp = new MySprite(Vec2(300, 300));
		sp->open("res/a.png");

		pp1 = new Circle2D(50, 400, 20);
		pp4 = new Circle2D(80, 500, 300);
		pp2 = new Polygon2D({ Vec2(150 , 50), Vec2(200, 50),Vec2(100, 130) });
		pp3 = new Polygon2D({ Vec2(60, 150), Vec2(160, 220), Vec2(160, 320), Vec2(60, 320) });

		
  
		addChild("sp", sp);
		addChild("pp1", pp1);
		addChild("pp2", pp2);
		addChild("pp3", pp3);
		addChild("pp4", pp4);
	}
	void onUpdate(double dt) {
		Scene::onUpdate(dt);
		this->dt = dt;
		//cout << dt << endl;
		
		double speed = 200.0;


		Vec2 velocity = Vec2(0, 0);
		if (Game::game->keys['A']) {
			velocity.x = -speed;
		}
		else if (Game::game->keys['D']) {
			velocity.x = speed;
		}
		else {
			velocity.x = 0;
		}

		if (Game::game->keys['W']) {
			velocity.y = -speed;
		}
		else if (Game::game->keys['S']) {
			velocity.y = speed;
		}
		else {
			velocity.y = 0;
		}


		if (fabs(velocity.x) <= eps && fabs(velocity.y) <= eps)
			return;
		
		Node* p = pp1;
		p->moveAndCollide(velocity*dt, true);
	}
	void onExit() {
		//cout << "exit" << endl;
	}

};

#endif