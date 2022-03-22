#pragma once

#ifndef SPRITE_H
#define SPRITE_H

#include <iostream>
#include <map>
#include <string>
#include <functional>

#include <SDL.h>
#include <SDL_image.h>


#include "Vec2.h"
#include "Node.h"
#include "Draw.h"
#include "Polygon.h"
#include "Scene.h"
#include "Animation.h"


using namespace std;


class Sprite : public Node{
private:
	SDL_Texture* img = NULL;
	SDL_Texture* defaultImg = NULL;
	

	SDL_Rect box = {0,0,0,0};
	double rotation = 0;
protected:
	Animation* curAnimation = NULL;
	Polygon2D collider;
	
	function<void(Sprite*)> updateFunc;
	function<void(Sprite*, Vec2)> collidedFunc;
	map<string, int> datas;

public:
	bool enableCollider = false;
	bool drawCollider = false;
	bool flipX = false;
	bool flipY = false;
	bool visable = true;
	bool simulateGravity = false;

	Vec2 velocity = Vec2(0, 0);
	double gravity = 2000;

public:
	Sprite(Vec2 position = Vec2(0, 0), string src = "", double scale = 1);
	Sprite(Sprite& sp);
	~Sprite();

	void open(string imgPath);
	SDL_Texture* getTexture();
	void setTexture(SDL_Texture* t) { if (t)img = t; };

	void runAnimation(Animation *anime);

	
	

	void setData(string dataName, int val) { datas[dataName] = val; }
	int getData(string dataName) { return datas[dataName]; }

	void draw();
	void draw(SDL_Rect targetRect);

	bool checkPointInside(Vec2& p) {
		return collider.checkPointInside(p); 
	};
	bool checkCollision(Collider& other, Vec2&dir) { 
		return collider.checkCollision(&other, dir);
	};

	vector<Line2D> getAllSides() { 
		if (enableCollider)
			return collider.getAllSides(); 
		return vector<Line2D>();
	}
	vector<Vec2> getAllSidesNormal() { 
		if (enableCollider)
			return collider.getAllSidesNormal(); 
		return vector<Vec2>();
	};
	Projection projectOn(Vec2& v) { 
		if (enableCollider)
			return collider.projectOn(v);
		return { 0, 0 }; 
	};
	void setPolygonCollider(Polygon2D &c);
	Polygon2D *getPolygonCollider() {return &collider; }
	Vec2 getPosition() { return position; };
	void setPosition(Vec2 p);
	void setBox(SDL_Rect r);
	SDL_Rect getBox() { return box; };
	void setColor(Color c) { collider.setColor(c);};
	Color getColor() { return collider.getColor(); }
	void setAnchor(Vec2 a);
	Vec2 getAnchor() { return anchor; };
	void setScale(double k);
	string getNodeType() { return "Sprite"; }
	void setName(string newName);
	void setRotation(double angle);
	void rotateTo(double angle, double speed = 360.0);
	double getRotation() { return rotation; }
	virtual Sprite* clone();

	virtual void onUpdate(double dt);
	virtual void onCollided(Node* other, Vec2 dir);

	void setUpdateFuncion(const function<void(Sprite*)> fun) { updateFunc = fun; };
	void setCollidedFuncion(const function<void(Sprite*, Vec2)> fun) { collidedFunc = fun; };
	function<void(Sprite*)> getUpdateFuncion() { return updateFunc; };
	function<void(Sprite*, Vec2)> getCollidedFuncion() { return collidedFunc; };
};


#endif