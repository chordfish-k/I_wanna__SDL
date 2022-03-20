#pragma once

#ifndef SPRITE_H
#define SPRITE_H

#include <iostream>
#include <map>
#include <string>
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
	
public:
	bool enableCollider = false;
	bool drawCollider = false;
	bool flipX = false;
	bool flipY = false;
	bool visable = true;
	

public:
	Sprite(Vec2 position = Vec2(0,0), string src = "", double scale = 1)
		: Node(position),  box({0,0,0,0})// box(Polygon())
	{ 
		collider = Polygon2D({Vec2(0,0),Vec2(0,0) ,Vec2(0,0) ,Vec2(0,0) }, position);
		anchor = Vec2(0.5, 0.5);
		if (src != "") {
			open(src);
		}
		setScale(scale);
	};
	Sprite(Sprite& sp);
	~Sprite();

	void open(string imgPath);
	SDL_Texture* getTexture();
	void setTexture(SDL_Texture* t) { if (t)img = t; };

	void runAnimation(Animation *anime);

	virtual void onUpdate(double dt);

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
	void cloneTo(Sprite* sp);
	void setScale(double k);
	string getNodeType() { return "Sprite"; }
	void setName(string newName);
	void setRotation(double angle);
	void rotateTo(double angle, double speed = 360.0);
	double getRotation() { return rotation; }
	virtual Sprite* clone();
};


#endif